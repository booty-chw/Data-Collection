#ifndef EGG_H
#define EGG_H

#include <string>
#include <chrono>
#include "../../../sensors/include/Sensor.h"

class BLEEGGDevice : public BioSensorDevice {
protected:
    bool is_connected_ = false;
    std::string mac_addr_;
    
    int64_t getTimestamp() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }
    
public:
    BLEEGGDevice(const std::string& mac_addr) : mac_addr_(mac_addr) {}
    
    bool connect() override {
        is_connected_ = true;  // 模拟连接
        return true;
    }
    
    bool readData(SensorData& out_data) override {
        if (!is_connected_) return false;
        
        // 模拟8通道EEG数据
        out_data.values = { 
            -4.5f, 2.1f, 3.3f, -1.2f,
            0.7f, 5.4f, -3.0f, 2.8f
        };
        out_data.timestamp_ns = getTimestamp();
        out_data.device_id = 1001;  // 为EEG设备指定一个ID
        return true;
    }
    
    void disconnect() override {
        is_connected_ = false;
        std::cout << "egg disconnected\n";
    }
    
    DeviceInfo getInfo() const override {
        return {"NeuroSky_EEG", "EEG", 256.0f};
    }
};

#endif // EGG_H