#include "wfmcollection.hpp"

/**
 * Search for WFM files in the specified directory and organize them into scan lists.
 * @param searchPath The directory path to search for WFM files
 */
void WFMCollection::SearchForWFMs(std::string searchPath)
{
    // Iterate over each entry in the specified directory
    for(const auto& entry : std::filesystem::directory_iterator(searchPath))
    {
        // Check if the entry is a regular file and has a ".wfm" extension
        if (std::filesystem::is_regular_file(entry.path()) &&
            (std::filesystem::path(entry.path()).filename().extension() == ".wfm"))
        {
            // Extract the filename from the path
            std::string filename = std::filesystem::path(entry.path()).filename().string();

            // Determine if the file is a DC or RF file and add it to the respective list
            if(filename.find("DC") != std::string::npos)
            {
                DCFileList.push_back(filename);
            }
            else if (filename.find("RF") != std::string::npos)
            {
                RFFileList.push_back(filename);
            }
        }
    }

    // Sort the DC and RF file lists
    std::sort(DCFileList.begin(), DCFileList.end());
    std::sort(RFFileList.begin(), RFFileList.end());

    // Organize files into scan lists based on scan numbers
    int scanNo = 0;
    std::vector<std::string> tempDCList;
    std::vector<std::string> tempRFList;
    bool scanIncremented = false;
    this->FilesInCollection = DCFileList.size();

    // Iterate over the DC file list to create scan lists
    for(int i = 0; i < DCFileList.size(); i++)
    {
        // Create scan pattern based on scan number
        std::string scanString = std::format("{0:02}", scanNo);
        std::string scanPattern = "DC-" + scanString;

        // Check if the current file belongs to the current scan
        if(DCFileList[i].find(scanPattern.c_str()) != std::string::npos)
        {
            // Add the file paths to the temporary scan lists
            tempDCList.push_back(searchPath + "/" + DCFileList[i]);
            tempRFList.push_back(searchPath + "/" + RFFileList[i]);
        }
        else
        {
            // If the file doesn't belong to the current scan
            if(tempDCList.size() != 0)
            {
                // Add completed scan lists to the main lists and reset temporary lists
                this->DCScanList.push_back(tempDCList);
                this->RFScanList.push_back(tempRFList);
                tempDCList.clear();
                tempRFList.clear();
                scanNo++;
                scanIncremented = true;
            }

            // If the scan was already incremented, add the current file to a new scan list
            if(scanIncremented)
            {
                tempDCList.push_back(searchPath + "/" + DCFileList[i]);
                tempRFList.push_back(searchPath + "/" + RFFileList[i]);
                scanIncremented = false;
            }
        }
    }

    // Add any remaining scan lists to the main lists
    this->DCScanList.push_back(tempDCList);
    this->RFScanList.push_back(tempRFList);
    this->ScansInCollection = DCScanList.size();
    return;
}


void WFMCollection::ComputeDC()
{
    return;
}

/**
 * Computes the DC average for each row in the given set of WFM files using multithreading.
 * @param _fileset A vector of vectors of strings representing the WFM file set
 */
void WFMCollection::ComputeDCAverage_mp(std::vector<std::vector<std::string>>& _fileset)
{
    // Get the number of available hardware threads
    const int n_threads = std::thread::hardware_concurrency();

    // Clear the existing DC values
    this->DCValues.clear();

    // Iterate over each scan in the file set
    for(auto &currentScan : _fileset)
    {
        std::vector<std::vector<double>> _dcOutput;
        std::vector<std::thread> threadVec;
        int scanrows = currentScan.size();
        int chunksize = scanrows / n_threads;
        int points_in_scanrow = -1;

        // Parse the first file to determine the number of points in each 'row'
        WFMFile tempWFM;
        tempWFM.ParseWFMFile(currentScan[0]);
        points_in_scanrow = tempWFM.GetPoints();

        // Initialize an empty vector based on the scan rows and points information
        _dcOutput.resize(scanrows, std::vector<double>(points_in_scanrow, 0.0));

        // Create threads for parallel processing
        for(int tNumber = 0; tNumber < n_threads; ++tNumber)
        {
            threadVec.emplace_back([tNumber, chunksize, n_threads, scanrows, &currentScan, &_dcOutput]()
                                   {
                                       int tStart = tNumber * chunksize;
                                       int tEnd = (tNumber == n_threads - 1) ? scanrows : tStart + chunksize;

                                       // Process each row within the assigned chunk
                                       for(int idx = tStart; idx < tEnd; ++idx)
                                       {
                                           WFMFile tmp_mp_wfm;
                                           tmp_mp_wfm.ParseWFMFile(currentScan[idx]);
                                           tmp_mp_wfm.ComputeDCAverage();
                                           _dcOutput[idx] = std::move(tmp_mp_wfm.DCAverages);
                                       }
                                   });
        }

        // Wait for all threads to finish and add the completed scan to the DCValues object
        for(std::thread& t : threadVec)
        {
            t.join();
        }

        this->DCValues.push_back(std::move(_dcOutput));
    }
}

