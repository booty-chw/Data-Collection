include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/sensors/include
)

# 查找必要的包
find_package(PkgConfig REQUIRED)
pkg_check_modules(MOSQUITTO REQUIRED libmosquitto)
find_package(nlohmann_json REQUIRED)

# 添加传感器库
add_library(sensors
    sensors/src/eye/eye.cpp
    sensors/src/egg/egg.cpp
    sensors/src/wristband/wristband.cpp
    common/MQTTTransfer.cpp
)

# 设置传感器库的包含目录和链接库
target_include_directories(sensors PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sensors/include
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${MOSQUITTO_INCLUDE_DIRS}
)

target_link_libraries(sensors PUBLIC
    ${MOSQUITTO_LIBRARIES}
    nlohmann_json::nlohmann_json
)

# 添加测试程序
add_executable(test_eye testCase/testEye.cpp)
target_link_libraries(test_eye PRIVATE sensors ${MOSQUITTO_LIBRARIES} nlohmann_json::nlohmann_json)

add_executable(test_egg testCase/testEgg.cpp)
target_link_libraries(test_egg PRIVATE sensors ${MOSQUITTO_LIBRARIES} nlohmann_json::nlohmann_json)

add_executable(test_wristband testCase/testWristband.cpp)
target_link_libraries(test_wristband PRIVATE sensors ${MOSQUITTO_LIBRARIES} nlohmann_json::nlohmann_json)

add_executable(test_all testCase/testAll.cpp)
target_link_libraries(test_all PRIVATE sensors ${MOSQUITTO_LIBRARIES} nlohmann_json::nlohmann_json)
