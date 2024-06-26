#include "wfmcollection.hpp"

void WFMCollection::SearchForWFMs(std::string searchPath)
    {
        for(const auto& entry : std::filesystem::directory_iterator(searchPath))
        {
            if (std::filesystem::is_regular_file(entry.path()) &&
               (std::filesystem::path(entry.path()).filename().extension() == ".wfm"))  
               {
                std::string filename = std::filesystem::path(entry.path()).filename().string();
                if(filename.find("DC") != std::string::npos)
                {
                    DCFileList.push_back(filename);
                } else if (filename.find("RF") != std::string::npos)
                {
                    RFFileList.push_back(filename);
                }
               }
        }
        // Sort the lists
        std::sort(DCFileList.begin(), DCFileList.end());
        std::sort(RFFileList.begin(), RFFileList.end());

        // Break out the lists into vectors ordered by scan number
        int scanNo = 0;
        std::vector<std::string> tempDCList;
        std::vector<std::string> tempRFList;
        bool scanIncremented = false;
        this->FilesInCollection = DCFileList.size();
        for(int i = 0; i < DCFileList.size(); i++)
        {
            std::string scanString = std::format("{0:02}", scanNo);
            std::string scanPattern = "DC-" + scanString;
            if(DCFileList[i].find(scanPattern.c_str()) != std::string::npos)
            {
                tempDCList.push_back(searchPath + "/" + DCFileList[i]);
                tempRFList.push_back(searchPath + "/" + RFFileList[i]);
            } else {
                if(tempDCList.size() != 0)
                {
                    this->DCScanList.push_back(tempDCList);
                    this->RFScanList.push_back(tempRFList);
                    tempDCList.clear();
                    tempRFList.clear();
                    scanNo++;
                    scanIncremented = true;
                }

                if(scanIncremented)
                {
                    tempDCList.push_back(searchPath + "/" + DCFileList[i]);
                    tempRFList.push_back(searchPath + "/" + RFFileList[i]);
                    scanIncremented = false;
                }
            }
        }
        this->DCScanList.push_back(tempDCList);
        this->RFScanList.push_back(tempRFList);
        this->ScansInCollection = DCScanList.size();
        return;
    }


void WFMCollection::ComputeDC()
{
    return;
}

void WFMCollection::ComputeDCAverage_mp(std::vector<std::vector<std::string>>& _fileset)
{
    const int n_threads = 8;
    this->DCValues.clear();
    for(auto &currentScan : _fileset)
    {
        std::vector<std::vector<double>> _dcOutput;
        std::vector<std::thread> threadVec;
        int scanrows = currentScan.size();
        int chunksize = scanrows / n_threads;
        int points_in_scanrow = -1;
        // If this is the first file, parse it to figure out how many points there
        // are in each 'row'
        WFMFile tempWFM;
        tempWFM.ParseWFMFile(currentScan[0]);
        points_in_scanrow = tempWFM.GetPoints();
        // We should now have enough information to initalize an empty vector to work on
        _dcOutput.resize(scanrows, std::vector<double>(points_in_scanrow, 0.0));
        for(int tNumber = 0; tNumber < n_threads; ++tNumber)
        {
            threadVec.emplace_back([tNumber, chunksize, n_threads, scanrows, &currentScan, &_dcOutput]()
            {
                int tStart = tNumber * chunksize;
                int tEnd = (tNumber == n_threads - 1) ? scanrows : tStart + chunksize;
                for(int idx = tStart; idx < tEnd; ++idx)
                {
                    WFMFile tmp_mp_wfm;
                    tmp_mp_wfm.ParseWFMFile(currentScan[idx]);
                    tmp_mp_wfm.ComputeDCAverage();
                    _dcOutput[idx] = std::move(tmp_mp_wfm.DCAverages);
                }
            });
        }
        // Wait for the threads to finish and add the completed scan to the DCMaps object
        for(std::thread& t : threadVec)
        {
            t.join();
        }
        this->DCValues.push_back(std::move(_dcOutput));
    }
}

