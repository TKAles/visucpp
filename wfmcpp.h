#ifndef WFMCPP_H
#define WFMCPP_H
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <numeric>
class WFMFile
{
    public:
        std::string WFMVersion;
        int ParseWFMFile(std::string filename);
        double GetSecondsResolution();
        double GetVoltageScale();
        int GetPoints();
        int GetFastFrames();
        void ComputeDCAverage();
        void ComputeFFT();
        std::vector<std::vector<double>> ScaledData;
        std::vector<double> DCAverages;


    private:
        bool chattyKathy = false;
        long curveDataStartOffset;
        int bytesPerSample;
        u_int32_t numberOfFastFrames;
        double voltageScale;
        double voltageOffset;
        int curveDataFormat;
        double timeScale;
        double timeOffset;
        ulong curveRecordLength;
        std::vector<double> timeStamps;
        std::vector<std::vector<int>> fastFrameRecordsRaw;
};
#endif /* WFMCPP_H */
