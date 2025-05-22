#ifndef DATA_TRANSFER_H
#define DATA_TRANSFER_H

#include <string>
#include <memory>
#include "SensorStruct.h"

class DataTransfer {
public:
    virtual ~DataTransfer() = default;
    virtual bool connect(const std::string& host, int port) = 0;
    virtual bool disconnect() = 0;
    virtual bool sendData(const SensorData& data) = 0;
    virtual bool isConnected() const = 0;
};

#endif // DATA_TRANSFER_H
