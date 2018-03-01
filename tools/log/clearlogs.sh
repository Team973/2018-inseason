#!/bin/bash

TEAM_NUMBER=973
TARGET="roborio-$TEAM_NUMBER-frc.local"

ssh lvuser@$TARGET "rm /home/lvuser/*.txt"
