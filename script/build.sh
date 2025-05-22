#!/bin/bash

# 获取脚本所在目录的绝对路径
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# 清理函数
clean_build() {
    echo "Cleaning build directory..."
    rm -rf "$PROJECT_ROOT/build"
}

# 错误处理函数
error_exit() {
    echo "Error: $1"
    exit 1
}

# 处理命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -c|--clean)
            clean_build
            shift
            ;;
        *)
            error_exit "Unknown parameter: $1"
            ;;
    esac
done

# 创建并进入构建目录
echo "Creating build directory..."
mkdir -p "$PROJECT_ROOT/build" || error_exit "Failed to create build directory"
cd "$PROJECT_ROOT/build" || error_exit "Failed to enter build directory"

# 运行 CMake
echo "Running CMake..."
cmake .. || error_exit "CMake configuration failed"

# 编译项目
echo "Building project..."
make -j$(nproc) || error_exit "Build failed"

echo "Build completed successfully!"

# 运行测试程序（如果需要的话）
# if [ -f "source/test_eye" ]; then
#     echo "Running test program..."
#     ./source/test_eye
# fi