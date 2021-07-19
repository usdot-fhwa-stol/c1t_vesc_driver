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

FROM usdotfhwastoldev/carma-base:noetic-f1tenth-develop

RUN mkdir ~/src
COPY --chown=carma . /home/carma/src/
RUN ~/src/docker/checkout.bash
RUN ~/src/docker/install.sh

FROM usdotfhwastoldev/carma-base:noetic-f1tenth-develop

ARG BUILD_DATE="NULL"
ARG VCS_REF="NULL"
ARG VERSION="NULL"

LABEL org.label-schema.schema-version="1.0"
LABEL org.label-schema.name="CARMA"
LABEL org.label-schema.description="Binary application for the CARMA Platform"
LABEL org.label-schema.vendor="Leidos"
LABEL org.label-schema.version=${VERSION}
LABEL org.label-schema.url="https://highways.dot.gov/research/research-programs/operations/CARMA"
LABEL org.label-schema.vcs-url="https://github.com/usdot-fhwa-stol/c1t_vesc_driver"
LABEL org.label-schema.vcs-ref=${VCS_REF}
LABEL org.label-schema.build-date=${BUILD_DATE}

COPY --from=setup /home/carma/install_isolated /opt/carma/install

CMD ["roslaunch", "c1t_vesc_driver", "c1t_vesc_driver.launch"]
