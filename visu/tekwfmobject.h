#ifndef TEKWFMOBJECT_H
#define TEKWFMOBJECT_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class TekWFMObject
{
public:
    TekWFMObject();
    int ParseWFMFile(std::string _wfmpath);
    std::string WFMVersion();
    int BytesPerPoint();
    std::string WaveformLabel();
    bool IsFastFrame();
    long NumberOfFastFrames();

    std::vector<std::vector<int>> Waveforms;

private:
    std::string _WFMVersion;
    int _BytesPerPoint;
    std::string _WaveformLabel;
    long _NumOfFastFrames;
    bool _IsFastFrameSet;

};

#endif // TEKWFMOBJECT_H
