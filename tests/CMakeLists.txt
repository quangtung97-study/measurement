project(measurement-tests)


add_executable(test_main
    detail/element.cpp
    detail/math.cpp
    unit.cpp
)

target_link_libraries(test_main
    gmock_main
    pthread
)

add_test(NAME TestMain COMMAND test_main)
