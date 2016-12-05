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
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(0)
#pragma userControlDuration(60)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                         Driver Skills Template
//
// This is a template for the driver skills competition. It is identical in structure to
// the standard competition template except that the two "#pragma' statements above (and
// copied below) adjust the time limits for the competition.
//				#pragma autonomousDuration(0)
//				#pragma userControlDuration(60)
// The autonomous duration for "Driver Skills" is zero; i.e. there is no autonomous phase.
// The user control duration is 60 seconds
//
// NOTE: The above two pragmas only impact the Crystal implementation. For systems using
//       VEXNET, the VEXNET system ignores these statements as it has the durations
//       for the competition built-in.
//
// Whenever this user program is run, the duration is automatically sent to the VEX master
// processor. The master CPU will only accept these commands once per power=on cycle. So, it's
// best to power cycle your VEX to ensure that they get recognized in case you were
// previously running a standard competition program with different durations.
//
// Testing Via Crystals:
// ====================
//
// The procedure to test a Driver Skills program using the crystals is as follows:
//
// 1. Turn off power to the Crystal transmitter/joysticks.
//
// 2. Turn on your VEX so that the Driver Skills program is running.
//
// 3. Driver skills program segment of your program will start running. At the end of 60
//    seconds the VEX Master CPU will turn off the motors.
//
// 4. Repeat the above sequence
//
//
// Testing Via VEXNET Using VEXNET Competition Switch
// ==================================================
//
// The procedure to test a Driver Skills program using VEXNET Competition Switch is as follows:
//
// 1. Set the two switches on the Competition switch to "DISABLE" and "USER CONTROL"
//
// 2. Start the Driver skills program
//
// 3. Set Switch to ENABLE from DISABLE
//
// 4. You need to manually time the 60 second duration.
//
// 5. Set Switch to DISABLE
//
// 6. Repeat from step (3) to run subsequent test runs. There's no need to reset the VEX or
//    restart your user program.
//
//
// Testing Via VEXNET Using ROBOTC IDE
// ==================================================
//
// It is not necessary to own a VEXNET switch. ROBOTC has a test window that allows the same functionality.
// The test window has three buttons for "DISABLE", "AUTONOMOUS", "USER CONTROL".
//
// 1. Open the ROBOTC Debugger. Then open the "Competition Control" Debugger window.
//
// 2. Start your Driver Skills program running.
//
// 3. Click the "DISABLED" button on the "Competition Control" window.
//
// 4. Click the "USER CONTROL" button on the "Competition Control" window.
//
// 5. You need to manually time the 60 second duration.
//
// 6. Click the "DISABLED" button on the "Competition Control" window.
//
// 7. Repeat from step (4) to run subsequent test runs. There's no need to reset the VEX or
//    restart your user program.
//
/////////////////////////////////////////////////////////////////////////////////////////

//Switch Cases
const int forward = 1;
const int turnRight = 2;
const int turnLeft = 3;
const int backwards = 4;
const int up = 5;
const int down= 6;

//Encoder Variables
float wheelCircumference = 3.25*PI;
float revolutions = 0;
float averageEncoderValue = 0;
int speedMCounts = 392; //number of counts per rotation for VEX High Speed Motor

void zeroEncoders(){ //Zeros Encoders
	SensorValue[DRFLED1] = 0;
	SensorValue[DRFRED1] = 0;
	SensorValue[DRBRED1] = 0;
	SensorValue[DRBLED1] = 0;
}
void setFBMotors(int speed){ //automatically sets the four bar power (reduce clutter)
	motor[RFBT] = speed;
	motor[RFBB] = speed;
	motor[LFBT] = speed;
	motor[LFBB] = speed;

}

