#include <iostream>
#include <chrono>
#include <thread>
#include "../sensors/include/Sensor.h"
#include "../sensors/src/eye/eye.h"
#include "../common/SensorStruct.h"
#include "../common/MQTTTransfer.h"

int main() {
    std::cout << "Starting sensor data collection..." << std::endl;    

    // 创建眼动仪实例
    USBEyeTracker eye(0x0483, 0x5740);  // Example VID/PID values
    
    // 创建MQTT传输实例
    MQTTTransfer transfer("sensor_client_1");
    
    // 连接到MQTT服务器
    if(!transfer.connect("localhost", 1883)) {
        std::cerr << "Failed to connect to MQTT broker" << std::endl;
        return -1;
    }
    
    // 连接眼动仪
    if(eye.connect()) {
        std::cout << "Connected to Eye Tracker" << std::endl;
        
        // 持续采集和发送数据
        for(int i = 0; i < 100; ++i) { // 采集100次数据
            SensorData eyedata;
            if(eye.readData(eyedata)) {
                // 发送数据到服务器
                if(transfer.sendData(eyedata)) {
                    std::cout << "Data sent: Gaze X = " << eyedata.values[0] << std::endl;
                } else {
                    std::cerr << "Failed to send data" << std::endl;
                }
            }
            
            // 等待10ms
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        eye.disconnect();
    } else {
        std::cerr << "Failed to connect to Eye Tracker" << std::endl;
        return -1;
    }
    
    // 断开MQTT连接
    transfer.disconnect();
    return 0;
}