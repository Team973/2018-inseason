# GreyDash
Forked from [FRC Dashboard](https://github.com/FRCDashboard/FRCDashboard), GreyDash is a custom HTML/CSS/JS based dashboard for interacting with the robot.

## Usage
This section will go over the usage of GreyDash.

### Installing dependencies
Install [Yarn](https://yarnpkg.com/en/docs/install), then cd to the GreyDash directory. Then, run `yarn install` to install dependencies. The main dependencies are listed in package.json.

### Starting
To start, run `yarn start`.

### Building
To package for OSes, run `yarn dist` or `yarn pack`.

### Linting
Please lint your JavaScript files. Easiest way is to run `yarn lint --fix`.

## Connecting to the Robot
A dialog will pop up with the option to connect to the robot. Make sure you're on the robot's network and the robot address is correct, then click "Connect". If you cant connect, try pinging the robot.
