#!/usr/bin/env python3
import json
import os
import sys
import signal
from database import DatabaseManager
from mqtt_handler import MQTTHandler

def load_config():
    """加载配置文件"""
    config_path = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'config', 'config.json')
    with open(config_path, 'r') as f:
        return json.load(f)

def signal_handler(signum, frame):
    """信号处理函数"""
    print("\nShutting down server...")
    if 'mqtt_handler' in globals():
        mqtt_handler.stop()
    if 'db_manager' in globals():
        db_manager.close()
    sys.exit(0)

def main():
    # 加载配置
    config = load_config()
    
    # 设置信号处理
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)
    
    try:
        # 初始化数据库
        global db_manager
        db_path = os.path.join(os.path.dirname(os.path.dirname(__file__)), config['database']['path'])
        db_manager = DatabaseManager(db_path)
        
        # 初始化MQTT处理器
        global mqtt_handler
        mqtt_handler = MQTTHandler(config, db_manager)
        
        print("Starting sensor data collection server...")
        mqtt_handler.start()
        
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
