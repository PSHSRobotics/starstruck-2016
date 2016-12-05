#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    AutonSelector,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  DRFLED1,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  DRFRED1,        sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  DRBRED1,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  DRBLED1,        sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LLM,           tmotorVex393HighSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FR,            tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FL,            tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LFBB,          tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LFBT,          tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           RFBB,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           RFBT,          tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port8,           RLM,           tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           BR,            tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          BL,            tmotorVex393TurboSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "..\Vex_Competition_Includes.c"

int threshold = 15;
const int forward = 1;
const int strafeRight = 2;
const int strafeLeft = 3;
const int backwards = 4;
float wheelCircumference = 3.25*PI;
float revolutions = 0;
float averageEncoderValue = 0;

void zeroEncoders(){
	nMotorEncoder[DRFLED1] = 0;
	nMotorEncoder[DRFRED1] = 0;
	nMotorEncoder[DRBRED1] = 0;
	nMotorEncoder[DRBLED1] = 0;
}
void setFBMotors(int speed){ //automatically sets the four bar power (reduce clutter)
	motor[LFBB] = speed;
	motor[LFBT] = speed;
	motor[RFBT] = speed;
	motor[RFBB] = speed;

}
void setDriveMotors(int FLSpeed, int FRspeed, int BRspeed, int BLspeed){
	motor[FL] = FLspeed;
	motor[FR] = FRspeed;
	motor[BR] = BRspeed;
	motor[BL] = BLspeed;
}
void setLiftMotors(int speed){
	motor[LLM] = speed;
	motor[RLM] = speed;
}
float getDTEncoderAverage(){
	averageEncoderValue = (abs(SensorValue(DRFLED1)) + abs(SensorValue(DRFRED1)) + abs(SensorValue(DRBRED1)) + abs(SensorValue(DRBLED1)))/4;
	return averageEncoderValue;
}
void move(int direction, int speed, int distance){
	revolutions = distance/wheelCircumference;
	switch (direction) {

	case forward:
		zeroEncoders();
		while(getDTEncoderAverage() < distance){
			setDriveMotors(127,127,127, 127);
		}
		break;

	case strafeLeft:
		zeroEncoders();
		while(getDTEncoderAverage() < distance){
			setDriveMotors(-127, 127, 127, -127);
		}
		break;

	case strafeRight:
		zeroEncoders();
		while(getDTEncoderAverage() < distance){
			setDriveMotors(127, -127, -127, 127);
		}
		break;

	case backwards:
		zeroEncoders();
		while(getDTEncoderAverage() < distance){
			setDriveMotors(-127, -127, -127, -127);
		}
		break;

	default:
		setDriveMotors(0,0,0,0);

	}
}

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}
task autonomous()
{
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................

	// Remove this function call once you have "real" code.
	AutonomousCodePlaceholderForTesting();
}

task FBControl(){ //task for the Four-Bar control
	while(true){
		//Four-Bar Motor Controls (2 bottom motors on either side are y-cabeled FYI
		if (vexRT[Btn6U] == 1 && vexRT[Btn6D] == 0){ //UP
			setFBMotors(127);
		}
		else if (vexRT[Btn6U] == 0 && vexRT[Btn6D] == 1){ //DOWN
			setFBMotors(-127);
		}
		else { //IDLE
			setFBMotors(0);
		}
	}
}
task liftControl (){//task for the lift control
	while(true){
		if(vexRT[Btn5U] == 1 && vexRT[Btn5D] == 0){
			setLiftMotors(127);
		}
		else if (vexRT[Btn5U] == 0 && vexRT[Btn5D] == 1){
			setLiftMotors(-127);
		}
		else {
			setLiftMotors(10);
		}
	}
}
task usercontrol()
{
	// User control code here, inside the loop
	startTask(FBControl);
	startTask(liftControl);
	while (true)
	{
		//Drivetrain controls and threshold (15)
		//Need to convert ternary statements at some point or another
		motor[FL] = vexRT[Ch3];
		motor[BL] = vexRT[Ch3];
		motor[FR] = vexRT[Ch2];
		motor[BR] = vexRT[Ch2];
	}
}
