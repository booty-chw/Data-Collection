# Multi-Biosensor Data Collection System
# 多生物传感器数据采集系统

A complete solution for simultaneous data collection from multiple biosensors, supporting real-time data acquisition, transmission, and storage from devices suMQTT message format for all sensors:

这是一个用于同时采集多种生物传感器数据的完整解决方案，支持眼动仪、脑电图(EEG)和腕带(PPG)等设备的实时数据采集、传输和存储。

## Project Structure 项目结构

```
.
├── source/
│   ├── common/          # Common utilities and data structures
│   ├── sensors/         # Sensor device implementations
│   │   ├── include/    # Sensor interface definitions
│   │   └── src/        # Concrete sensor implementations
│   │       ├── eye/    # Eye tracker device
│   │       ├── egg/    # EEG device
│   │       └── wristband/ # Wristband device
│   └── testCase/       # Test cases
├── script/             # Build and utility scripts
├── server/            # Server implementation
│   ├── src/           # Server source code
│   └── README.md      # Server documentation
├── thirdParty/        # Third-party dependencies
└── build/             # Build output directory
```

## Supported Devices 支持的设备

- Eye Tracker (眼动仪)
- EEG Device (脑电图设备)
- Biosensor Wristband (生物传感器腕带)

## Database Structure 数据库结构

The system uses SQLite for data storage with the following schema:

```sql
-- Device registration table
CREATE TABLE devices (
    device_id INTEGER PRIMARY KEY,
    device_type TEXT,
    name TEXT,
    channels INTEGER,
    sampling_rate REAL,
    description TEXT,
    created_at DATETIME
);

-- Sensor data table
CREATE TABLE sensor_data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    timestamp DATETIME,
    device_id INTEGER,
    channel_number INTEGER,
    value REAL,
    FOREIGN KEY(device_id) REFERENCES devices(device_id)
);
```

## Data Transmission 数据传输

The system uses MQTT for real-time data transmission. Each sensor publishes data to specific topics:

- Eye Tracker: `sensors/eye/<device_id>/data`
- EEG: `sensors/eeg/<device_id>/data`
- Wristband: `sensors/wristband/<device_id>/data`

### MQTT Message Format

```json
{
    "device_id": "string",
    "timestamp": "ISO8601 string",
    "values": [ ]
}
```

## Build Instructions 构建说明

### Dependencies 依赖项

- CMake (>= 3.10)
- C++17 Compatible Compiler
  - Windows: Visual Studio 2019 or 2022
  - Linux: GCC 7.0 or higher
  - macOS: Clang 8.0 or higher
- MQTT Broker (Mosquitto)
- Python 3.7+
  - paho-mqtt
  - sqlite3

### Windows Build Steps Windows 构建步骤

1. Ensure Visual Studio 2019/2022 is installed (with C++ development tools)
   确保已安装 Visual Studio 2019 或 2022（需要包含 C++ 开发工具）
2. Install CMake (download from https://cmake.org/download/)
   安装 CMake（可从 https://cmake.org/download/ 下载）
3. Use build script:
   使用构建脚本：
   ```cmd
   # Normal build 普通构建
   script\build.bat

   # Clean and rebuild 清理并重新构建
   script\build.bat -c
   ```

### Linux/macOS Build Steps Linux/macOS 构建步骤

1. Using build script (recommended):
   使用构建脚本（推荐）：
   ```bash
   # Normal build 普通构建
   ./script/build.sh

   # Clean and rebuild 清理并重新构建
   ./script/build.sh -c
   ```

2. Manual build:
   手动构建：
   ```bash
   mkdir -p build
   cd build
   cmake ..
   make
   ```

### Server Setup 服务器设置

1. Install MQTT broker:
   安装 MQTT 服务器：
   ```bash
   sudo apt-get install mosquitto mosquitto-clients
   ```

2. Install Python dependencies:
   安装 Python 依赖：
   ```bash
   cd server
   pip install -r requirements.txt
   ```

3. Start the MQTT broker:
   启动 MQTT 服务器：
   ```bash
   sudo systemctl start mosquitto
   sudo systemctl enable mosquitto
   ```

4. Start the data collection server:
   运行数据采集服务器：
   ```bash
   cd server
   ./script/server.sh start
   ```

### Testing the System 测试系统

1. Run comprehensive test:
   运行综合测试：
   ```bash
   cd build/source
   ./test_all
   ```

2. Individual sensor tests:
   单个传感器测试：
   ```bash
   # Eye tracker test 眼动仪测试
   ./test_eye

   # EEG device test 脑电图测试
   ./test_egg

   # Wristband test 腕带测试
   ./test_wristband
   ```

### System Requirements 系统要求

- CPU: 2.0 GHz dual-core or better
- RAM: 4GB minimum, 8GB recommended
- Storage: 1GB free space
- USB ports for sensors
- Network connection for data transmission

### Sensor Specifications 传感器规格

1. Eye Tracker 眼动仪
   - Resolution: 0.1 degree
   - Sampling rate: 60 Hz
   - Channels: 3 (X, Y, Z coordinates)
   - Connection: USB (VID: 0x0483, PID: 0x5740)

2. EEG Device 脑电图设备
   - Channels: 8
   - Sampling rate: 256 Hz
   - Connection: Bluetooth LE
   - Battery life: 8 hours

3. PPG Wristband 生物传感器腕带
   - Channel: 1 (PPG)
   - Sampling rate: 128 Hz
   - Connection: Bluetooth LE
   - Battery life: 24 hours

### Data Format 数据格式

MQTT message format for all sensors:
所有传感器的 MQTT 消息格式：

```json
{
    "device_id": "string",
    "timestamp": "ISO8601 string",
    "values": ["", "", ""]
}
```

Database schema:
数据库结构：

```sql
-- Device registration table 设备注册表
CREATE TABLE devices (
    device_id INTEGER PRIMARY KEY,
    device_type TEXT,
    name TEXT,
    channels INTEGER,
    sampling_rate REAL,
    description TEXT,
    created_at DATETIME
);

-- Sensor data table 传感器数据表
CREATE TABLE sensor_data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    timestamp DATETIME,
    device_id INTEGER,
    channel_number INTEGER,
    value REAL,
    FOREIGN KEY(device_id) REFERENCES devices(device_id)
);
```

## Troubleshooting 故障排除

1. MQTT Connection Issues MQTT连接问题
   - Check if the MQTT broker is running: `systemctl status mosquitto`
   - Verify MQTT port (default 1883) is open: `netstat -an | grep 1883`
   - Check MQTT logs: `tail -f /var/log/mosquitto/mosquitto.log`

2. Device Connection Issues 设备连接问题
   - Check USB permissions (for eye tracker)
   - Verify Bluetooth is enabled (for EEG and wristband)
   - Check device battery level
   - Ensure correct device IDs are configured

3. Database Issues 数据库问题
   - Verify database file exists: `server/data/sensor_data.db`
   - Check file permissions
   - Run integrity check: `sqlite3 server/data/sensor_data.db "PRAGMA integrity_check;"`

4. Build Issues 编译问题
   - Verify CMake version: `cmake --version`
   - Check compiler version:
     ```bash
     g++ --version    # Linux
     clang++ --version # macOS
     ```
   - Ensure all dependencies are installed

## License 许可证

This project is licensed under the MIT License - see the LICENSE file for details.
本项目采用 MIT 许可证 - 详见 LICENSE 文件。

## Contributing 贡献

We welcome contributions! Please see CONTRIBUTING.md for guidelines.
我们欢迎贡献！请参阅 CONTRIBUTING.md 了解指南。
