#!/bin/bash

# Copyright 2021 U.S. Department of Transportation, Federal Highway Administration

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

# http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

source /opt/ros/$ROS_DISTRO/setup.bash
cd ~/
catkin_make_isolated --install --only-pkg-with-deps c1t_vesc_driver -DCMAKE_BUILD_TYPE=Release
