

class BLEEGGDevice : public BLEBioSensor {
public:
    using BLEBioSensor::BLEBioSensor;
    
    bool readData(SensorData& out_data) override {
        if (!is_connected_) return false;
        
        // 模拟8通道EEG数据
        out_data.values = { 
            -4.5f, 2.1f, 3.3f, -1.2f,
            0.7f, 5.4f, -3.0f, 2.8f
        };
        out_data.timestamp_ns = getTimestamp();
        return true;
    }
    
    DeviceInfo getInfo() const override {
        return {"NeuroSky_EEG", "EEG", 256.0f};
    }
};