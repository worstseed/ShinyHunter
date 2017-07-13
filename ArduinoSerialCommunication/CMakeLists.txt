cmake_minimum_required(VERSION 3.7)
project(ArduinoSerialCommunication)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SerialPort.cpp SerialPort.h RobotController.cpp RobotController.h RobotData.h)
add_executable(ArduinoSerialCommunication ${SOURCE_FILES})