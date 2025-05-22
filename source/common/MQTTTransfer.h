#ifndef MQTT_TRANSFER_H
#define MQTT_TRANSFER_H

#include "DataTransfer.h"
#include <mosquitto.h>
#include <string>

class MQTTTransfer : public DataTransfer {
public:
    MQTTTransfer(const std::string& clientId);
    ~MQTTTransfer();

    bool connect(const std::string& host, int port) override;
    bool disconnect() override;
    bool sendData(const SensorData& data) override;
    bool isConnected() const override;

private:
    struct mosquitto* mosq;
    bool connected;
    std::string topic;
};

#endif // MQTT_TRANSFER_H
