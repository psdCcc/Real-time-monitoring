cmake_minimum_required(VERSION 3.1.0)

project(indoor_monitoring)

ADD_SUBDIRECTORY(DHT11)
ADD_SUBDIRECTORY(Camera)

ADD_EXECUTABLE(main main.cpp)

TARGET_LINK_LIBRARIES(main DHT11)
TARGET_LINK_LIBRARIES(main Camera)
