option(QTBuild "Set ON to develop QTBuild" ON)

if(QTBuild AND NOT APPLE)

cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(Tidalwave_InterfaceApp LANGUAGES CXX)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(custom_interfaces REQUIRED)
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
elseif(NOT QTBuild AND NOT APPLE)
cmake_minimum_required(VERSION 3.8)
project(Tidalwave_InterfaceApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(std_srvs REQUIRED)
add_executable(tidalwave_ros2_only Backend/ros2.cpp)
 ament_target_dependencies(tidalwave_ros2_only
        rclcpp 
        custom_interfaces 
        std_srvs
    )
install(TARGETS tidalwave_ros2_only DESTINATION lib/tidalwave_ros2_only)
OPTION(ROS2ONLY "only run the ros2 parts" ON)
add_compile_definitions(ROS2ONLY)
ament_package()
elseif(QTBuild)
    cmake_minimum_required(VERSION 3.21.1)

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
endif()