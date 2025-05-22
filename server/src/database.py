import sqlite3
from datetime import datetime

class DatabaseManager:
    def __init__(self, db_path):
        self.db_path = db_path
        self.conn = None
        self.init_database()
    
    def init_database(self):
        """初始化数据库连接和表结构"""
        self.conn = sqlite3.connect(self.db_path)
        cursor = self.conn.cursor()
        
        # 创建设备信息表
        cursor.execute('''
        CREATE TABLE IF NOT EXISTS devices (
            device_id INTEGER PRIMARY KEY,
            device_type TEXT,
            name TEXT,
            channels INTEGER,
            sampling_rate REAL,
            description TEXT,
            created_at DATETIME
        )
        ''')
        
        # 创建传感器数据表
        cursor.execute('''
        CREATE TABLE IF NOT EXISTS sensor_data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            timestamp DATETIME,
            device_id INTEGER,
            channel_number INTEGER,
            value REAL,
            FOREIGN KEY(device_id) REFERENCES devices(device_id)
        )
        ''')
        
        self.conn.commit()
    
    def save_sensor_data(self, timestamp, device_id, values):
        """保存传感器数据"""
        cursor = self.conn.cursor()
        for i, value in enumerate(values):
            cursor.execute(
                'INSERT INTO sensor_data (timestamp, device_id, channel_number, value) VALUES (?, ?, ?, ?)',
                (timestamp, device_id, i, value)
            )
        self.conn.commit()
    
    def register_device(self, device_id, device_type, name, channels, sampling_rate, description=""):
        """注册新设备"""
        cursor = self.conn.cursor()
        cursor.execute(
            'INSERT OR REPLACE INTO devices (device_id, device_type, name, channels, sampling_rate, description, created_at) VALUES (?, ?, ?, ?, ?, ?, ?)',
            (device_id, device_type, name, channels, sampling_rate, description, datetime.now())
        )
        self.conn.commit()
        cursor.execute(
            'INSERT OR REPLACE INTO devices (device_id, device_type, name, description, created_at) VALUES (?, ?, ?, ?, ?)',
            (device_id, device_type, name, description, datetime.now())
        )
        self.conn.commit()
    
    def query_data(self, device_id=None, start_time=None, end_time=None, limit=1000):
        """查询传感器数据
        
        Args:
            device_id: 设备ID（可选）
            start_time: 开始时间（可选）
            end_time: 结束时间（可选）
            limit: 返回的最大记录数
            
        Returns:
            list of tuples: (timestamp, device_id, channel_number, value)
        """
        cursor = self.conn.cursor()
        query = 'SELECT timestamp, device_id, channel_number, value FROM sensor_data'
        params = []
        conditions = []
        
        if device_id is not None:
            conditions.append('device_id = ?')
            params.append(device_id)
        
        if start_time:
            conditions.append('timestamp >= ?')
            params.append(start_time)
        
        if end_time:
            conditions.append('timestamp <= ?')
            params.append(end_time)
        
        if conditions:
            query += ' WHERE ' + ' AND '.join(conditions)
        
        query += ' ORDER BY timestamp DESC LIMIT ?'
        params.append(limit)
        
        cursor.execute(query, params)
        return cursor.fetchall()
    
    def get_device_info(self, device_id):
        """获取设备信息
        
        Args:
            device_id: 设备ID
            
        Returns:
            tuple: (device_type, name, channels, sampling_rate, description)
        """
        cursor = self.conn.cursor()
        cursor.execute(
            'SELECT device_type, name, channels, sampling_rate, description FROM devices WHERE device_id = ?',
            (device_id,)
        )
        return cursor.fetchone()
    
    def get_latest_data(self, device_id, channel=None, limit=1):
        """获取设备最新的数据
        
        Args:
            device_id: 设备ID
            channel: 通道编号（可选）
            limit: 返回的记录数量
            
        Returns:
            list of tuples: (timestamp, channel_number, value)
        """
        cursor = self.conn.cursor()
        query = 'SELECT timestamp, channel_number, value FROM sensor_data WHERE device_id = ?'
        params = [device_id]
        
        if channel is not None:
            query += ' AND channel_number = ?'
            params.append(channel)
        
        query += ' ORDER BY timestamp DESC LIMIT ?'
        params.append(limit)
        
        cursor.execute(query, params)
        return cursor.fetchall()
    
    def get_data_by_timerange(self, device_id, start_time, end_time, channels=None):
        """获取指定时间范围内的数据
        
        Args:
            device_id: 设备ID
            start_time: 开始时间
            end_time: 结束时间
            channels: 通道列表（可选，None表示所有通道）
            
        Returns:
            dict: {
                'timestamps': [时间戳列表],
                'channels': {
                    channel_number: [数值列表]
                }
            }
        """
        cursor = self.conn.cursor()
        query = '''
            SELECT timestamp, channel_number, value 
            FROM sensor_data 
            WHERE device_id = ? AND timestamp BETWEEN ? AND ?
        '''
        params = [device_id, start_time, end_time]
        
        if channels is not None:
            query += ' AND channel_number IN (' + ','.join('?' * len(channels)) + ')'
            params.extend(channels)
        
        query += ' ORDER BY timestamp ASC, channel_number ASC'
        cursor.execute(query, params)
        rows = cursor.fetchall()
        
        # 组织数据
        result = {'timestamps': [], 'channels': {}}
        current_timestamp = None
        
        for timestamp, channel, value in rows:
            if timestamp != current_timestamp:
                result['timestamps'].append(timestamp)
                current_timestamp = timestamp
            
            if channel not in result['channels']:
                result['channels'][channel] = []
            result['channels'][channel].append(value)
        
        return result
    
    def get_device_statistics(self, device_id, channel=None):
        """获取设备数据的统计信息
        
        Args:
            device_id: 设备ID
            channel: 通道编号（可选）
            
        Returns:
            dict: {
                'count': 记录总数,
                'min_value': 最小值,
                'max_value': 最大值,
                'avg_value': 平均值,
                'first_timestamp': 最早时间,
                'last_timestamp': 最新时间
            }
        """
        cursor = self.conn.cursor()
        query = '''
            SELECT 
                COUNT(*) as count,
                MIN(value) as min_value,
                MAX(value) as max_value,
                AVG(value) as avg_value,
                MIN(timestamp) as first_timestamp,
                MAX(timestamp) as last_timestamp
            FROM sensor_data 
            WHERE device_id = ?
        '''
        params = [device_id]
        
        if channel is not None:
            query += ' AND channel_number = ?'
            params.append(channel)
        
        cursor.execute(query, params)
        row = cursor.fetchone()
        
        return {
            'count': row[0],
            'min_value': row[1],
            'max_value': row[2],
            'avg_value': row[3],
            'first_timestamp': row[4],
            'last_timestamp': row[5]
        }
    
    def close(self):
        """关闭数据库连接"""
        if self.conn:
            self.conn.close()
