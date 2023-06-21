cmake_minimum_required(VERSION 3.5)

project(PhotoEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BOOST的设置
# 设置不使用静态库
set (Boost_USE_STATIC_LIBS OFF)
# 设置使用多线程库
set (Boost_USE_MULTITHREADED ON)
# 设置不使用静态运行时库
set (Boost_USE_STATIC_RUNTIME OFF)

set(OpenCV_DIR "D:/opencv/build")
set(Eigen3_DIR "F:/CodeLibrary/eigen/eigen-3.3.9/install/share/eigen3/cmake")
set(Qt_DIR $ENV{QT_DIR_5_15_2_MSVC2019_64})
set(BOOST_CODE_LIBRARY_PATH F:/CodeLibrary/boost_1_79_0)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${Qt_DIR}})
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${Qt_DIR}/bin)

set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${OpenCV_DIR}/include/opencv2)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${OpenCV_DIR}/bin)
set(OpenCV_ROOT ${OpenCV_DIR})

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    link_directories(${OpenCV_LIBRARY_DIRS})
    message(STATUS "OpenCV 库信息")
    message(STATUS "OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS}")
    message(STATUS "OpenCV_LIBRARY_DIRS=${OpenCV_LIBRARY_DIRS}")
endif()

# 添加boost路径
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${BOOST_CODE_LIBRARY_PATH})
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${BOOST_CODE_LIBRARY_PATH}/stage/lib)
set(BOOST_ROOT ${BOOST_CODE_LIBRARY_PATH})# 设置自己的路径

find_package(BOOST REQUIRED  COMPONENTS  system filesystem asio)
# target_link_libraries 需要在add_excutable后面
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS}) 
	link_directories(${Boost_LIBRARY_DIRS})
	message(STATUS "Boost 库信息:")
	message(STATUS "Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")
	message(STATUS "Boost_LIBRARY_DIRS=${Boost_LIBRARY_DIRS}")
endif()

# set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${Eigen3_DIR}/include)
# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${Eigen3_DIR}/share/eigen3/cmake)
set(Eigen3_ROOT ${Eigen3_DIR})

find_package(Eigen3 CONFIG REQUIRED)
if(Eigen3_FOUND)
    include_directories(${EIGEN3_INCLUDE_DIRS})
    message(STATUS "Eigen3 库信息")
    message(STATUS "Eigen3_INCLUDE_DIRS=${EIGEN3_INCLUDE_DIRS}")
 endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui)

set(PROJECT_SOURCES
        main.cpp
        photoeditormainwindow.cpp
        photoeditormainwindow.h
        photoeditormainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PhotoEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PhotoEditor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PhotoEditor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PhotoEditor
             ${PROJECT_SOURCES}
             "WorkSpace/workspace.h" 
             "WorkSpace/workspace.cpp" 
             "PhotoEditor/PhotoEditor.h" 
             "PhotoEditor/PhotoEditor.cpp" 
             "Image/Image.h" 
             "Image/Image.cpp" "Operator/Operator.h" "Thread/ThreadFactory.h" "Operator/OperatorFactory.h" "Error/error.h" "Operator/Operator.cpp" "Operator/OperatorQueue.h" "Operator/OperatorQueue.cpp" "Widget/PainterWidget.h")
    endif()
endif()

target_link_libraries(PhotoEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(PhotoEditor PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(PhotoEditor PRIVATE Qt${QT_VERSION_MAJOR}::Gui)

if(OpenCV_FOUND)
    target_link_libraries(PhotoEditor PUBLIC ${OpenCV_LIBRARIES})
endif()

if(Eigen3_FOUND)
    target_link_libraries(PhotoEditor PUBLIC Eigen3::Eigen)
endif()

if(Boost_FOUND)
	target_link_libraries(PhotoEditor PUBLIC ${BOOST_LIBRARIES})
endif()

set_target_properties(PhotoEditor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS PhotoEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PhotoEditor)
endif()
