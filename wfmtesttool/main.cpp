#include <iostream>
#include <string>
#include "../visu/tekwfmobject.h"
#include "../visu/tekwfmobject.cpp"
using namespace std;

int main()
{
    // Set this to the file to use as the dummy test
    // file.
    std::string _testpath = "/home/tka/Documents/Layer028/DC-00-0001.wfm";

    cout << "WFM Parser Utility Test Suite." << endl;
    cout << "Using: " << endl
         << _testpath << " as the test file." << endl;
    TekWFMObject TestTekObject;
    auto retcode = TestTekObject.ParseWFMFile(_testpath);
    if(retcode != 0)
    {
        cout << "Problem opening test file." << endl
             << "return error was: " << retcode << endl;
    } else {
        cout << "WFM Version string reports as: "
             << TestTekObject.WFMVersion() << endl;
        cout << "Bytes Per Point: " << TestTekObject.BytesPerPoint() << endl;
        cout << "User Label: " << TestTekObject.WaveformLabel() << endl;
        cout << "Number of Frames in File: " << TestTekObject.GetNumberOfFrames() << endl;
        cout << "Voltage Scale: " << TestTekObject.GetVoltageScale() << "\tOffset: " << TestTekObject.GetVoltageOffset() << endl;
        cout << "Timebase information:" << endl << "Record Length: " << TestTekObject.GetRecordLength() << endl
             << "Time Scale: " << TestTekObject.GetTimescale() << "\tTrigger Position: " << TestTekObject.GetTriggerPosition() << endl;
    }
    return 0;
}
