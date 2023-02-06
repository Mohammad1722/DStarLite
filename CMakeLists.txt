cmake_minimum_required(VERSION 3.7)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)


project(DStarLiteVisualization CXX)

find_package(SFML COMPONENTS window graphics system)
# include_directories(${SDL2_INCLUDE_DIRS} src)

file(GLOB SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB INCLUDE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_executable(${PROJECT_NAME} 
    ${SRC_FILES}
    ${INCLUDE_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
)

# string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
# target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} -lpthread)
