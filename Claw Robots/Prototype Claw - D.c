#pragma config(Sensor, in1,    arm,            sensorPotentiometer)
#pragma config(Sensor, in2,    claw,           sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  lDriveEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rDriveEnc,      sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  armDown,        sensorTouch)
#pragma config(Sensor, dgtl6,  liftEnc,        sensorQuadEncoder)
#pragma config(Motor,  port1,           leftClaw,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           lDriveFront,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           lDriveBack,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           lDump12,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           lDump3,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rDump3,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           rDump12,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rDriveBack,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rDriveFront,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightClaw,     tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition stuff
// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

//global variables
int LEFT = 1; //note that changing this value could affect gyro rotation function if LEFT is used for the value of the direction parameter in that function
int RIGHT = 2;
int AUTON_SIDE = 0; //either LEFT or RIGHT, as above
int AUTON_PLAY = 0;
int armPotOffset = 0; //The value of the claw potentiometer when the claw is fully closed and touching the physical limit
bool disableLiftComp = false;
bool LCD_CUBE = true;
bool LCD_STARS = true;


int getArmPos() {
	return SensorValue[claw] - armPotOffset;
}

//Our includes
#include "autonomousLib C.c"
#include "../State/Position PID - 4 Motor Struct.c"
#include "LCD Wizard.c"
//setDumpMotors and setClawMotors are in autonomousLib.c

void pre_auton()
{
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	//bDisplayCompetitionStatusOnLcd = false;

	bLCDBacklight = true;
	//bool testLcdWizard = false;
	//if (bIfiRobotDisabled || testLcdWizard) { //Only show auton play wizard when the robot is in competition mode & disabled on initial startup
	//	startTask(LCDSelect);
	//}
}

int liftTarget;
int liftTime;
int clawTarget;
int liftgo = 0;
task liftTask()
{
	while(1)
	{
		if(liftgo == 1)
		{
			liftToTargetPIDEnc(liftTarget,liftTime,2,0.00035,.2);
			liftgo = 0;
		}
	}
}

task asyncLiftPID() {
	while(1) {
		if (!bIfiAutonomousMode) { //only do this in driver control
			disableLiftComp = true;
		}
		if (liftgo) {
			liftToTargetPIDEnc(liftTarget,liftTime,2.5,0.00035,.2);
			liftgo = 0;
		}
		if (!bIfiAutonomousMode) { //only do this in driver control
			disableLiftComp = false;
		}
	}
}

task clawTask()
{
	moveClaw(127,clawTarget);
}
void throw()
{
	setClawMotors(-50);
	liftTarget = 125;
	liftTime = 2200;
	liftgo = 1;
	startTask(liftTask);
	while(sensorValue[liftEnc] < 95)
	{
		wait1Msec(5);
	}
	clawTarget = 1750;
	startTask(clawTask);
}

//potentiometer value for lift: 2150
task autonomous() {
	//strafeLeft(450,127);
	setClawMotors(-127);
	wait10Msec(135);
	setClawMotors(20);
	SensorValue[rDriveEnc] = 0;
	//wait10Msec(100);
	//while(abs(sensorValue[rDriveEnc]) < 370)
	//{
	//	writeDebugStreamLine("%d",SensorValue[rDriveEnc]);
	//	motor[lDriveFront] = -127;
	//	motor[lDriveBack] = 127;
	//	motor[rDriveFront] = 127;
	//	motor[rDriveBack] = -127;
	//	wait1Msec(25);
	//}
	//motor[lDriveFront] = 0;
	//while(abs(SensorValue[rDriveEnc]) < 300) {
		setLeftDtMotors(127);
		setRightDtMotors(-127);
	//}
	wait1Msec(500);
	setLeftDtMotors(-10);
	setRightDtMotors(10);
	wait1Msec(75);
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(25);
	setRightDtMotors(127);
	setLeftDtMotors(127);
	wait10Msec(120);
	setLeftDtMotors(0);
	setRightDtMotors(0);
	setClawMotors(-50);
	wait10Msec(75);
	//SensorValue[rDriveEnc] = 0;
	//straight(127,1000);
	//setClawMotors(-40);
	//wait10Msec(100);
	setDumpMotors(127);
	wait10Msec(80);
	setDumpMotors(15);
	//SensorValue[rDriveEnc] = 0;
	//wait10Msec(100);
	//while(abs(SensorValue[rDriveEnc]) < 870)
	//{
	//	writeDebugStreamLine("%d",SensorValue[rDriveEnc]);
	//	setRightDtMotors(-127);
	//	setLeftDtMotors(-127);
	//	wait1Msec(25);
	//}
	//SensorValue[rDriveEnc] = 0;
	//wait10Msec(100);
	//while(abs(SensorValue[rDriveEnc]) < 415)
	//{
	//	writeDebugStreamLine("%d",SensorValue[rDriveEnc]);
	//	setRightDtMotors(-85);
	//	setLeftDtMotors(85);
	//	wait1Msec(25);
	//}
	//SensorValue[rDriveEnc] = 0;
	//wait10Msec(100);
	//while(abs(SensorValue[rDriveEnc]) < 870)
	//{
	//	writeDebugStreamLine("%d",SensorValue[rDriveEnc]);
	//	setRightDtMotors(-127);
	//	setLeftDtMotors(-127);
	//	wait1Msec(25);
	//}
	//liftToPotTarget(1100,127);
	//setClawMotors(127);
	//wait10Msec(200);
	//setClawMotors(0);
	wait10Msec(25);
	setRightDtMotors(-127);
	setLeftDtMotors(-127);
	wait10Msec(120);
	setLeftDtMotors(0);
	setRightDtMotors(0);
	setLeftDtMotors(127);
		setRightDtMotors(-127);
	//}
	wait1Msec(347);
	setLeftDtMotors(-10);
	setRightDtMotors(10);
	wait1Msec(75);
	setLeftDtMotors(0);
	setRightDtMotors(0);
	wait10Msec(25);
	setRightDtMotors(-127);
	setLeftDtMotors(-127);
	wait10Msec(155);
	setLeftDtMotors(0);
	setRightDtMotors(0);
	setDumpMotors(127);
	wait10Msec(80);
	setDumpMotors(0);
	setClawMotors(127);
	wait10Msec(75);
	setClawMotors(15);
}

