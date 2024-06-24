#ifndef WFMCOLLECTION_H
#define WFMCOLLECTION_H
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <format>
#include <matplot/matplot.h>
#include "wfmcpp.h"

class WFMCollection
{
    public:
        int FilesInCollection;
        int ScansInCollection;
        std::vector<std::vector<std::string>> DCScanList;
        std::vector<std::vector<std::string>> RFScanList;
        std::vector<std::vector<std::vector<double>>> DCValues;
        void SearchForWFMs(std::string searchPath);
        void ComputeDC();

    private:
    std::vector<std::string> DCFileList;
    std::vector<std::string> RFFileList;
};

#endif /* WFMCOLLECTION_H */
