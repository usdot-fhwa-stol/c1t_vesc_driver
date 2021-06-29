cmake_minimum_required(VERSION 3.0.2)
project(c1t_vesc_driver)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  cav_driver_utils
  cav_msgs
  vesc_ackermann
  vesc_driver
  vesc_msgs
  autoware_msgs
)

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp cav_driver_utils cav_msgs vesc_ackermann vesc_driver vesc_msgs autoware_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node 
  src/c1t_vesc_driver.cpp
  src/c1t_vesc_driver_node.cpp)

target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY 
  launch
  config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
