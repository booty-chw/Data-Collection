include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/sensors/include
)

# 添加传感器库
add_library(sensors
    sensors/src/eye/eye.cpp
    sensors/src/egg/egg.cpp
    sensors/src/wristband/wristband.cpp
)

# 设置传感器库的包含目录
target_include_directories(sensors PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sensors/include
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

# 添加测试程序
add_executable(test_eye testCase/test.cpp)
target_link_libraries(test_eye PRIVATE sensors)
