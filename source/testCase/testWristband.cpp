#include <iostream>
#include <chrono>
#include <thread>
#include "../sensors/include/Sensor.h"
#include "../sensors/src/wristband/wristband.h"
#include "../common/SensorStruct.h"
#include "../common/MQTTTransfer.h"

int main() {
    std::cout << "Starting PPG data collection..." << std::endl;    

    // 创建腕带实例
    BLEPPGDevice ppg("00:11:22:33:44:55");  // 示例MAC地址
    
    // 创建MQTT传输实例
    MQTTTransfer transfer("ppg_client_1");
    
    // 连接到MQTT服务器
    if(!transfer.connect("localhost", 1883)) {
        std::cerr << "Failed to connect to MQTT broker" << std::endl;
        return -1;
    }
    
    // 连接腕带设备
    if(ppg.connect()) {
        std::cout << "Connected to PPG Device" << std::endl;
        
        // 持续采集和发送数据
        for(int i = 0; i < 100; ++i) { // 采集100次数据
            SensorData ppgdata;
            if(ppg.readData(ppgdata)) {
                // 发送数据到服务器
                if(transfer.sendData(ppgdata)) {
                    std::cout << "Data sent: PPG = " << ppgdata.values[0] << std::endl;
                } else {
                    std::cerr << "Failed to send data" << std::endl;
                }
            }
            
            // 等待10ms
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        ppg.disconnect();
    } else {
        std::cerr << "Failed to connect to PPG Device" << std::endl;
        return -1;
    }
    
    // 断开MQTT连接
    transfer.disconnect();
    return 0;
}
