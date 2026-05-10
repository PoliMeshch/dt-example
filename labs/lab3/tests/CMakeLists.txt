add_executable(test_notification_priority_queue test_notification_priority_queue.cpp)
target_link_libraries(test_notification_priority_queue PRIVATE mylib)
add_test(NAME test_notification_priority_queue COMMAND test_notification_priority_queue
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
