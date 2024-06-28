#include "wfmcpp.h"

int WFMFile::ParseWFMFile(std::string filename)
        {
            // Open the file. Return -1 on any kind of I/O error
            std::ifstream WFMFileStream(filename, 
                std::ios::binary | std::ios::in);
            if (!WFMFileStream.is_open()) {
                std::cerr << "Failed to open file" << std::endl;
                return -1;
            }

            // Read WFM Version
            char wfmVersion[9];
            WFMFileStream.seekg(2);
            WFMFileStream.read(wfmVersion, 8);
            wfmVersion[8] = '\0';
            // If the WFM version isn't 3.0 return -1
            this->WFMVersion = std::string(wfmVersion);
            if(this->WFMVersion != std::string(":WFM#003"))
            {
                std::cerr << "This only supports version 3 WFM files!"
                    << std::endl;
                return -1;
            }
            // Determine how many bytes each sample occupies
            char bytesPerPointC[1];
            WFMFileStream.seekg(0x00f, std::ios::beg);
            WFMFileStream.read(bytesPerPointC, 1);
            this->bytesPerSample = static_cast<int>(*bytesPerPointC);

            // Extract the curve data start offset
            char curveDataStartOffsetC[4];
            u_int32_t curveDataStartOffsetBuffer;
            WFMFileStream.seekg(0x010, std::ios::beg);
            WFMFileStream.read(curveDataStartOffsetC, 4);
            std::memcpy(&curveDataStartOffsetBuffer, curveDataStartOffsetC, sizeof(curveDataStartOffsetBuffer));
            this->curveDataStartOffset = static_cast<u_long>(curveDataStartOffsetBuffer);

            // Extract the number of FastFrames in the file
            char numberOfFastFramesC[4];
            WFMFileStream.seekg(0x048, std::ios::beg);
            WFMFileStream.read(numberOfFastFramesC, 4);
            u_int32_t numberOfFastFramesBuffer;
            std::memcpy(&numberOfFastFramesBuffer, numberOfFastFramesC, sizeof(numberOfFastFramesBuffer));
            this->numberOfFastFrames = static_cast<u_long>(numberOfFastFramesBuffer);

            // Get the voltage scale out of the file
            char voltageScaleC[8];
            double voltageScaleBuffer;
            WFMFileStream.seekg(0x0a8, std::ios::beg);
            WFMFileStream.read(voltageScaleC, 8);
            std::memcpy(&voltageScaleBuffer, voltageScaleC, sizeof(voltageScaleBuffer));
            this->voltageScale = static_cast<double>(voltageScaleBuffer);

            // Get voltage offset
            char voltageOffsetC[8];
            double voltageOffsetBuffer;
            WFMFileStream.seekg(0x0b0, std::ios::beg);
            WFMFileStream.read(voltageOffsetC, 8);
            std::memcpy(&voltageOffsetBuffer, voltageOffsetC, sizeof(voltageOffsetBuffer));
            this->voltageOffset = static_cast<double>(voltageOffsetBuffer);

            // Get time resolution
            char timeScaleC[8];
            double timeScaleBuffer;
            WFMFileStream.seekg(0x1e8, std::ios::beg);
            WFMFileStream.read(timeScaleC, 8);
            std::memcpy(&timeScaleBuffer, timeScaleC, sizeof(timeScaleBuffer));
            this->timeScale = static_cast<double>(timeScaleBuffer);

            // Get offset / trigger position
            char timeOffsetC[8];
            double timeOffsetBuffer;
            WFMFileStream.seekg(0x1f0, std::ios::beg);
            WFMFileStream.read(timeOffsetC, 8);
            std::memcpy(&timeOffsetBuffer, timeOffsetC, sizeof(timeOffsetBuffer));
            this->timeOffset = static_cast<double>(timeOffsetBuffer);

            // Get Record Length (with pre/post charge)
            // this is in 'points' not bytes.
            char curveRecordLengthC[4];
            u_int32_t curveRecordLengthBuffer;
            WFMFileStream.seekg(0x1f8, std::ios::beg);
            WFMFileStream.read(curveRecordLengthC, 4);
            std::memcpy(&curveRecordLengthBuffer, curveRecordLengthC, sizeof(curveRecordLengthBuffer));
            this->curveRecordLength = static_cast<u_long>(curveRecordLengthBuffer);
            char prechargeC[4];
            char postchargeStartC[4];
            char postchargeEndC[4];
            char dataOffsetC[4];
            char dataTypeC[4];
            int dataType;
            int prechargePoints;
            int postchargePointsStart;
            int postchargePointsEnd;
            int dataOffset;
            WFMFileStream.seekg(0x332, std::ios::beg);
            WFMFileStream.read(prechargeC, 4);
            WFMFileStream.seekg(0x336, std::ios::beg);
            WFMFileStream.read(dataOffsetC, 4);
            WFMFileStream.seekg(0x33e, std::ios::beg);
            WFMFileStream.read(postchargeStartC, 4);
            WFMFileStream.seekg(0x33e, std::ios::beg);
            WFMFileStream.read(postchargeEndC, 4);
            std::memcpy(&prechargePoints, prechargeC, sizeof(prechargePoints));
            std::memcpy(&dataOffset, dataOffsetC, sizeof(dataOffset));
            std::memcpy(&postchargePointsStart, postchargeStartC, sizeof(postchargePointsStart));
            std::memcpy(&postchargePointsEnd, postchargeEndC, sizeof(postchargePointsEnd));
            int postchargeSize = postchargePointsEnd - postchargePointsStart;
            WFMFileStream.seekg(0x0f0, std::ios::beg);
            WFMFileStream.read(dataTypeC, 4);
            std::memcpy(&dataType, dataTypeC, sizeof(dataType));
            // This block is to print debug information to stdout. To enable
            // set ChattyKathy to true in the header file.
            if(this->chattyKathy)
            {
                std::cout << "CHATTY KATHY MODE ENABLED!" << std::endl;
                std::cout << "Data Type is " << dataType << std::endl;
                std::cout << "Bytes per point: " <<
                    this->bytesPerSample << std::endl;
                std::cout << "Curve data start offset: " <<
                    this->curveDataStartOffset << std::endl;
                int calcOffset = 838 + (this->numberOfFastFrames * 54);
                std::cout << "Calculated curve data start offset:" << calcOffset << std::endl;
                std::cout << "Number of fast frames: " <<
                    this->numberOfFastFrames << std::endl;
                std::cout << "Voltage scale: " <<
                    this->voltageScale << std::endl;
                std::cout << "Voltage offset: " <<
                    this->voltageOffset << std::endl;
                std::cout << "Time scale: " <<
                    this->timeScale << std::endl;
                std::cout << "Time offset: " <<
                    this->timeOffset << std::endl;
                std::cout << "Curve record length: " <<
                    this->curveRecordLength << std::endl;
                std::cout << "Precharge Size is " << prechargePoints <<
                " Postcharge size is " << postchargeSize << std::endl;
                std::cout << std::endl << std::endl <<
                "---------FASTFRAME INFORMATION--------" << std::endl;
            }

            const int rpBaseAddress = 0x310;
            const int ttBaseAddress = 0x314;
            const int fracBaseAddress = 0x31c;
            const int gmtBaseAddress = 0x324;
            const int updateSpecSize = 24;
            int curveObjectOffset;
            std::vector<u_int32_t> realPointsVector;
            std::vector<double> ttVector;
            std::vector<double> fracVector;
            std::vector<u_int32_t> gmtVector;
            // Extract header and timestamp information for each fast frame
            for (int i = 0 ; i < this->numberOfFastFrames ; i++)
            {
                char rpC[4];
                char ttC[8];
                char fracC[8];
                char gmtC[4];
                u_int32_t rpBuf;
                double ttBuf;
                double fracBuf;
                u_int32_t gmtBuf;
                if (i != 0)
                {
                    curveObjectOffset = 30;
                } else {
                    curveObjectOffset = 0;
                }
                WFMFileStream.seekg(rpBaseAddress + (i*updateSpecSize) + curveObjectOffset);
                WFMFileStream.read(rpC, 4);
                WFMFileStream.seekg(ttBaseAddress + (i*updateSpecSize)+ curveObjectOffset);
                WFMFileStream.read(ttC, 8);
                WFMFileStream.seekg(fracBaseAddress + (i*updateSpecSize)+ curveObjectOffset);
                WFMFileStream.read(fracC, 8);
                WFMFileStream.seekg(gmtBaseAddress + (i*updateSpecSize)+ curveObjectOffset);
                WFMFileStream.read(gmtC, 4);
                std::memcpy(&rpBuf, rpC, sizeof(rpBuf));
                realPointsVector.push_back(rpBuf);
                std::memcpy(&ttBuf, ttC, sizeof(ttBuf));
                ttVector.push_back(ttBuf);
                std::memcpy(&fracBuf, fracC, sizeof(fracBuf));
                fracVector.push_back(fracBuf);
                std::memcpy(&gmtBuf, gmtC, sizeof(gmtBuf));
                gmtVector.push_back(gmtBuf);
                if(this->chattyKathy)
                {
                    std::cout << i << ": RP: " << rpBuf << " TT: " << ttBuf 
                        << " FRAC: " << fracBuf << " GMT: " << gmtBuf << std::endl;
                }
            }

            // Extract the curve data and read it into the DCValues vector after
            // casting/processing
            for(int i = 0; i<this->numberOfFastFrames; i++)
            {
                int baseAddr = this->curveDataStartOffset + (i * this->curveRecordLength);
                char recordC[this->curveRecordLength];
                int8_t record[this->curveRecordLength];
                WFMFileStream.seekg(baseAddr);
                WFMFileStream.read((char*)recordC, this->curveRecordLength * sizeof(int8_t));
                std::memcpy(record, recordC, this->curveRecordLength * sizeof(int8_t));
                std::vector<int> recordVector(record, record + this->curveRecordLength);
                this->fastFrameRecordsRaw.push_back(recordVector);

            }

            // Scale the data by the voltage resolution and add the voltage offset
            for (auto &row : this->fastFrameRecordsRaw)
            {
                std::vector<double> tempRow;
                for (auto &column : row)
                {
                    tempRow.push_back(static_cast<double>(column) * this->voltageScale + this->voltageOffset);
                }
                this->ScaledData.push_back(tempRow);
            }

            // Close the file and exit.
            WFMFileStream.close();
            return 0;
        }
/**
 * @brief WFMFile::GetFastFrames
 * @return Returns an integer representing the number of fastframes in the dataset.
 */
int WFMFile::GetFastFrames()
{
    return this->numberOfFastFrames;
}
/**
 * @brief WFMFile::ComputeDCAverage computes the average DC value for each fastframe in the
 *                                  WFM file.
 */
void WFMFile::ComputeDCAverage()
{
    if(this->ScaledData.size() == 0)
    {
        return;
    }
    this->DCAverages.clear();
    for (auto &pixel : this->ScaledData)
    {
        double voltageSum = std::accumulate(pixel.begin(), pixel.end(), 0.0);
        double voltageAverage = voltageSum / pixel.size();
        this->DCAverages.push_back(voltageAverage);
    }
    return;
}
/**
 * @brief WFMFile::GetSecondsResolution
 * @return Returns the sample timescale resolution in seconds. This value is for the time
 *         between adjacent samples of the same point, not the time between consecutive FastFrames.
 */
double WFMFile::GetSecondsResolution()
{
    return this->timeScale;
}

/**
 * @brief WFMFile::GetPoints
 * @return Returns the number points in each FastFrame
 */
int WFMFile::GetPoints()
{
    return this->curveRecordLength;
}
