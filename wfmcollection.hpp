#ifndef WFMCOLLECTION_H
#define WFMCOLLECTION_H
#include <vector>
#include <string>
#include <iostream>
#include <thread>
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
        double AverageDCRow(std::vector<double>);
        void ComputeDC();
        void ComputeDCAverage_mp(std::vector<std::vector<std::string>>& _fileset);

    private:
    std::vector<std::string> DCFileList;
    std::vector<std::string> RFFileList;
    void DCAverageOperation_mp(std::vector<std::string>& _DCSampleFilename,
                               std::vector<double>& result);

};

#endif /* WFMCOLLECTION_H */
