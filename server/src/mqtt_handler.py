import paho.mqtt.client as mqtt
import json
from datetime import datetime
import logging

class MQTTHandler:
    def __init__(self, config, database):
        self.config = config
        self.database = database
        self.client = None
        self.setup_logging()
        self.registered_devices = set()
        
    def setup_logging(self):
        """设置日志"""
        self.logger = logging.getLogger('mqtt_handler')
        self.logger.setLevel(logging.INFO)
        
        # 添加文件处理器
        fh = logging.FileHandler(self.config['logging']['file'])
        fh.setLevel(logging.INFO)
        
        # 设置日志格式
        formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
        fh.setFormatter(formatter)
        self.logger.addHandler(fh)
    
    def register_device_if_needed(self, device_id, values):
        """注册设备（如果尚未注册）"""
        if device_id not in self.registered_devices:
            # 根据数据特征判断设备类型
            if len(values) == 8:
                self.database.register_device(
                    device_id, 
                    "EEG", 
                    "NeuroSky_EEG",
                    8,
                    256.0,
                    "8-channel EEG device"
                )
            elif len(values) == 3:
                self.database.register_device(
                    device_id,
                    "EyeTracker",
                    "Eye_Tracker",
                    3,
                    60.0,
                    "Eye tracking device (X, Y, Z coordinates)"
                )
            elif len(values) == 1:
                self.database.register_device(
                    device_id,
                    "PPG",
                    "Polar_PPG",
                    1,
                    128.0,
                    "Single channel PPG device"
                )
            self.registered_devices.add(device_id)
    
    def on_connect(self, client, userdata, flags, rc):
        """连接回调"""
        self.logger.info(f"Connected with result code {rc}")
        client.subscribe(self.config['mqtt']['topic'])
    
    def on_message(self, client, userdata, msg):
        """消息处理回调"""
        try:
            data = json.loads(msg.payload)
            timestamp = datetime.fromtimestamp(data['timestamp_ns'] / 1e9)
            
            # 检查并注册设备
            self.register_device_if_needed(data['device_id'], data['values'])
            
            self.logger.info(f"Received data at {timestamp} from device {data['device_id']}")
            
            # 保存到数据库
            self.database.save_sensor_data(
                timestamp,
                data['device_id'],
                data['values']
            )
            
        except json.JSONDecodeError:
            self.logger.error("Invalid JSON data received")
        except KeyError as e:
            self.logger.error(f"Missing key in data: {e}")
        except Exception as e:
            self.logger.error(f"Error processing message: {e}")
    
    def start(self):
        """启动MQTT客户端"""
        self.client = mqtt.Client(client_id=self.config['mqtt']['client_id'])
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        
        try:
            self.logger.info(f"Connecting to MQTT broker at {self.config['mqtt']['broker']}:{self.config['mqtt']['port']}")
            self.client.connect(self.config['mqtt']['broker'], self.config['mqtt']['port'], 60)
            self.client.loop_forever()
        except Exception as e:
            self.logger.error(f"Error starting MQTT client: {e}")
            raise
    
    def stop(self):
        """停止MQTT客户端"""
        if self.client:
            self.client.disconnect()
            self.logger.info("MQTT client disconnected")
