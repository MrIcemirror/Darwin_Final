cmake_minimum_required(VERSION 3.16...3.20 FATAL_ERROR)
set(CXX_STANDARD_REQUIRED 17)

project(Darwin_PS)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#find root
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)
include(${ROOT_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)



add_executable(Darwin_PS Darwin_PS.cc ${sources} ${headers})
target_link_libraries(Darwin_PS ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

add_custom_target(Simulation DEPENDS Darwin_shielding_main)
