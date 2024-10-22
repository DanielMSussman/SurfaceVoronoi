cmake_minimum_required(VERSION 3.19)
project(surfaceVoronoi)

find_package (Eigen3 3.3 REQUIRED)

set(MODEL3D_SRC_DIR ${PROJECT_SOURCE_DIR}/Model3D)
set(GEODESIC_SRC_DIR ${PROJECT_SOURCE_DIR}/Geodesic)
set(GVD_RVD_SRC ${PROJECT_SOURCE_DIR}/GVD_RVD)

message(STATUS "Model3D source directory: ${MODEL3D_SRC_DIR}")

file(GLOB MODEL_SOURCES ${MODEL3D_SRC_DIR}/*.cpp)
file(GLOB GEODESIC_SOURCES ${GEODESIC_SRC_DIR}/*.cpp)
file(GLOB GVD_RVD_SOURCES ${GVD_RVD_SRC}/*.cpp)


add_library(Model3D STATIC ${MODEL_SOURCES})
add_library(Geodesic STATIC ${GEODESIC_SOURCES})

add_executable(GVD_RVD ${GVD_RVD_SOURCES})
# add_compile_options(-g)
target_include_directories(GVD_RVD PRIVATE ${MODEL3D_SRC_DIR} ${GEODESIC_SRC_DIR} ${MAIN_SRC_DIR})
target_link_libraries(GVD_RVD PRIVATE Model3D Geodesic gmp mpfr Eigen3::Eigen)


target_include_directories(Model3D PRIVATE ${MODEL3D_SRC_DIR} )
target_include_directories(Geodesic PRIVATE ${GEODESIC_SRC_DIR})

target_link_libraries(Model3D PRIVATE gmp mpfr Eigen3::Eigen)
target_link_libraries(Geodesic PRIVATE gmp mpfr Eigen3::Eigen)
