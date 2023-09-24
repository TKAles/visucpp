#include "tekwfmobject.h"

TekWFMObject::TekWFMObject()
{

}
int TekWFMObject::ParseWFMFile(std::string _wfmpath)
{
    std::fstream wfmFileStream;

    wfmFileStream.open(_wfmpath);
    // Check if there was an issue opening the file, otherwise
    // proceed.
    char wfmversion[8];
    wfmFileStream.seekp(2);
    wfmFileStream.get(wfmversion, 8);
    this->WFMVersion = std::string(wfmversion);
    return 0;
}
