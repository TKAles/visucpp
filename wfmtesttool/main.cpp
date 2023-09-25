#include <iostream>
#include <string>
#include "../visu/tekwfmobject.h"
#include "../visu/tekwfmobject.cpp"
using namespace std;

int main()
{
    // Set this to the file to use as the dummy test
    // file.
    std::string _testpath = "/home/tka/Documents/Beta21S/L0/DC-00-0000.wfm";

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
    }
    return 0;
}
