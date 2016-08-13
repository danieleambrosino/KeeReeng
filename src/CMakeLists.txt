set(SOURCES
    core/Crypto.cpp
    core/Database.cpp
    gui/mainwindow.cpp
    gui/enterpassworddialog.cpp)

set(HEADERS
    core/Crypto.h
    core/Database.h
    core/Entry.h
    gui/mainwindow.h
    gui/enterpassworddialog.h)

add_library(core STATIC ${SOURCES} ${HEADERS})
target_link_libraries(core
                      Qt5::Core
                      Qt5::Widgets)

add_executable(KeeReeng main.cpp)
target_link_libraries(KeeReeng
                      core)