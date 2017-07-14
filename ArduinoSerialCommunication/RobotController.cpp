////////////////////////////////////////////////////Include libraries///////////////////////////////////////////////////
#include <iostream>
/////////////////////////////////////////////////////Include headers////////////////////////////////////////////////////
#include "RobotController.h"
///////////////////////////////////////////////////////Send key/////////////////////////////////////////////////////////
void RobotController::sendKey(SerialPort &arduino, std::string sendString)
{
    char *c_string = new char[sendString.size() + 1];
    std::copy(sendString.begin(), sendString.end(), c_string);
    c_string[sendString.size()] = '\n';
    if(!arduino.writeSerialPort(c_string, MAX_DATA_LENGTH))
        std::cout << "Cannot write to Arduino" << std::endl;
    delete[] c_string;
}
////////////////////////////////////////////////////////Press A/////////////////////////////////////////////////////////
void RobotController::pressBtn_A(SerialPort &arduino)
{
    std::string sendString ("a");
    sendKey(arduino, sendString);
}
///////////////////////////////////////////////////////Soft Reset///////////////////////////////////////////////////////
void RobotController::softReset(SerialPort &arduino)
{
    std::string sendString ("S");
    sendKey(arduino, sendString);
}
/////////////////////////////////////////////////Un-press all buttons///////////////////////////////////////////////////
void RobotController::unPressAllButtons(SerialPort &arduino)
{
    std::string sendString ("0");
    sendKey(arduino, sendString);
}
///////////////////////////////////////////////////Take LDR reading/////////////////////////////////////////////////////
void RobotController::takeLDRReading(SerialPort &arduino)
{
    std::string sendString ("C");
    sendKey(arduino, sendString);
}
/////////////////////////////////////////////////Menage bottom screen///////////////////////////////////////////////////
void RobotController::bottomScreenLDR(SerialPort &arduino)
{
    byte b1 = 0;
    int LDR_Reading = 0;
    int LDR1, LDR2 = 0, LDR1_ave, LDR2_ave;
    int LDRn = 40;
    int LDR_ave[40] = {};
    int stepChange = 0;
    int LDR_Counter = 0;

    robotData.timeBegin = clock();
    while (true) {
        // Tell arduino to take a reading from the LDR and send first byte
        takeLDRReading(arduino);
        Sleep(30);
        // Read serial data from Arduino
        arduino.readSerialPort(output, MAX_DATA_LENGTH);

        b1 = (byte) output[0];
        LDR_Reading = 4 * (int) b1;

        for (int i = 0; i < (LDRn - 1); i++) {
            LDR_ave[i] = LDR_ave[i + 1];
        }
        LDR_ave[(LDRn - 1)] = LDR_Reading;

        if (LDR_Counter > (LDRn - 1)) {
            LDR1 = 0;
            LDR2 = 0;
            for (int i = 0; i < (LDRn / 2); i++) {
                LDR1 = LDR1 + LDR_ave[i];
            }
            for (int i = (LDRn / 2); i < LDRn; i++) {
                LDR2 = LDR2 + LDR_ave[i];
            }

            LDR1_ave = 2 * LDR1 / LDRn;
            LDR2_ave = 2 * LDR2 / LDRn;

            stepChange = abs(LDR2_ave - LDR1_ave);
        }

        if (stepChange > 10) {
            robotData.final_LDR = LDR_Reading;
            break;
        }

        robotData.timeCurrent = clock() - robotData.timeBegin;
        if (robotData.timeCurrent > robotData.timeLimit) {
            robotData.final_LDR = LDR2 / 3;
            break;
        }

        LDR_Counter++;
    }
}
///////////////////////////////////////////////////Access Port Name/////////////////////////////////////////////////////
char* RobotController::PortName()
{
    //return robotData.port_name; TODO
    return (char*) "\\.\\COM3";
}
/////////////////////////////////////////////////Access Time Current////////////////////////////////////////////////////
long RobotController::TimeCurrent()
{
    return robotData.timeCurrent;
}
/////////////////////////////////////////////////Increase Time Current//////////////////////////////////////////////////
void RobotController::increaseTimeCurrent(long term)
{
    robotData.timeCurrent += term;
}
///////////////////////////////////////////////////////////END//////////////////////////////////////////////////////////