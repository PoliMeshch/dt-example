cmake_minimum_required(VERSION 3.15)
project(Lab3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mylib STATIC
    src/my_string.cpp
    src/matrix.cpp
    src/worker_db.cpp
    src/notification.cpp
    src/notification_queue.cpp
    src/notification_priority_queue.cpp
    src/bool_array.cpp
    src/basefile.cpp
)

target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(tests)
