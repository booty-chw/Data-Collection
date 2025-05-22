
#include <iostream>
#include "src/eye/eye.h"
#include "common/SensorStructs.h"

int main() {
    cout << "Hello, World!" << endl;    
    // Create an instance of the USBEyeTracker
    // USBEyeTracker eye = new USBEyeTracker();
    USBEyeTracker eye = std::make_unique<USBEyeTracker>();
    if(eye.connect())
    {
        std::cout << "Connected to Eye Tracker" << std::endl;
    }
    else
    {
        std::cerr << "Failed to connect to Eye Tracker" << std::endl;
        return -1;
    }
    eyedata = SensorData();
    eye.readData(eyedata);
    std::cout << "Gaze X: " << eyedata.values[0] << std::endl;
    eye.disconnect();
    return 0;
}