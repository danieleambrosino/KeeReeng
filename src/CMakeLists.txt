set(SOURCES)

set(HEADERS)

set(FORMS)

add_library(core STATIC ${SOURCES} ${HEADERS})

add_executable(KeeReeng main.cpp)
target_link_libraries(KeeReeng
                      core)