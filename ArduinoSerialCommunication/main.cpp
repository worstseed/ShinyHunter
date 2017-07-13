////////////////////////////////////////////////////Include libraries///////////////////////////////////////////////////
#include <iostream>
/////////////////////////////////////////////////////Include headers////////////////////////////////////////////////////
#include "SerialPort.h"
#include "RobotController.h"
/////////////////////////////////////////////////////////Pragmas////////////////////////////////////////////////////////
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
//////////////////////////////////////////////////////////Using/////////////////////////////////////////////////////////
using std::string;
using std::cout;
using std::endl;
using std::cin;
///////////////////////////////////////////////////////////Main/////////////////////////////////////////////////////////
int main()
{
    RobotController robotController;
    SerialPort arduino(robotController.PortName());
    // Check connection with Arduino
    if (arduino.isConnected())
        cout << "Connection Established" << endl;
    else
    {
        cout << "ERROR, check port name";
        return 1;
    }

    // TEST
    cout << "First" << endl;
    robotController.pressBtn_A(arduino);
    Sleep(4000);
    cout << "Second" << endl;
    robotController.pressBtn_A(arduino);
    Sleep(5000);
    cout << "Third" << endl;
    robotController.pressBtn_A(arduino);
    Sleep(5000);



//    Sleep(300);
//    robotController.unPressAllButtons(arduino);
//    Sleep(2000);


//    // Set control parameters
//    int softResetCount = 0;
//    int blackoutLim = 0;
//    char notShiny;
//
//    // Start
//    robotController.softReset(arduino);
//    Sleep(SOFT_RESET_TIME);
//
//    while (true)
//    {
//        // Talk
//        robotController.pressBtn_A(arduino);
//        Sleep(4000);
//        robotController.pressBtn_A(arduino);
//        Sleep(5000);
//        robotController.pressBtn_A(arduino);
//        Sleep(5000);
//
//        // Use this one for Ho-oh/Lugia and Hoen Legendaries
//        //pressBtn_A(arduino);
//        //Sleep(3000);
//
//        robotController.pressBtn_A(arduino);
//        Sleep(8000);
//
//        // Measure blackout time
//        robotController.bottomScreenLDR(arduino);
//        robotController.increaseTimeCurrent(8000);
//        cout << "Blackout Time:" << robotController.TimeCurrent() << endl;
//
//        // Set blackout time limit
//        if (!softResetCount)
//        {
//            blackoutLim = robotController.TimeCurrent() + 1000;
//            cout << "Blackout Limit will be set to " << blackoutLim << "mS" << endl;
//            cout << "Press enter to continue" << endl;
//            cin.ignore(2);
//        }
//
//        // Check if shiny, based on blackout time
//        if ((robotController.TimeCurrent() > blackoutLim) && (robotController.TimeCurrent() < 20000))
//        {
//            cout << "Shiny!!!!!!!!!!!!!!" << endl;
//            // TODO: buzzer
//            cout << "If this is not what you were looking for enter n" << endl;
//            cin >> notShiny;
//            cout << notShiny << endl;
//
//            if (notShiny == 110)
//                cout << "I feel a bit stupid...." << endl;
//            else
//                while (true) { }
//        }
//
//        softResetCount++;
//        cout << "Soft Resets:" << softResetCount << endl;
//
//        // Soft reset
//        robotController.softReset(arduino);
//        Sleep(SOFT_RESET_TIME);
//    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma clang diagnostic pop
///////////////////////////////////////////////////////////END//////////////////////////////////////////////////////////