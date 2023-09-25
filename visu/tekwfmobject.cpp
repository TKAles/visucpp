#include "tekwfmobject.h"

TekWFMObject::TekWFMObject()
{

}

int TekWFMObject::ParseWFMFile(std::string _wfmpath)
{
    std::fstream wfmFileStream;

    wfmFileStream.open(_wfmpath);
    if(wfmFileStream.bad())
    {
        return -1;
    }
    // Check if there was an issue opening the file, otherwise
    // proceed.
    char wfmversion[8];
    wfmFileStream.seekp(0x002);
    wfmFileStream.read(wfmversion, 8);
    std::string wfmversionstr = std::string(wfmversion);
    // If the file isn't a v3 WFM, or the magic phrase doesn't appear
    // where expected, do not continue
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
    char bpp[1];
    wfmFileStream.seekp(0x00f);
    wfmFileStream.read(bpp, 1);
    this->_BytesPerPoint = static_cast<int>(*bpp);
    char curveOffset[4];
    wfmFileStream.seekp(0x010);
    wfmFileStream.read(curveOffset, 4);
    char wfmLabel[32];
    wfmFileStream.seekp(0x028, 32);
    this->_WaveformLabel = std::string(wfmLabel);
    // Check to see if this is a fast-frame dataset.
    char isFastFrame[1];
    wfmFileStream.seekp(0x04e);
    wfmFileStream.read(isFastFrame, 1);
    this->_IsFastFrameSet = static_cast<bool>(*isFastFrame);
    // For now, this tool only supports fast-frames because that's
    // what my use case requires.
    if(this->_IsFastFrameSet == false)
    {
        return -3;
    }

    return 0;
}

std::string TekWFMObject::WFMVersion()
{
    return this->_WFMVersion;
}

int TekWFMObject::BytesPerPoint()
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

long TekWFMObject::NumberOfFastFrames()
{
    return this->_NumOfFastFrames;
}
