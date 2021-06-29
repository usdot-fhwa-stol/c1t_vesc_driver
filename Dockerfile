FROM dustynv/ros:noetic-ros-base-l4t-r32.4.4 as setup

# Base image already has ros_base packages in this workspace
WORKDIR /workspace/ros_catkin_ws/
COPY . src/
RUN src/docker/checkout.bash
RUN src/docker/install.sh

FROM dustynv/ros:noetic-ros-base-l4t-r32.4.4

ARG BUILD_DATE="NULL"
ARG VERSION="NULL"
ARG VCS_REF="NULL"

COPY --from=setup /workspace/ros_catkin_ws/install_isolated /opt/ros/$ROS_DISTRO

CMD ["roslaunch", "c1t_vesc_driver", "c1t_vesc_driver.launch"]
