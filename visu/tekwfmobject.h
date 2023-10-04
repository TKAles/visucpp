#ifndef TEKWFMOBJECT_H
#define TEKWFMOBJECT_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <arpa/inet.h>
class TekWFMObject
{
public:
    TekWFMObject();
    int ParseWFMFile(std::string _wfmpath);
    std::string WFMVersion();
    char BytesPerPoint();
    std::string WaveformLabel();
    bool IsFastFrame();
    uint16_t GetNumberOfFrames();

    std::vector<std::vector<uint16_t>> Waveforms;
    std::vector<std::vector<double>>Timestamps;
    double GetVoltageScale();
    double GetVoltageOffset();
    std::string GetVoltageUnits();
    double GetTimescale();
    double GetTriggerPosition();
    uint16_t GetRecordLength();
    std::vector<uint16_t> RealPointOffsets;
    std::vector<double> TriggerTimestampFraction;
    std::vector<double> FractionalSecond;
    std::vector<int32_t> GMTTimestamp;

private:
    std::string _WFMVersion;
    char _BytesPerPoint;
    std::string _WaveformLabel;
    bool _IsFastFrameSet;
    uint16_t _NumOfFastFrames;
    double _VoltageScale;
    double _VoltageOffset;
    std::string _VoltageUnits;
    double _TimeScale;
    double _TriggerOffset;
    uint16_t _RecordLength;
    enum _RecordType {
        EXPLICIT_INT16 = 0,
        EXPLICIT_INT32 = 1,
        EXPLICIT_UINT32 = 2,
        EXPLICIT_UINT64 = 3,
        EXPLICIT_FP32 = 4,
        EXPLICIT_FP64 = 5,
        EXPLICIT_INVALID_FORMAT = 8,
        EXPLICIT_UINT8 = 6,
        EXPLICIT_INT8 = 7,
        
    };
};

#endif // TEKWFMOBJECT_H
