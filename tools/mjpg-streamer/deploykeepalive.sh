#!/bin/bash

###
# Deploys the keep alive scripts to the robot
###

ROBOT=$1

scp -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null keep_streamer_alive_bin admin@$ROBOT:/usr/local/bin/keep_streamer_alive
scp -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null keep-streamer-alive-initd admin@$ROBOT:/etc/init.d/keep-streamer-alive

ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null admin@$ROBOT chmod +x \
    /usr/local/bin/keep_streamer_alive \
    /etc/init.d/keep-streamer-alive \
    /etc/init.d/mjpg-streamer

ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null admin@$ROBOT '/sbin/ldconfig && /usr/sbin/update-rc.d -s keep-streamer-alive defaults 89'
