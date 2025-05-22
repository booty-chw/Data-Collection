#!/bin/bash

# 获取脚本所在目录的绝对路径
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SERVER_ROOT="$(dirname "$SCRIPT_DIR")"

# 确保日志目录存在
mkdir -p "$SERVER_ROOT/logs"

# 检查 Python 环境
if ! command -v python3 &> /dev/null; then
    echo "Error: Python3 is not installed"
    exit 1
fi

# 检查必要的 Python 包
python3 -c "import paho.mqtt.client" 2>/dev/null || {
    echo "Installing paho-mqtt..."
    pip3 install paho-mqtt
}

# 函数：启动服务器
start_server() {
    echo "Starting sensor data collection server..."
    python3 "$SERVER_ROOT/src/main.py" > "$SERVER_ROOT/logs/server.log" 2>&1 &
    echo $! > "$SERVER_ROOT/server.pid"
    echo "Server started with PID $(cat "$SERVER_ROOT/server.pid")"
}

# 函数：停止服务器
stop_server() {
    if [ -f "$SERVER_ROOT/server.pid" ]; then
        PID=$(cat "$SERVER_ROOT/server.pid")
        if kill -0 "$PID" 2>/dev/null; then
            echo "Stopping server (PID: $PID)..."
            kill "$PID"
            rm "$SERVER_ROOT/server.pid"
        else
            echo "Server is not running"
            rm "$SERVER_ROOT/server.pid"
        fi
    else
        echo "Server is not running"
    fi
}

# 函数：检查服务器状态
status_server() {
    if [ -f "$SERVER_ROOT/server.pid" ]; then
        PID=$(cat "$SERVER_ROOT/server.pid")
        if kill -0 "$PID" 2>/dev/null; then
            echo "Server is running (PID: $PID)"
            echo "Recent logs:"
            tail -n 5 "$SERVER_ROOT/logs/server.log"
        else
            echo "Server is not running (stale PID file)"
            rm "$SERVER_ROOT/server.pid"
        fi
    else
        echo "Server is not running"
    fi
}

# 处理命令行参数
case "$1" in
    start)
        start_server
        ;;
    stop)
        stop_server
        ;;
    restart)
        stop_server
        sleep 2
        start_server
        ;;
    status)
        status_server
        ;;
    *)
        echo "Usage: $0 {start|stop|restart|status}"
        exit 1
        ;;
esac

exit 0
