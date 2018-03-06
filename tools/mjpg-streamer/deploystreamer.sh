#!/bin/bash

###
# Deploys mjpg-streamer to the robot
###

ROBOT=$1

python3 opkginstaller.py install-opkg --robot $ROBOT mjpg-streamer v4l-utils

scp -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null mjpg-streamer admin@$ROBOT:/etc/default/mjpg-streamer
scp -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null mjpg-streamer-initd admin@$ROBOT:/etc/init.d/mjpg-streamer

ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null admin@$ROBOT 'v4l2-ctl -c focus_auto=0'
