#include <iostream>
#include <chrono>
#include <Sensor.h>



class USBEyeTracker : public BioSensorDevice {
public:
    USBEyeTracker(uint16_t vid, uint16_t pid) 
        : vid_(vid), pid_(pid) {}
    
    bool connect() override {
        // 使用hidapi库实现USB HID连接
        // hid_open(vid_, pid_, nullptr);
        std::cout << "USB EyeTracker connected\n";
        return true;
    }
    
    bool readData(SensorData& out_data) override {
        // 模拟眼动坐标数据 (x,y,pupil_size)
        out_data.values = {0.5f, 0.8f, 3.2f}; 
        out_data.timestamp_ns = getTimestamp();
        return true;
    }
    
    void disconnect() override {
        std::cout << "USB EyeTracker disconnected\n";
    }
    
    DeviceInfo getInfo() const override {
        return {"EyeTracker_Pro", "EYE", 60.0f};
    }

private:
    uint16_t vid_, pid_;
    uint64_t getTimestamp() {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(
            system_clock::now().time_since_epoch()
        ).count();
    }
};