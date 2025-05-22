#ifndef WRISTBAND_H
#define WRISTBAND_H

#include <string>
#include <chrono>
#include "../../../sensors/include/Sensor.h"

class BLEPPGDevice : public BioSensorDevice {
protected:
    bool is_connected_ = false;
    std::string mac_addr_;
    
    int64_t getTimestamp() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }
    
public:
    BLEPPGDevice(const std::string& mac_addr) : mac_addr_(mac_addr) {}
    
    bool connect() override {
        is_connected_ = true;  // 模拟连接
        return true;
    }
    
    bool readData(SensorData& out_data) override {
        if (!is_connected_) return false;
        
        // 模拟PPG数据
        out_data.values = {0.98f}; 
        out_data.timestamp_ns = getTimestamp();
        out_data.device_id = 1002;  // 为PPG设备指定一个ID
        return true;
    }
    
    void disconnect() override {
        is_connected_ = false;
        std::cout << "wristband disconnected\n";

    }
    
    DeviceInfo getInfo() const override {
        return {"Polar_PPG", "PPG", 128.0f};
    }
};

#endif // WRISTBAND_H