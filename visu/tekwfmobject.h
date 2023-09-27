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
    double GetVoltageScale();
    double GetVoltageOffset();
    std::string GetVoltageUnits();
    double GetTimescale();
    double GetTriggerPosition();
    uint16_t GetRecordLength();


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
};

#endif // TEKWFMOBJECT_H
