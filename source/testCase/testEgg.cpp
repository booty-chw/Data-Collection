#include <iostream>
#include <chrono>
#include <thread>
#include "../sensors/include/Sensor.h"
#include "../sensors/src/egg/egg.h"
#include "../common/SensorStruct.h"
#include "../common/MQTTTransfer.h"

int main() {
    std::cout << "Starting EEG data collection..." << std::endl;    

    // 创建脑电图实例
    BLEEGGDevice egg("24:71:89:cc:09:05");  // 示例MAC地址
    
    // 创建MQTT传输实例
    MQTTTransfer transfer("eeg_client_1");
    
    // 连接到MQTT服务器
    if(!transfer.connect("localhost", 1883)) {
        std::cerr << "Failed to connect to MQTT broker" << std::endl;
        return -1;
    }
    
    // 连接脑电图设备
    if(egg.connect()) {
        std::cout << "Connected to EEG Device" << std::endl;
        
        // 持续采集和发送数据
        for(int i = 0; i < 100; ++i) { // 采集100次数据
            SensorData eegdata;
            if(egg.readData(eegdata)) {
                // 发送数据到服务器
                if(transfer.sendData(eegdata)) {
                    std::cout << "Data sent: EEG CH1 = " << eegdata.values[0] << std::endl;
                } else {
                    std::cerr << "Failed to send data" << std::endl;
                }
            }
            
            // 等待10ms
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        egg.disconnect();
    } else {
        std::cerr << "Failed to connect to EEG Device" << std::endl;
        return -1;
    }
    
    // 断开MQTT连接
    transfer.disconnect();
    return 0;
}
