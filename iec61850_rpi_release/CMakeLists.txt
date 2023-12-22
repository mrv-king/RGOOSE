cmake_minimum_required(VERSION 3.10)
project(IEC61850_PROJ VERSION 1.0)

add_executable(iec61850 source/main.cpp)

IF (WIN32)
    FIND_PACKAGE(Boost 1.62.0 REQUIRED)
    FIND_PACKAGE(Python 3.11 COMPONENTS Interpreter Development)
	
    target_include_directories(iec61850 PUBLIC "${PROJECT_SOURCE_DIR}/headers;${PROJECT_SOURCE_DIR}/winpcap;${Boost_INCLUDE_DIRS};${Python_INCLUDE_DIRS}")
    target_link_libraries(iec61850 PRIVATE ${CMAKE_SOURCE_DIR}/iec61850lib/libIEC61850LIB.dll ${Python_LIBRARIES} -lws2_32)
	add_custom_command(TARGET iec61850 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/iec61850lib/libIEC61850LIB.dll ${CMAKE_CURRENT_BINARY_DIR}/libIEC61850LIB.dll)
ENDIF (WIN32)

IF (UNIX)
    SET(Include_DIR "${PROJECT_SOURCE_DIR}/headers;")
	
    FIND_PACKAGE(Boost 1.62.0 REQUIRED COMPONENTS system)
    FIND_PACKAGE(Python COMPONENTS Interpreter Development)

    target_include_directories(iec61850 PUBLIC "${Include_DIR};${Boost_INCLUDE_DIRS};${Python_INCLUDE_DIRS}")
    target_link_libraries(iec61850 PRIVATE ${CMAKE_SOURCE_DIR}/iec61850lib/libIEC61850LIB.so -lpthread -lboost_system ${Python_LIBRARIES})
	add_custom_command(TARGET iec61850 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/iec61850lib/libIEC61850LIB.so ${CMAKE_CURRENT_BINARY_DIR}/libIEC61850LIB.so)
ENDIF (UNIX)