# 多生物传感器数据采集服务器

这是数据采集系统的服务器端实现，负责接收、存储和管理来自各种生物传感器的数据。

## 功能特性

- MQTT消息订阅和处理
- SQLite数据库存储
- 实时数据监控
- 灵活的数据查询API
- 设备自动注册和管理
- 日志记录和监控

## 目录结构

```
server/
├── config/              # 配置文件
│   └── config.json     # 主配置文件
├── data/               # 数据存储
│   └── sensor_data.db  # SQLite数据库
├── logs/               # 日志文件
│   └── server.log      # 服务器日志
├── script/             # 管理脚本
│   └── server.sh       # 服务器控制脚本
└── src/                # 源代码
    ├── database.py     # 数据库管理
    ├── mqtt_handler.py # MQTT处理
    └── main.py         # 主程序
```

## 数据库结构

### 设备表 (devices)

| 字段 | 类型 | 说明 |
|------|------|------|
| device_id | INTEGER | 设备ID（主键）|
| device_type | TEXT | 设备类型 |
| name | TEXT | 设备名称 |
| channels | INTEGER | 通道数量 |
| sampling_rate | REAL | 采样率(Hz) |
| description | TEXT | 设备描述 |
| created_at | DATETIME | 创建时间 |

### 传感器数据表 (sensor_data)

| 字段 | 类型 | 说明 |
|------|------|------|
| id | INTEGER | 记录ID（主键）|
| timestamp | DATETIME | 时间戳 |
| device_id | INTEGER | 设备ID（外键）|
| channel_number | INTEGER | 通道编号 |
| value | REAL | 数据值 |

## 配置说明

`config/config.json` 文件包含以下配置项：

```json
{
    "mqtt": {
        "broker": "localhost",
        "port": 1883,
        "topic": "sensors/data",
        "client_id": "sensor_server"
    },
    "database": {
        "type": "sqlite",
        "path": "data/sensor_data.db"
    },
    "logging": {
        "level": "INFO",
        "file": "logs/server.log"
    }
}
```

## 服务器管理

### 启动服务器
```bash
./script/server.sh start
```

### 停止服务器
```bash
./script/server.sh stop
```

### 查看状态
```bash
./script/server.sh status
```

## 数据查询API

### 基本查询
```python
from src.database import DatabaseManager

db = DatabaseManager('data/sensor_data.db')

# 查询最新数据
latest_data = db.get_latest_data(device_id=1001, channel=0)

# 查询时间范围内的数据
data = db.get_data_by_timerange(
    device_id=1001,
    start_time='2025-05-22 00:00:00',
    end_time='2025-05-22 23:59:59'
)

# 获取设备统计信息
stats = db.get_device_statistics(device_id=1001)
```

### 支持的查询功能

1. 获取最新数据 (`get_latest_data`)
   - 支持指定通道
   - 可限制返回记录数

2. 时间范围查询 (`get_data_by_timerange`)
   - 支持多通道数据
   - 返回结构化的数据格式

3. 统计信息查询 (`get_device_statistics`)
   - 记录数统计
   - 数值范围统计
   - 时间范围统计

## 错误处理

服务器日志文件 (`logs/server.log`) 记录了详细的运行信息和错误信息，包括：
- MQTT连接状态
- 数据接收记录
- 设备注册信息
- 错误和异常信息

## 依赖项

- Python 3.7+
- paho-mqtt
- sqlite3 (Python标准库)

## 安装步骤

1. 安装Python依赖：
```bash
pip install paho-mqtt
```

2. 安装MQTT代理服务器：
```bash
# Ubuntu/Debian
sudo apt-get install mosquitto mosquitto-clients

# CentOS/RHEL
sudo yum install mosquitto mosquitto-clients
```

3. 创建必要的目录：
```bash
mkdir -p data logs
```
