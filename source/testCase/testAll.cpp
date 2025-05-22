#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include "../sensors/include/Sensor.h"
#include "../sensors/src/eye/eye.h"
#include "../sensors/src/egg/egg.h"
#include "../sensors/src/wristband/wristband.h"
#include "../common/SensorStruct.h"
#include "../common/MQTTTransfer.h"

// 辅助函数：打印传感器数据
void printSensorData(const std::string& sensorName, const SensorData& data) {
    std::cout << sensorName << " data: ";
    for (size_t i = 0; i < data.values.size(); ++i) {
        std::cout << data.values[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Starting comprehensive sensor data collection..." << std::endl;

    // 创建所有传感器实例
    USBEyeTracker eye(0x0483, 0x5740);
    BLEEGGDevice egg("24:71:89:cc:09:05");
    BLEPPGDevice ppg("00:11:22:33:44:55");

    // 创建MQTT传输实例
    MQTTTransfer transfer("multi_sensor_client");
    
    // 连接到MQTT服务器
    if(!transfer.connect("localhost", 1883)) {
        std::cerr << "Failed to connect to MQTT broker" << std::endl;
        return -1;
    }

    // 连接所有设备
    bool eye_connected = eye.connect();
    bool egg_connected = egg.connect();
    bool ppg_connected = ppg.connect();

    if (!eye_connected) std::cerr << "Failed to connect to Eye Tracker" << std::endl;
    if (!egg_connected) std::cerr << "Failed to connect to EEG Device" << std::endl;
    if (!ppg_connected) std::cerr << "Failed to connect to PPG Device" << std::endl;

    // 如果至少有一个设备连接成功，则开始数据采集
    if (eye_connected || egg_connected || ppg_connected) {
        std::cout << "Starting data collection from connected devices..." << std::endl;
        
        // 持续采集和发送数据
        for(int i = 0; i < 100; ++i) { // 采集100次数据
            // 采集眼动数据
            if (eye_connected) {
                SensorData eyedata;
                if(eye.readData(eyedata)) {
                    if(transfer.sendData(eyedata)) {
                        printSensorData("Eye", eyedata);
                    }
                }
            }

            // 采集脑电数据
            if (egg_connected) {
                SensorData eegdata;
                if(egg.readData(eegdata)) {
                    if(transfer.sendData(eegdata)) {
                        printSensorData("EEG", eegdata);
                    }
                }
            }

            // 采集PPG数据
            if (ppg_connected) {
                SensorData ppgdata;
                if(ppg.readData(ppgdata)) {
                    if(transfer.sendData(ppgdata)) {
                        printSensorData("PPG", ppgdata);
                    }
                }
            }

            // 等待10ms
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        // 断开所有设备连接
        if (eye_connected) eye.disconnect();
        if (egg_connected) egg.disconnect();
        if (ppg_connected) ppg.disconnect();
    } else {
        std::cerr << "No devices connected. Exiting..." << std::endl;
        return -1;
    }
    
    // 断开MQTT连接
    transfer.disconnect();
    return 0;
}
