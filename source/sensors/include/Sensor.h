#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include "common/SensorStruct.h"

class BioSensorDevice {
public:
    virtual ~BioSensorDevice() = default;
    
    // 连接设备
    virtual bool connect() = 0;
    
    // 读取数据（非阻塞）
    virtual bool readData(SensorData& out_data) = 0;
    
    // 断开连接
    virtual void disconnect() = 0;
    
    // 获取设备元数据
    struct DeviceInfo {
        std::string name;
        std::string type;
        float sampling_rate;
    };
    virtual DeviceInfo getInfo() const = 0;
};

#endif // SENSOR_H