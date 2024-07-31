set(SERVER_TARGET ${PROJECT_NAME}-server)

qt_add_executable(${SERVER_TARGET}
    main.cpp
    ClientSession.cpp
    ClientsMediator.cpp
    Application.cpp
    ../common/Protocol.cpp
    ../common/UserDto.cpp
)

target_compile_definitions(${SERVER_TARGET} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
target_link_libraries(${SERVER_TARGET} PRIVATE Qt6::Network)
