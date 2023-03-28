file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.toml DESTINATION ${CMAKE_BINARY_DIR})

aux_source_directory("./" DIR_SOURCE_SRCS)


set(LISIN_MTR1 "test_toml")
# 指定生成目标
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
