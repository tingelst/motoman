cmake_minimum_required(VERSION 3.5)

project(motoman_gp25_support)

find_package(ament_cmake REQUIRED)

install(DIRECTORY config
                  launch
                  meshes
                  urdf
        DESTINATION share/${PROJECT_NAME})

ament_export_dependencies(urdf)
ament_package()
