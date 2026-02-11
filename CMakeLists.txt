option(QTBuild "Set ON to develop QTBuild" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(ROS2 "Set ON to develop ROS" ON)
if(APPLE)
    option(ROS2 "Set to off" OFF)
endif()

############################################
if(QTBuild AND ROS2)
message("Normal build")
cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(Tidalwave_InterfaceApp LANGUAGES CXX)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(ament_cmake_gtest REQUIRED)
find_package(std_srvs REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Widgets Qml Quick QuickTimeline ShaderTools)
qt_standard_project_setup()


qt_add_executable(${CMAKE_PROJECT_NAME})
target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
       rclcpp 
        custom_interfaces 
        std_srvs 
        )
qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf)

include(qds)

if (BUILD_QDS_COMPONENTS)
    include(qmlcomponents OPTIONAL)
endif()

if (LINK_INSIGHT)
    include(insight OPTIONAL)
endif ()

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# -------------------------
# GoogleTest
# -------------------------
ament_add_gtest( testExec
    Backend/test/ROS2_ONLY/test_main.cpp
    Backend/test/QT_ONLY/test_main.cpp
    Backend/ros2.cpp
)
    if(TARGET testExec)
        ament_target_dependencies(testExec rclcpp  custom_interfaces 
        std_srvs)
    endif()
ament_package()

############################################

elseif(NOT QTBuild AND ROS2)
message("Only ros2 build")
cmake_minimum_required(VERSION 3.8)
project(Tidalwave_InterfaceApp)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(ament_cmake_gtest REQUIRED)
find_package(std_srvs REQUIRED)

OPTION(ROS2ONLY "only run the ros2 parts" ON)
add_compile_definitions(ROS2ONLY)
# -------------------------
# GoogleTest
# -------------------------
ament_add_gtest( ROS2_ONLY_test_exec
    Backend/test/ROS2_ONLY/test_main.cpp
    Backend/ros2.cpp
)
    if(TARGET ROS2_ONLY_test_exec)
        ament_target_dependencies(ROS2_ONLY_test_exec rclcpp  custom_interfaces 
        std_srvs)
    endif()
ament_package()

############################################

elseif(QTBuild) # ONLY QT BUILD
message("Only QT build")
    cmake_minimum_required(VERSION 3.21.1)
    OPTION(QTBUILDONLY "only run the QT code" ON)
    add_compile_definitions(QTBUILDONLY)
    option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
    option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

    project(Tidalwave_InterfaceApp LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Widgets Qml Quick QuickTimeline ShaderTools)
qt_standard_project_setup()


qt_add_executable(${CMAKE_PROJECT_NAME})

qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf)

include(qds)

if (BUILD_QDS_COMPONENTS)
    include(qmlcomponents OPTIONAL)
endif()

if (LINK_INSIGHT)
    include(insight OPTIONAL)
endif ()

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# -------------------------
# GoogleTest
# -------------------------
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS test/*.cpp) # ensures all the files in test are included
add_executable(MyTests ${TEST_SOURCES})

target_link_libraries(MyTests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(MyTests)
endif()