#include "MQTTTransfer.h"
#include <nlohmann/json.hpp>
#include <sstream>
#include <thread>
#include <chrono>

using json = nlohmann::json;

MQTTTransfer::MQTTTransfer(const std::string& clientId) {
    mosquitto_lib_init();
    mosq = mosquitto_new(clientId.c_str(), true, nullptr);
    connected = false;
    topic = "sensors/data";  // 设置默认的topic
}

MQTTTransfer::~MQTTTransfer() {
    if (connected) {
        disconnect();
    }
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

bool MQTTTransfer::connect(const std::string& host, int port) {
    if (mosquitto_connect(mosq, host.c_str(), port, 60) != MOSQ_ERR_SUCCESS) {
        return false;
    }
    
    // 启动MQTT网络循环
    if (mosquitto_loop_start(mosq) != MOSQ_ERR_SUCCESS) {
        return false;
    }
    
    connected = true;
    return true;
}

bool MQTTTransfer::disconnect() {
    if (!connected) return true;
    
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);
    connected = false;
    return true;
}

bool MQTTTransfer::sendData(const SensorData& data) {
    if (!connected) return false;

    // 将数据转换为JSON格式
    json j = {
        {"timestamp_ns", data.timestamp_ns},
        {"device_id", data.device_id},
        {"values", data.values}
    };
    
    std::string payload = j.dump();
    
    // 发送数据
    int rc = mosquitto_publish(mosq, nullptr, topic.c_str(),
                             payload.size(), payload.c_str(),
                             0, false);
    
    return rc == MOSQ_ERR_SUCCESS;
}

bool MQTTTransfer::isConnected() const {
    return connected;
}
