cmake_minimum_required(VERSION 3.23)
project(cpp_qt_wfh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt@5/5.15.7")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(cpp_qt_wfh main.cpp window.cpp window.h ThreadPool.cpp ThreadPool.h widgets/progress_widget.cpp widgets/progress_widget.h  worker/worker.cpp worker/worker.h utilities.cpp utilities.h widgets/lint_check_widget.cpp widgets/lint_check_widget.h)
target_link_libraries(cpp_qt_wfh
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

