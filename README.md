# 多生物传感器数据采集系统

这是一个用于同时采集多种生物传感器数据的完整解决方案，支持眼动仪、脑电图(EEG)和腕带(PPG)等设备的实时数据采集、传输和存储。

## 项目结构

```
.
├── source/
│   ├── common/          # 通用数据结构和工具
│   ├── sensors/         # 传感器设备实现
│   │   ├── include/    # 传感器接口定义
│   │   └── src/        # 具体传感器实现
│   │       ├── eye/    # 眼动仪设备
│   │       ├── egg/    # 脑电图设备
│   │       └── wristband/ # 腕带设备
│   └── testCase/       # 测试用例
├── script/             # 构建和工具脚本
├── thirdParty/        # 第三方依赖
└── build/             # 构建输出目录
```

## 支持的设备

- 眼动仪 (Eye Tracker)
- 脑电图设备 (EEG)
- 生物传感器腕带 (Wristband)

## 构建说明

### 依赖项

- CMake (>= 3.10)
- C++17 兼容的编译器
  - Windows: Visual Studio 2019 或 2022
  - Linux: GCC 7.0 或更高版本
  - macOS: Clang 8.0 或更高版本

### Windows 构建步骤

1. 确保已安装 Visual Studio 2019 或 2022（需要包含 C++ 开发工具）
2. 安装 CMake（可从 https://cmake.org/download/ 下载）
3. 使用构建脚本：
   ```cmd
   # 普通构建
   script\build.bat

   # 清理并重新构建
   script\build.bat -c
   ```

### Linux/macOS 构建步骤

1. 使用构建脚本（推荐）：
   ```bash
   # 普通构建
   ./script/build.sh

   # 清理并重新构建
   ./script/build.sh -c
   ```

2. 手动构建：
   ```bash
   mkdir -p build
   cd build
   cmake ..
   make
   ```

## 使用示例

```cpp
#include <iostream>
#include "sensors/src/eye/eye.h"
#include "common/SensorStruct.h"

int main() {
    // 创建眼动仪实例
    USBEyeTracker eye(0x0483, 0x5740);
    
    if(eye.connect()) {
        SensorData eyedata;
        eye.readData(eyedata);
        std::cout << "Gaze X: " << eyedata.values[0] << std::endl;
        eye.disconnect();
    }
    return 0;
}
```

## 数据传输服务

### 服务端设置

1. 安装 MQTT 服务器：
   ```bash
   sudo apt-get install mosquitto mosquitto-clients
   ```

2. 安装 Python 依赖：
   ```bash
   pip3 install paho-mqtt
   ```

3. 启动 MQTT 服务器：
   ```bash
   sudo systemctl start mosquitto
   sudo systemctl enable mosquitto
   ```

4. 运行数据接收服务器：
   ```bash
   python3 script/server.py
   ```

### 数据格式

数据通过 MQTT 协议传输，使用 JSON 格式：

```json
{
    "timestamp_ns": 1234567890,
    "device_id": 1,
    "values": [0.5, 0.8, 3.2]
}
```

- `timestamp_ns`: 纳秒级时间戳
- `device_id`: 设备唯一标识
- `values`: 传感器数据数组

### MQTT 主题

- 传感器数据主题: `sensors/data`

## 开发说明

### 添加新的传感器设备

1. 在 `source/sensors/src` 下创建新的设备目录
2. 实现 `BioSensorDevice` 接口
3. 在 `source/CMakeLists.txt` 中添加新的源文件

## 许可证

[请添加许可证信息]

## 贡献指南

欢迎提交 Issue 和 Pull Request。
