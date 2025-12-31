add_executable(testMyMatrix tests.cpp)
add_test(NAME unitTests COMMAND testMyMatrix)
target_link_libraries(testMyMatrix PRIVATE MyMatrix)
target_link_directories(testMyMatrix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)