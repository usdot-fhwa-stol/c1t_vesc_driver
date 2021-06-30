# Copyright 2021 U.S. Department of Transportation, Federal Highway Administration
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
