set(SOURCES core/Crypto.cpp core/Crypto.h)

set(HEADERS)

set(FORMS)

add_library(core STATIC ${SOURCES} ${HEADERS})
target_link_libraries(core
                      Qt5::Core)

add_executable(KeeReeng main.cpp)
target_link_libraries(KeeReeng
                      core)