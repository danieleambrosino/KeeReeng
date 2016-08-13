set(SOURCES
    core/Crypto.cpp
    core/Database.cpp
    core/Entry.cpp)

set(HEADERS
    core/Crypto.h
    core/Database.h
    core/Entry.h)

set(FORMS)

add_library(core STATIC ${SOURCES} ${HEADERS})
target_link_libraries(core
                      Qt5::Core)

add_executable(KeeReeng main.cpp)
target_link_libraries(KeeReeng
                      core)