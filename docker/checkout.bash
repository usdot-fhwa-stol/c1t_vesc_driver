#!/bin/bash

# CMARA dependencies
vcs import --input src/carma-msgs.repos src/
vcs import --input src/carma-utils.repos src/

# Autoware dependencies
vcs import --input src/autoware-messages.repos src/

# F1/10 VESC dependencies
vcs import --input src/vesc.repos src/