bool holdDown = false;
bool liftCompStarted = false;

//lift to 77
//claw to 1869

task liftComp() {
	int target = SensorValue[liftEnc];
	liftToTargetPIDEnc(target+6,1000,2.25,0.00035,.2);
	while(1) {
		wait1Msec(500); //keep this task alive until it stops; the wait time here doesn't really matter, since the task will be stopped when it is no longer needed
	}
}
task usercontrol()
{
	//releaseClaw();
//	driveDistancePID(1400,STRAIGHT,2000);
//wait1Msec(1000000);
//	startTask(autonStars);
//	stopTask(usercontrol);
	//startTask(midfenceStarHeightMacro);
	//throw();
	//stopTask(usercontrol);
	int LY = 0;
	int LX = 0;
	int RY = 0;
	int RX = 0;
	int threshold = 15;
	int armEncMaxLimit = 118; //software limit for potentiometer to limit arm movement from going over the top (protects potentiometer)
	bool enableSoftwareArmPosLimit = false; //experimental software limit for arm, see above
	int clawCompPower = 15;
	bool btn8UPressed = false;
  while(1)
  {
  	if(vexRT[Btn7D]){
  		//throw();
  		startTask(autonomous);
  		stopTask(usercontrol);
  	}
  	//for deadzones; when the joystick value for an axis is below the threshold, the motors controlled by that joystick will not move in that direction
  	LY = (abs(vexRT[Ch3]) > threshold) ? vexRT[Ch3] : 0;
  	LX = (abs(vexRT[Ch4]) > threshold) ? vexRT[Ch4] : 0;
  	RY = (abs(vexRT[Ch2]) > threshold) ? vexRT[Ch2] : 0;
  	RX = (abs(vexRT[Ch1]) > threshold) ? vexRT[Ch1] : 0;
    motor[lDriveFront] = LY + LX;
  	motor[lDriveBack] = LY - LX;
  	motor[rDriveFront] = RY - RX;
  	motor[rDriveBack] = RY + RX;

  	//old lift macros
    if(vexRT[Btn7U])
		{
			clawTarget = 1750;
			startTask(clawTask);
			setClawMotors(18);
			liftToTargetPIDEnc(75,1000,2.5,0.00035,.2);
			setDumpMotors(15);
		}
		//if(vexRT[Btn7L])
		//{
		//	liftgo = 1;
		//	clawTarget = 2000;
		//	liftTarget = 2300;
		//	startTask(clawTask);
		//	startTask(liftTask);
		//}

  	if (vexRT[Btn7R]) {
  		releaseClaw();
  	}

    if (vexRT[Btn5U] && (SensorValue[liftEnc] < armEncMaxLimit || !enableSoftwareArmPosLimit)) {
	  	stopTask(liftComp);
	  	liftCompStarted = false;
	  	setDumpMotors(127);
	  	holdDown = false;
		} else if (vexRT[Btn5D] && !SensorValue[liftDown]) { //second part of condition is to prevent motors from jittering if 5U and 5D are pressed down
			stopTask(liftComp);
			liftCompStarted = false;
			setDumpMotors(-127);
		} else {
			//vertical at 117
			/*if (SensorValue[arm] > 3890) { //arm is all the way down; no compensation power
				setDumpMotors(0);
			} else if (SensorValue[arm] > 1350) { *///arm is up but has not gone past vertical (behind back of robot).  Positive compensation power
				if (SensorValue[liftDown]) {
					holdDown = true;
				}
				if (vexRT[Btn8U] && !btn8UPressed) {
					stopTask(liftComp);
					holdDown = false;
					liftTarget = 77;
					liftTime = 750;
					clawTarget = 1869;
					stopTask(asyncLiftPID);
					startTask(asyncLiftPID);
					liftgo = 1;
					startTask(clawTask);
					btn8UPressed = true;
					liftCompStarted = true; //so that when the lifting finishes, the driver control compensation code doesn't raise the lift even higher
				} else if ((holdDown || SensorValue[liftEnc] >= 117) && !disableLiftComp) {
					stopTask(liftComp);
					liftCompStarted = false;
					setDumpMotors(-12);
				} else if (!liftCompStarted && !disableLiftComp) { //don't restart this task unless the lift has moved and unless the midfence height macro isn't running
					startTask(liftComp);
					liftCompStarted = true;
				}
				if (!vexRT[Btn8U] && btn8UPressed) {
					btn8UPressed = false;
				}
			/*} else { //arm is up and behind the back of the robot.  Negative compensation power (and increased compensation power to protect potentiometer from crossing its physical limit and counter momentum)
				setDumpMotors(-armCompPower - 5);
			}*/
		}

  	if (vexRT[Btn6U]) {
			setClawMotors(127);
			clawCompPower = 15;
		} else if (vexRT[Btn6D]) {
			setClawMotors(-127);
			clawCompPower = -20;
		}	else {
			setClawMotors(clawCompPower);
		}

  	wait1Msec(25);
	}
}
