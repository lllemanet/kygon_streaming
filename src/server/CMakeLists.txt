set(SERVER_TARGET ${PROJECT_NAME}-server)

add_executable(${SERVER_TARGET} main.cpp)

target_link_libraries(${SERVER_TARGET} PRIVATE Qt6::Network)
