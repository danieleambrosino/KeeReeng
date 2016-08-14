set(SOURCES
    core/Crypto.cpp
    core/Database.cpp
    gui/MainWindow.cpp
    gui/EnterPasswordDialog.cpp
    gui/EntryList.cpp
    gui/EntryDialog.cpp)

set(HEADERS
    core/Crypto.h
    core/Database.h
    core/Entry.h
    gui/MainWindow.h
    gui/EnterPasswordDialog.h
    gui/EntryList.h
    gui/EntryDialog.h)

add_library(core STATIC ${SOURCES} ${HEADERS})
target_link_libraries(core
                      Qt5::Core
                      Qt5::Widgets)

add_executable(KeeReeng main.cpp)
target_link_libraries(KeeReeng
                      core)