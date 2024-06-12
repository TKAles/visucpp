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
        for(const auto& entry : DCFileList)
        {
            std::string scanString = std::format("{0:02}", scanNo);
            std::string scanPattern = "DC-" + scanString;
            
        }
    
    }

    private:
    std::vector<std::string> DCFileList;
    std::vector<std::string> RFFileList;
};

#endif /* WFMCOLLECTION_H */
