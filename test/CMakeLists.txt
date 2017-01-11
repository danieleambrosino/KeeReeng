set(TEST_SOURCES
    core/CryptoTest.cpp
        core/DatabaseTest.cpp)

find_package(Qt5Test 5.7 REQUIRED)

add_executable(KeeReeng_test ${TEST_SOURCES})
target_link_libraries(KeeReeng_test
                      core
                      Qt5::Test)
add_test(NAME KeeReeng_test COMMAND KeeReeng_test)