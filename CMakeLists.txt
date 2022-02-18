cmake_minimum_required(VERSION 3.20)
project(Image_Morphology)

set(CMAKE_CXX_STANDARD 14)

#OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# include
include_directories(./Inc)

# SRC
aux_source_directory(./Src USER_SRC)

# Set the output folder where your program will be created
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# link_libraries
set(LINK_LIB
        ${OpenCV_LIBS}
        )

add_executable(Image_Morphology ${USER_SRC})
target_link_libraries(Image_Morphology ${LINK_LIB})

