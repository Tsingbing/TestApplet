aux_source_directory("./" DIR_SOURCE_SRCS)

set(LISIN_MTR1 "test_toml")
# 指定生成目标
# 指定生成目标文件夹




#判断debug模式
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message(STATUS "Debug mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/Debug)
else()
    message(STATUS "Release mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -std=c++11")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin//Release)
endif()
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/vehicle_fault.toml DESTINATION EXECUTABLE_OUTPUT_PATH)

message(STATUS "EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH}")
add_executable( ${LISIN_MTR1}
                ${DIR_SOURCE_SRCS}
              )

#头文件包含
target_include_directories(${LISIN_MTR1} PRIVATE
                           ${THIRLD_LIB_PATH}
                           )

#连接库
#target_link_libraries(${LISIN_MTR1} PUBLIC ${Mqtt_lib})

#执行文件的安装位置
#install(TARGETS ${LISIN_MTR1} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
