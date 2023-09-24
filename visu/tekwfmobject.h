#ifndef TEKWFMOBJECT_H
#define TEKWFMOBJECT_H
#include <string>
#include <fstream>
class TekWFMObject
{
public:
    TekWFMObject();
    int ParseWFMFile(std::string _wfmpath);
    std::string WFMVersion;

};

#endif // TEKWFMOBJECT_H
