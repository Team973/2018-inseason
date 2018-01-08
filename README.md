# 2018-inseason
## Power Up code of FRC Team 973: The Greybots

[![Build Status](https://travis-ci.com/Team973/2018-inseason.svg?token=PMQ4h4i9r3eRUJnsCJBt&branch=master)](https://travis-ci.com/Team973/2018-inseason)
[![FRC Year](https://img.shields.io/badge/frc-2018-brightgreen.svg)](https://www.firstinspires.com/robotics/frc/game-and-season)
[![Language Type](https://img.shields.io/badge/language-c++-brightgreen.svg)](https://wpilib.screenstepslive.com/s/4485/m/13810)

## Getting Started
Setup your programming environments by following the guide in our README of the greybots-skeleton repository. 

### Cloning the Repo
Start by cloning the repo by running the command:
`git clone <https://github.com/Team973/2018-inseason.git>`

### Make a Branch
Create and checkout a new branch. `git checkout -b <your_branch_name>`, where `<your_branch_name>` is a descriptive name for your branch. Use dashes in the branch name, not underscores. Do not create a new branch unless a same branch has already been made. Make whatever code changes you want/need to make. Be sure to write tests for your changes! Commit your work locally. Try to make your commits as small as possible. Follow the conventions for commit messages.

### Add your Name to the Contributors list
In `src/Robot.h`, add your name to the contributor list at the top of the program in the big chunk of comment.

### Compiling and Deploying
Run this command if you are compiling the robot code: 
`bazel build //src:robot --cpu=roborio` 
Compiling and Deploying:
`bazel run //tools:deploy --cpu=roborio-darwin`
**Note:** Use roborio-darwin as the CPU if you are a macOS user.

### Add, Commit, Push
In the home repo directory, do a `git add .` to add all files in the repo for staging the commit.
Then run `git commit -m “<commit message>”` where `<commit message>` is a succinct description of your local commit and what changes you made.
Push to your own specific branch of the repo. `git push origin <your_branch_name>` 

### Make a PR
Submit a pull request by clicking on `New pull request` in your branch. Add a couple of bulleted list description of what you did in addition to the commit summary. 

### Waiting for Approval
Once you submit your PR, Andrew, Kyle, or Oliver must approve your changes before they are merged. If there are any concerns about your pull request, fix them. To update your PR, just push to the branch. 

### Merge and Close Branch
Once everything is good and free of errors :fire:, Andrew, Kyle, or Oliver will merge your changes to the `master` branch. Then you should delete your branch by going to your pull request and clicking on `Delete Pull Request`.

Questions? Slack Andrew, Kyle, or Oliver
