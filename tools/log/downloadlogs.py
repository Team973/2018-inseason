#!/usr/bin/env python

"""
Copy ALL the logs from the roborio to this directory
For each logfile, check the contents and see if there's a match number.  If
there is a match number, copy the file into the labeled directory and change
the name of the file to the match number (makes portmortem log-checking much
easier).
"""

import csv, os, sys

# TODO Check for team number in environment
TEAM_NUMBER = 973

# TODO determinea better destination location for logfiles
DESTINATION_DIR_PARENT = os.path.expanduser("~/robot_logs/")
DESTINATION_DIR_RAW = DESTINATION_DIR_PARENT + 'raw/'
DESTINATION_DIR_LABELED = DESTINATION_DIR_PARENT + 'labeled/'

os.system('mkdir {}'.format(DESTINATION_DIR_PARENT))
os.system('mkdir {}'.format(DESTINATION_DIR_RAW))
os.system('mkdir {}'.format(DESTINATION_DIR_LABELED))

os.system('scp -p lvuser@roborio-{}-frc.local:/home/lvuser/*.txt {}'.format(
    TEAM_NUMBER, DESTINATION_DIR_RAW))

for filename in os.listdir(DESTINATION_DIR_RAW):
    matchLabel = None
    with open(filename, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row['Match Identifier']:
                matchLabel = row['Match Identifier']
                break

    os.system('cp {} "{}"'.format(
        filename,
        DESTINATION_DIR_LABELED + matchLabel + '.csv'))
