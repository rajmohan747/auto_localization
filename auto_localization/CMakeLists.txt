cmake_minimum_required(VERSION 2.8.3)
project(auto_localization)

add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
  
  geometry_msgs
  roscpp
  rospy
  std_msgs
  roslib


  

)










catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
    
    geometry_msgs
    roscpp
    rospy
    std_msgs

)
###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include/auto_localization
)


add_executable(auto_localization
  src/auto_localization.cpp
  src/ros_class.cpp

)

target_link_libraries(auto_localization
  ${catkin_LIBRARIES}
)
