find_package(Qt5Test 5.7 REQUIRED)

add_executable(CryptoTest CryptoTest.cpp)
target_link_libraries(CryptoTest core Qt5::Test)
add_test(NAME CryptoTest COMMAND CryptoTest)

add_executable(DatabaseTest DatabaseTest.cpp)
target_link_libraries(DatabaseTest core Qt5::Test)
add_test(NAME DatabaseTest COMMAND DatabaseTest)