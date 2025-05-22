#ifndef SensorStruct_h
#define SensorStruct_h


#include <cstdint>


struct SensorData {
    std::vector<float> values;      // 原始数据
    uint64_t timestamp_ns;          // 纳秒级时间戳
    uint32_t device_id;             // 设备唯一标识
};