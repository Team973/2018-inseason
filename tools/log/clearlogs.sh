#!/bin/bash

# Clear all the logfiles on the rio

TEAM_NUMBER=973
TARGET="roborio-$TEAM_NUMBER-frc.local"

ssh lvuser@$TARGET "rm /home/lvuser/log-*.txt"