void setDriveMotors(int FLSpeed, int FRspeed, int BRspeed, int BLspeed){ //int FLSpeed, int FRspeed, int BRspeed, int BLspeed
	motor[FL] = FLspeed;
	motor[FR] = FRspeed;
	motor[BR] = BRspeed;
	motor[BL] = BLspeed;
}
void setLiftMotors(int speed){
	motor[LLM] = speed;
	motor[RLM] = speed;
}
void Break(int direction){
	switch (direction) {
	case forward:
		setDriveMotors(-127,-127,-127,-127);
		wait10Msec(7);
		break;

	case turnLeft:
		setDriveMotors(127, -127, -127, 127);
		wait10Msec(7);
		break;

	case turnRight:
		setDriveMotors(-127, 127, 127, -127);
		wait10Msec(7);
		break;

	case backwards:
		setDriveMotors(127,127,127,127);
		wait10Msec(7);
		break;

	default:
		setDriveMotors(0,0,0,0);
	}
}
float getDTEncoderAverage(){
	averageEncoderValue = (abs(SensorValue(DRFLED1)) + abs(SensorValue(DRFRED1)) + abs(SensorValue(DRBRED1)) + abs(SensorValue(DRBLED1)))/4;
	return averageEncoderValue;
}
float getFBEncoderAverage(){

}
void moveFB(int direction, int degrees){
	int pinionTeeth = 12;
	int largeGearTeeth = 84;
	int percentGearTurned = degrees/360;
	int lGearTeethUsed = largeGearTeeth*percentGearTurned;
	int pinionRots = lGearTeethUsed/pinionTeeth;
	float ticks = pinionRots*speedMCounts;
	if(direction == up){
		while(getFBEncoderAverage() < ticks){
			setFBMotors(127);
		}
		if(direction == down){
			while(getFBEncoderAverage() < ticks){
				setFBMotors(-127);
			}
		}
		else {
			setFBMotors(0);
		}

	}
}
void move(int direction, int speed, int distance){
	revolutions = 360*(distance/wheelCircumference);
	switch (direction) {

	case forward:
		zeroEncoders();
		while(getDTEncoderAverage() < revolutions){
			setDriveMotors(127,127,127, 127);
		}
		zeroEncoders();
		Break(forward);
		break;

	case turnLeft: //int FLSpeed, int FRspeed, int BRspeed, int BLspeed
		zeroEncoders();
		while(getDTEncoderAverage() < revolutions){
			setDriveMotors(-127, 127, 127, -127);

		}
		Break(turnLeft);
		break;

	case turnRight: //int FLSpeed, int FRspeed, int BRspeed, int BLspeed
		zeroEncoders();
		while(getDTEncoderAverage() < revolutions){
			setDriveMotors(127, -127, -127, 127);
		}
		Break(turnRight);
		break;

	case backwards:
		zeroEncoders();
		while(getDTEncoderAverage() < revolutions){
			setDriveMotors(-127, -127, -127, -127);

		}
		Break(backwards);
		break;

	default:
		setDriveMotors(0,0,0,0);
		zeroEncoders();

	}
	zeroEncoders();
}
void encoderTest(int ticks){
	zeroEncoders();
	while(getDTEncoderAverage() < ticks){
		setDriveMotors(127,127,127, 127);
	}
}
void doTheShimmy(){ //release the platform on plays that require that

	int shimmyDistance = 1.5;
	move(forward, 127, shimmyDistance);
	Break(forward);
	move(backwards, 127, shimmyDistance);
	Break(backwards);
	move(forward, 127, shimmyDistance);
	Break(forward);
	move(backwards, 127, shimmyDistance);
	Break(backwards);
	move(forward, 127, shimmyDistance);
	Break(forward);
	move(backwards, 127, shimmyDistance);
	Break(backwards);
	move(forward, 127, shimmyDistance);
	Break(forward);
	move(backwards, 127, shimmyDistance);
	Break(backwards);

}
void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// The "Driver Skills" competition has no autonomous phase. Simply leave the following
// placeholder.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	int wt =775;
	int fbs = 40;
	float tsp = 80;

	//LFence Play

	//Raise Four-Bar (Uses time at the moment)
	setFBMotors(fbs);
	wait1Msec(wt);
	setFBMotors(0);

	move(forward, 127, 55); //Move forward to knock off stars
	move(backwards, 127, 25); //Move back to give room to turn
	move(turnLeft, tsp, 10.5); //rotate 90 deg to the left
	move(forward, 127, 13); //Move forward to align with the third star
	move(turnRight, tsp, 10.5); //Rotate 90 deg to the right
	move(forward, 127, 2); //Move forward to knock of third star
	move(backwards, 127, 2);
	setDriveMotors(0,0,0,0);
	wait10Msec(30);
	move(turnLeft, 127, 10.5);
	move(backwards, 127, 13);
	move(turnRight, 127, 10.5);
	move(backwards, 127, 55 );
	move(turnRight, 127, 10.5)
	//We are now in starting position for the second autonomous play
	setFBMotors(-fbs);
	wait1Msec(wt);
	setFBMotors(0);
	move(backwards, 50, 20); //move back to allow room to release platform
	dotheShimmy(); //release the platform
	move(forward, 75, 48); //move to pick up stars
	//Secure the stars by lifting up the platform
	setFBMotors(fbs); //
	wait1Msec(300);
	setFBMotors(0);
	//Get in position to launch the stars
	move(turnRight, 40, 10.5); //Rotate 90 degrees clockwise
	move(backwards, 50, 48); //Drive backwards toward the fence
	//Lower the platform
	setFBMotors(-fbs);
	wait1Msec(300);
	setFBMotors(0);
	//Launch the stars
	setFBMotors(127);
	wait1Msec(900);
	setFBMotors(0);

	//This play should get us 8 points

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
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
		motor[FL] = vexRT[Ch3];
		motor[BL] = vexRT[Ch3];
		motor[FR] = vexRT[Ch2];
		motor[BR] = vexRT[Ch2];
	}
}
