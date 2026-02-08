
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    "main.cpp"
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Qml)

if(ROS2ONLY)
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