cmake_minimum_required(VERSION 3.10)
project(linux-monitor-service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the executable
add_executable(monitor-service
    main.cpp
    "src /monitor/temperaure_reader.cpp"
)

# Add include directories
target_include_directories(monitor-service PRIVATE "src /monitor")
