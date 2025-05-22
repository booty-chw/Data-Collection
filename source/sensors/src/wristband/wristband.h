



class BLEPPGDevice : public BLEBioSensor {
public:
    using BLEBioSensor::BLEBioSensor;
    
    bool readData(SensorData& out_data) override {
        if (!is_connected_) return false;
        
        // 模拟单导联PPG信号
        out_data.values = {0.98f}; 
        out_data.timestamp_ns = getTimestamp();
        return true;
    }
    
    DeviceInfo getInfo() const override {
        return {"Polar_PPG", "PPG", 128.0f};
    }
};