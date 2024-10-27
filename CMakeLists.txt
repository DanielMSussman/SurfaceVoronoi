cmake_minimum_required(VERSION 3.19)
project(surfaceVoronoi)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package (Eigen3 3.3 REQUIRED)
find_package(CGAL REQUIRED)
set(CMAKE_BUILD_TYPE "Release")

#The first block of stuff is just a simple conversion to cmake of the existing repo
set(MODEL3D_SRC_DIR ${PROJECT_SOURCE_DIR}/Model3D)
set(GEODESIC_SRC_DIR ${PROJECT_SOURCE_DIR}/Geodesic)
set(GVD_RVD_SRC ${PROJECT_SOURCE_DIR}/GVD_RVD)


file(GLOB MODEL_SOURCES ${MODEL3D_SRC_DIR}/*.cpp)
file(GLOB GEODESIC_SOURCES ${GEODESIC_SRC_DIR}/*.cpp)
file(GLOB GVD_RVD_SOURCES ${GVD_RVD_SRC}/*.cpp)

# Libraries
add_library(Model3D STATIC ${MODEL_SOURCES})
add_library(Geodesic STATIC ${GEODESIC_SOURCES})
target_include_directories(Model3D PRIVATE ${MODEL3D_SRC_DIR} )
target_include_directories(Geodesic PRIVATE ${GEODESIC_SRC_DIR})
target_link_libraries(Model3D PRIVATE gmp mpfr Eigen3::Eigen)
target_link_libraries(Geodesic PRIVATE gmp mpfr Eigen3::Eigen)

add_executable(GVD_RVD ${GVD_RVD_SOURCES})
# add_compile_options(-g)
target_include_directories(GVD_RVD PRIVATE ${MODEL3D_SRC_DIR} ${GEODESIC_SRC_DIR} ${MAIN_SRC_DIR})
target_link_libraries(GVD_RVD PRIVATE Model3D Geodesic gmp mpfr Eigen3::Eigen)

#Now, let's also build our sample geodesictVoronoiDiagram executable

add_executable(geodesicVoronoi ${CMAKE_SOURCE_DIR}/geodesicVoronoi.cpp)
target_include_directories(geodesicVoronoi PRIVATE ${MODEL3D_SRC_DIR} ${GEODESIC_SRC_DIR} ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(geodesicVoronoi PRIVATE Model3D Geodesic gmp mpfr Eigen3::Eigen)

# configure_file(${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json COPYONLY)
add_custom_command(
        TARGET geodesicVoronoi POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
                ${CMAKE_SOURCE_DIR}/compile_commands.json
)
