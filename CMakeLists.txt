# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)

# Requires OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# add executable
add_executable( ballDetection ballDetection.cpp )
add_executable( tracking tracking.cpp )
add_executable( ballDetectVideo ballDetectVideo.cpp )

# link libraries
target_link_libraries( ballDetection ${OpenCV_LIBS})
target_link_libraries( tracking ${OpenCV_LIBS})
target_link_libraries( ballDetectVideo ${OpenCV_LIBS})
