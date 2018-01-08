The purpose of this document is to give instruction to manually install
CTRE Phoenix FRC Libraries.

For Java/C++:
	NOTE: Old library files are titled TalonSRXLib or CTRLib.
	These should be deleted as new library files use the CTRE_Phoenix
	naming convention.  Duplicate libraries may cause issues
	when writing code.

	Take the folder for your desired language (java or cpp) and
	place it into the wpilib user folder.

	In Linux, this is located in USERHOME\wpilib\user.

	If you examine this file directory, you will notice a
	static library in user\cpp\lib (with header in cpp\include)
	and a shared object and jar in user\java\lib.

	The wpilib eclipse plugins will automatically pick up
	any *.a or *.so files in the cpp directory and any
	*.so or *.jar files in the java directory, so any libraries
	can be included this way.


For Robotbuilder:

	These are Robotbuilder extensions for using CTRE classes.
	It currently contains the Talon SRX, Victor SPX, CANifier, and Pigeon IMU extensions.

	Take the desired extension folder (eg. "Talon SRX") and place it in
	USERHOME\Robotbuilder\extensions.