# How To Incoporate NetworkTables Into Your Subsystem
*This guide will go over the required steps for getting the 2018 NetworkTables working in your subsystem.*

## Step 1: Include Statements
You will need to include NetworkTables by adding the following line at the top of your subsystem's header file:
```cpp
#include "networktables/NetworkTableInstance.h"
```

## Step 2: Add `dashboard` to your subsystem's constructor and pass Robot's member `m_dashboard` to it
In your subsystem's header, find the constructor declaration in the public section:
```cpp
class SubsystemName ... {
    public:
        SubsystemName(TaskMgr *scheduler, ... NetworkTableInstance dashboard, ...);
        ...
}
```
**Note: there is no * before dashboard.**

In your subsystem's cpp, find the constructor definition, and mirror the constructor declaration in the header:
```cpp
SubsystemName::SubsystemName(TaskMgr *scheduler, ... NetworkTableInstance dashboard, ...)
        ... {
    ...
};
```

In Robot.cpp, find your subsystem and mirror the changes:
```cpp
Robot::Robot()
        : CoopMTRobot()
        ...
        , m_dashboard(NetworkTableInstance::GetDefault())
        ...
        , m_mySubsystem(new SubsystemName(this, ... m_dashboard, ...)
        ... {
    ....
};
```
**Note: make sure the parameters for your subsystem constructor are in the correct order and all exist!**

## Step 3: Declare a private member `m_dashboard` in your subsystem
In your subsystem's header, find the private section, and add a new `m_dashboard` member:
```cpp
class SubsystemName ... {
    public:
        ...
    private:
        ...
        TaskMgr m_scheduler;
        ...
        NetworkTableInstance m_dashboard;
        ...
}
```

In your subsystem's cpp, find the constructor's initializer list and add `m_dashboard`:
```cpp
SubsystemName::SubsystemName(TaskMgr *scheduler, ... NetworkTableInstance dashboard, ...)
        : m_scheduler(scheduler)
        , m_dashboard(dashboard)
        ... {
    ...
};
```
**Note: make sure you declare `m_dashboard` in the header in the same posistion as in the cpp!**

## Step 4a: Write to the table!
In your subsystem's cpp, find the function that you want to have the ability to send information to the table, i.e. TaskPeriodic, which will continuously update values:
```cpp
int value = 0;
...
void SubsystemName::TaskPeriodic(RobotMode mode) {
    ...
    value += 1
    m_dashboard.GetEntry("CountBy1").SetValue(value);
    ...
}
```
The example above will set `value` equal to itself plus 1, then set the entry `CountBy1` equal to `value`.

Other set options are available! View them [here](http://first.wpi.edu/FRC/roborio/release/docs/cpp/classnt_1_1NetworkTableEntry.html).

## Step 4b: Choosing your key name
Wherever you have a NetworkTable entry, you should have an appropriate key, or entry name. For example, if your subsystem was drive, and you wanted to post a gyro value, a good choice for a key would be `GetEntry("drive/gyro")`. It's good practice to follow the `GetEntry("SubsystemName/SubsystemDeviceName")` for naming your keys.
