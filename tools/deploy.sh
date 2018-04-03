#!/bin/bash
PROGRAM=$1
shift # shift "shifts" the command line arguments up by 1 so $2 becomes $1 etc.
ROBOTCOMMAND=$1
shift
LIBRARIES=( "$@" )

TEAM_NUMBER="${LIBRARIES[${#LIBRARIES[@]}-1]}"
if test ! $(echo "$TEAM_NUMBER" | grep .so | wc -l) -eq 1
then
    unset LIBRARIES["${#LIBRARIES[@]}"-1]
else
    TEAM_NUMBER=973
fi

TARGET_USER=lvuser
TARGET_DIR=/home/lvuser

LIBRARY_USER=admin
LIBRARY_DIR=/usr/local/frc/lib
LIBRARY_TMP_DIR=$TARGET_DIR/tmp

deploy () {
    if [ $? -eq 0 ]; then
        echo "Removing old program..."
        ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$TARGET_USER@$TARGET" "rm -f $TARGET_DIR/FRCUserProgram" > /dev/null 2>&1
        echo "Copying over new program..."
        scp -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$PROGRAM" "$TARGET_USER@$TARGET:$TARGET_DIR/FRCUserProgram" > /dev/null 2>&1
        echo "Copying over robotCommand..."
        scp -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$ROBOTCOMMAND" "$TARGET_USER@$TARGET:$TARGET_DIR" > /dev/null 2>&1
        echo "Checking for libraries..."
        ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$TARGET_USER@$TARGET" 'test ! $(ls '"$LIBRARY_DIR"' | grep libopencv_ | wc -l) -eq 17' > /dev/null 2>&1
        if [ $? -eq 0 ]
        then
            ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$TARGET_USER@$TARGET" "mkdir $LIBRARY_TMP_DIR" > /dev/null 2>&1
            for LIB in "${LIBRARIES[@]}"
            do
                LIBRARY_SO=$(basename "$LIB")
                ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$TARGET_USER@$TARGET" "test ! -e $LIBRARY_DIR/$LIBRARY_SO" > /dev/null 2>&1
                if [ $? -eq 0 ]
                then
                    echo "Copying $LIBRARY_SO to $LIBRARY_TMP_DIR/$LIBRARY_SO"
                    scp -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$LIB" "$LIBRARY_USER@$TARGET:$LIBRARY_TMP_DIR/$LIBRARY_SO" > /dev/null 2>&1
                fi
            done
            echo "Cleaning up after copying libraries..."
            ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$LIBRARY_USER@$TARGET" "sed -i -e 's/^StartupDLLs/;StartupDLLs/' /etc/natinst/share/ni-rt.ini;
            chmod +x $LIBRARY_TMP_DIR/libopencv_* && mv $LIBRARY_TMP_DIR/* $LIBRARY_DIR/. && ldconfig;
            rm -rf $LIBRARY_TMP_DIR;
            " > /dev/null 2>&1
        fi
        echo "Cleaning up..."
        ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$TARGET_USER@$TARGET" ". /etc/profile.d/natinst-path.sh;
        chown lvuser $TARGET_DIR/FRCUserProgram;
        setcap 'cap_sys_nice=pe' $TARGET_DIR/FRCUserProgram;
        chmod a+x $TARGET_DIR/FRCUserProgram;
        /usr/local/frc/bin/frcKillRobot.sh -t -r;
        sync" > /dev/null 2>&1
        exit
    fi
}

# Probe for connection
TARGET="roborio-$TEAM_NUMBER-frc.local"
echo "Probing for $TARGET..."
ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$TARGET_USER@$TARGET" true > /dev/null 2>&1
deploy

TEAM_NUMBER=$(printf "%04d" "$TEAM_NUMBER")
P1=${TEAM_NUMBER:0:2}
P2=${TEAM_NUMBER:2:2}
TARGET="10.$((10#$P1)).$P2.2"
echo "Not found - probing for $TARGET..."
ssh -4 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$TARGET_USER@$TARGET" true > /dev/null 2>&1
deploy

echo "Not found - giving up."
exit 1
