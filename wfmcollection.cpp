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
    for(auto &currentScanSet : this->DCScanList)
    {
        std::vector<std::vector<double>> tmpDCValues;
        tmpDCValues.reserve(currentScanSet.size());
        for(auto &wfmFileString : currentScanSet)
        {
            WFMFile tmpData;
            tmpData.ParseWFMFile(wfmFileString);
            tmpData.ComputeDCAverage();
            tmpDCValues.push_back(std::move(tmpData.DCAverages));
        }
        this->DCValues.push_back(std::move(tmpDCValues));
    }
    return;
}