/**
 * Computes the Fast Fourier Transform (FFT) for each row in the given set of RF files.
 * @param _rffileset A vector of vectors of strings representing the RF file set
 */
void WFMCollection::ComputeFFT_mp(std::vector<std::vector<std::string>>& _rffileset)
{
    // Loop through each scan in the RF file set
    for(int scan = 0; scan < _rffileset.size(); ++scan)
    {
        // Create a frequency map for the current scan
        std::vector<std::vector<double>> frequencyMap(_rffileset[scan].size(), std::vector<double>());

        // Loop through each row in the current scan
        for(int row = 0; row < _rffileset[scan].size(); ++row)
        {
            // Load the RF WFM file and extract sample values
            WFMFile tempWFM;
            tempWFM.ParseWFMFile(_rffileset[scan][row]);
            double sampleRate = 1 / tempWFM.GetSecondsResolution();
            int pxInRow = tempWFM.GetFastFrames();
            std::vector<double> peakFrequenciesInRow(pxInRow, 0.0);

            // Loop through each pixel in the row
            for (int cPixel = 0; cPixel < pxInRow; ++cPixel)
            {
                double pixelMaxFrequency = 0.0;
                double pixelMaxMagnitude = 0.0;
                fftw_complex* inVec = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*pxInRow);
                fftw_complex* outVec = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*pxInRow);
                fftw_plan fft_plan = fftw_plan_dft_1d(pxInRow, inVec, outVec, FFTW_FORWARD, FFTW_ESTIMATE);

                // Copy each sample into the FFT array and set imaginary parts to 0
                for(int sNum = 0; sNum < pxInRow; ++sNum)
                {
                    inVec[sNum][0] = tempWFM.ScaledData[cPixel][sNum];
                    inVec[sNum][1] = 0.0;
                }

                // Perform FFT calculation
                fftw_execute(fft_plan);
                double freqbin = sampleRate / tempWFM.ScaledData[cPixel].size();

                // Loop through frequency bins
                for(int fIdx = 0; fIdx < tempWFM.ScaledData[cPixel].size(); ++fIdx)
                {
                    double frequency = fIdx * freqbin;
                    double magnitude = std::sqrt(std::pow(outVec[fIdx][0], 2) + std::pow(outVec[fIdx][1], 2));

                    // Check if the current magnitude is greater than the maximum magnitude
                    if(magnitude > pixelMaxMagnitude)
                    {
                        pixelMaxMagnitude = magnitude; // Update maximum magnitude
                        pixelMaxFrequency = frequency; // Update corresponding frequency
                    }
                }

                peakFrequenciesInRow[cPixel] = pixelMaxFrequency; // Save peak frequency for the pixel

                // Cleanup and free FFTW memory
                fftw_destroy_plan(fft_plan);
                fftw_free(inVec);
                fftw_free(outVec);
            }

            frequencyMap[row] = std::move(peakFrequenciesInRow); // Store peak frequencies for the row
        }

        this->FrequencyMaps.emplace_back(frequencyMap); // Add frequency map for the current scan
    }
}

double WFMCollection::ComputeRowFFT_mp(std::string rowfile)
{

}
