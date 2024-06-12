#ifndef WFMCOLLECTION_H
#define WFMCOLLECTION_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <format>

class WFMCollection
{
    public:
    void SearchForWFMs(std::string searchPath)
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
        std::cout << "Found " << DCFileList.size() << " DC files and " 
                  << RFFileList.size() << " RF files" << std::endl;

        // Sort the lists
        std::sort(DCFileList.begin(), DCFileList.end());
        std::sort(RFFileList.begin(), RFFileList.end());

        // Break out the lists into vectors ordered by scan number
        int scanNo = 0;
        std::vector<std::vector<std::string>> DCScanList;
        std::vector<std::vector<std::string>> RFScanList;
        std::vector<std::string> tempDCList;
        std::vector<std::string> tempRFList;
        bool scanIncremented = false;
        for(int i = 0; i < DCFileList.size(); i++)
        {
            std::string scanString = std::format("{0:02}", scanNo);
            std::string scanPattern = "DC-" + scanString;
            if(DCFileList[i].find(scanPattern.c_str()) != std::string::npos)
            {
                tempDCList.push_back(DCFileList[i]);
                tempRFList.push_back(RFFileList[i]);
            } else {
                if(tempDCList.size() != 0)
                {
                    DCScanList.push_back(tempDCList);
                    RFScanList.push_back(tempRFList);
                    tempDCList.clear();
                    tempRFList.clear();
                    scanNo++;
                    scanIncremented = true;
                }

                if(scanIncremented)
                {
                    tempDCList.push_back(DCFileList[i]);
                    tempRFList.push_back(RFFileList[i]);
                    scanIncremented = false;
                }
            }
        }
        DCScanList.push_back(tempDCList);
        RFScanList.push_back(tempRFList);
    }

    private:
    std::vector<std::string> DCFileList;
    std::vector<std::string> RFFileList;
};

#endif /* WFMCOLLECTION_H */
