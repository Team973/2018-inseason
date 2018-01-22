#!/bin/bash
TEAM_NUMBER=$1
shift # shift "shifts" the command line arguments up by 1 so $2 becomes $1 etc.
PROGRAM=$1
shift
ROBOTCOMMAND=$1
shift
LIBRARIES=( "$@" )

TARGET_USER=lvuser
TARGET_DIR=/home/lvuser

deploy () {
    if [ $? -eq 0 ]; then
        echo "Removing old program..."
        ssh -o StrictHostKeyChecking=no "$TARGET_USER@$TARGET" "rm -f $TARGET_DIR/FRCUserProgram" > /dev/null 2>&1
        echo "Copying over new program..."
        scp -o StrictHostKeyChecking=no "$PROGRAM" "$TARGET_USER@$TARGET:$TARGET_DIR/FRCUserProgram" > /dev/null 2>&1
        echo "Copying over robotCommand..."
        scp -o StrictHostKeyChecking=no "$ROBOTCOMMAND" "$TARGET_USER@$TARGET:$TARGET_DIR" > /dev/null 2>&1
        echo "Checking for libraries..."
        for LIB in "${LIBRARIES[@]}"
        do
            LIBRARY_SO=$(basename "$LIB")
            if ssh -o StrictHostKeyChecking=no  "$TARGET_USER@$TARGET" "test $TARGET_DIR/$LIBRARY_SO" \> /dev/null 2\>\&1
            then
                echo "Copying $LIBRARY_SO to $TARGET_DIR/$LIBRARY_SO"
                scp -o StrictHostKeyChecking=no "$LIB" "$TARGET_USER@$TARGET:$TARGET_DIR/$LIBRARY_SO" > /dev/null 2>&1
            fi
        done
        echo "Cleaning up..."
        ssh -o StrictHostKeyChecking=no "$TARGET_USER@$TARGET" ". /etc/profile.d/natinst-path.sh;
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
ssh "$TARGET_USER@$TARGET" true > /dev/null 2>&1
deploy

TEAM_NUMBER=$(printf "%04d" "$TEAM_NUMBER")
P1=${TEAM_NUMBER:0:2}
P2=${TEAM_NUMBER:2:2}
TARGET="10.$((10#$P1)).$P2.2"
echo "Not found - probing for $TARGET..."
ssh "$TARGET_USER@$TARGET" true > /dev/null 2>&1
deploy

echo "Not found - giving up."
exit 1
