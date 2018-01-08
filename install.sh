#!/bin/sh

# This script has been modified to install bazel for ubuntu and macos
# however it has not been tested; USE AT YOUR OWN RISK

# Set regular user
safeuser="INSERT_USERNAME_HERE"

if [ $safeuser = "INSERT_USERNAME_HERE"]
then
  echo "Change safeuser username!"
  exit 1
fi

# Exit if an error occurs
set -e

# Make sure script is root
if [ "$(id -u)" != "0" ]; then
  echo "ERROR: Must run as root!"
  exit 1
fi

roborioPrep()
{
    echo "No roborio prep necessary"
    exit
}

# Ubuntu based installation
ubuntuInstall()
{
  add-apt-repository ppa:wpilib/toolchain
  echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
  curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -
  apt-get update
  apt-get install openjdk-8-jdk bazel frc-toolchain
}

# macOS installation
macInstall()
{
  # Get RoboRio toolchain
  wget http://first.wpi.edu/FRC/roborio/toolchains/FRC-2017-OSX-Toolchain-4.9.3.pkg.tar.gz
  tar xvf FRC-2017-OSX-Toolchain-4.9.3.pkg.tar.gz
  installer -pkg FRC\ ARM\ Toolchain.pkg/ -target /

  # Check for Homebrew. If installed, update
  # Drop root to install Homebrew
  sudo -u $safeuser $0
  which -s brew
  if [[ $? != 0 ]] ; then
    # Install Homebrew
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
  else
    brew update
    brew install bazel
  fi
}

echo "Prepare RoboRio?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) roborioPrep; break;;
        No ) break;;
    esac
done

echo "Install on Ubuntu or macOS?"
select yn in "Ubuntu" "macOS"; do
    case $yn in
        Debian ) debianInstall; break;;
        macOS ) macInstall; break;;
    esac
done

echo "Done."
