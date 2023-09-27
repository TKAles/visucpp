#include "tekwfmobject.h"

TekWFMObject::TekWFMObject()
{

}

int TekWFMObject::ParseWFMFile(std::string _wfmpath)
{
    // Open the file
    std::fstream wfmFileStream;
    wfmFileStream.open(_wfmpath, std::ios::binary | std::ios::in);
    if(wfmFileStream.bad())
    {
        return -1;
    }
    // Check if there was an issue opening the file, otherwise
    // proceed.
    char wfmversion[8];
    wfmFileStream.seekg(0x002);
    wfmFileStream.get(wfmversion, 9);
    std::string wfmversionstr = wfmversion;
    // If the file isn't a v3 WFM, or the magic phrase doesn't appear
    // where expected, do not continue
    std::cout << wfmversion << std::endl;
    if(wfmversionstr.compare(":WFM#003") == 0)
    {
        // Valid version, add to object metadata and
        // continue parsing

        this->_WFMVersion = std::string(wfmversion);
    } else {
        // Abort if not a v3 file.
        return -2;
    }
    // Start the extraction of the metadata.
    wfmFileStream.seekg(0x00f);
    wfmFileStream.read(reinterpret_cast<char*>(&this->_BytesPerPoint), 1);
    uint16_t curveOffset;
    wfmFileStream.seekg(0x010);
    wfmFileStream.read(reinterpret_cast<char*>(&curveOffset), 4);
    char wfmLabel[32];
    wfmFileStream.seekg(0x028);
    wfmFileStream.get(wfmLabel, 32);
    this->_WaveformLabel = std::string(wfmLabel);
    // Check to see if this is a fast-frame dataset.
    bool isFastFrame;
    wfmFileStream.seekg(0x04e);
    wfmFileStream.read(reinterpret_cast<char*>(&isFastFrame), 1);
    this->_IsFastFrameSet = isFastFrame;
    // For now, this tool only supports fast-frames because that's
    // what my use case requires.
    if(this->_IsFastFrameSet == false)
    {
        return -3;
    }
    // Get the number of fast-frames in the file
    wfmFileStream.seekg(0x092, std::ios_base::beg);
    wfmFileStream.read(reinterpret_cast<char*>(&this->_NumOfFastFrames), 4);
    // Allocate the Waveforms vector to have a capacity equal to the number
    // of fast-frames in the file.
    this->Waveforms.reserve(this->GetNumberOfFrames());
    // Get the voltage scale and offset values
    wfmFileStream.seekg(0x0a8);
    wfmFileStream.read(reinterpret_cast<char*>(&this->_VoltageScale), 8);
    wfmFileStream.seekg(0x0b0);
    wfmFileStream.read(reinterpret_cast<char*>(&this->_VoltageOffset), 8);
    char _vu[20];
    wfmFileStream.seekg(0x0bc);
    wfmFileStream.read(_vu, 20);
    this->_VoltageUnits = std::string(_vu);
    // Get the timescale information
    wfmFileStream.seekg(0x1e8);
    wfmFileStream.read(reinterpret_cast<char*>(&this->_TimeScale), 8);
    wfmFileStream.seekg(0x1f0);
    wfmFileStream.read(reinterpret_cast<char*>(&this->_TriggerOffset), 8);
    wfmFileStream.seekg(0x1f8);
    wfmFileStream.read(reinterpret_cast<char*>(&this->_RecordLength), 4);
    //
    return 0;
}
// Getters for various private variables.
std::string TekWFMObject::WFMVersion()
{
    return this->_WFMVersion;
}
char TekWFMObject::BytesPerPoint()
{
    return this->_BytesPerPoint;
}
std::string TekWFMObject::WaveformLabel()
{
    return this->_WaveformLabel;
}
bool TekWFMObject::IsFastFrame()
{
    return this->_IsFastFrameSet;
}
uint16_t TekWFMObject::GetNumberOfFrames()
{
    return this->_NumOfFastFrames;
}
double TekWFMObject::GetVoltageOffset()
{
    return this->_VoltageOffset;
}
double TekWFMObject::GetVoltageScale()
{
    return this->_VoltageScale;
}
std::string TekWFMObject::GetVoltageUnits()
{
    return this->_VoltageUnits;
}
double TekWFMObject::GetTimescale()
{
    return this->_TimeScale;
}
double TekWFMObject::GetTriggerPosition()
{
    return this->_TriggerOffset;
}
uint16_t TekWFMObject::GetRecordLength()
{
    return this->_RecordLength;
}

