#include <iostream>
#include <chrono>
#include "../sensors/include/Sensor.h"
#include "../sensors/src/eye/eye.h"
#include "../common/SensorStruct.h"

int main() {
    std::cout << "Hello, World!" << std::endl;    
    // Create an instance of the USBEyeTracker with vendor ID and product ID
    USBEyeTracker eye(0x0483, 0x5740);  // Example VID/PID values
    
    if(eye.connect())
    {
        std::cout << "Connected to Eye Tracker" << std::endl;
    }
    else
    {
        std::cerr << "Failed to connect to Eye Tracker" << std::endl;
        return -1;
    }

    SensorData eyedata;
    eye.readData(eyedata);
    std::cout << "Gaze X: " << eyedata.values[0] << std::endl;
    eye.disconnect();
    return 0;
}