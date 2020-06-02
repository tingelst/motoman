cmake_minimum_required(VERSION 3.5)
project(motoman_driver)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(simple_message REQUIRED)
# uncomment the following section in order to fill in further dependencies
# manually. find_package(<dependency> REQUIRED)

add_definitions(-DLINUXSOCKETS=1)  #use linux sockets for communication
add_definitions(-DROS=1)

set(MSG_SRC_FILES
    src/simple_message/messages/motoman_read_single_io_message.cpp
    src/simple_message/messages/motoman_read_single_io_reply_message.cpp
    src/simple_message/messages/motoman_write_single_io_message.cpp
    src/simple_message/messages/motoman_write_single_io_reply_message.cpp
    src/simple_message/motoman_motion_ctrl.cpp
    src/simple_message/motoman_motion_ctrl_message.cpp
    src/simple_message/motoman_motion_reply.cpp
    src/simple_message/motoman_motion_reply_message.cpp
    src/simple_message/motoman_read_single_io.cpp
    src/simple_message/motoman_read_single_io_reply.cpp
    src/simple_message/motoman_write_single_io.cpp
    src/simple_message/motoman_write_single_io_reply.cpp
    )

add_library(motoman_simple_message ${MSG_SRC_FILES})
target_include_directories(
  motoman_simple_message
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)
ament_target_dependencies(motoman_simple_message "simple_message")

# Causes the visibility macros to use dllexport rather than dllimport, which is
# appropriate when building the dll but not consuming it.
target_compile_definitions(motoman_simple_message PRIVATE
                           "MOTOMAN_DRIVER_BUILDING_LIBRARY")

install(DIRECTORY include/ DESTINATION include)
install(TARGETS motoman_simple_message
        EXPORT export_${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights uncomment
  # the line when a copyright and license is not present in all source files
  # set(ament_cmake_copyright_FOUND TRUE) the following line skips cpplint (only
  # works in a git repo) uncomment the line when this package is not in a git
  # repo set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)
ament_export_interfaces(export_${PROJECT_NAME})
ament_export_libraries(motoman_simple_message)

ament_package()
