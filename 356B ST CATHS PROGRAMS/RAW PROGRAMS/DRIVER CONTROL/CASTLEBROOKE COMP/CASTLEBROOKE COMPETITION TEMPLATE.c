#pragma config(Sensor, in2,    gyro,           sensorGyro)
#pragma config(Sensor, in4,    potentiometer_lift, sensorPotentiometer)
#pragma config(Sensor, dgtl2,  left_chassis_encoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  right_chassis_encoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           R_Lift,        tmotorVex393HighSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           ycable2DriveR, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           R_Shooter,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           C_F_Left,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           Claw,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           Intake,        tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           C_F_Right,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           L_Shooter,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           ycable1DriveL, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          L_Lift,        tmotorVex393HighSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

	int R_Freq = 50;
	int R_Batt = 8628;
	int P_Freq = R_Freq * (R_Batt / nImmediateBatteryLevel)
	// Initial values for Sensors: in 1 = 854  in 2 = 2288
	// Initial values for IMEs: port 1 = 0  port 2 = 0  port 3 = 0

	void wait(int temp)
	{
		wait1Msec( P_Freq * temp);
	}

// Aman Patel
// 356B
// Turning Point
// November 25 2018
// Just Driver Control Program


//drive void
int drive = 0;

// chassis void
void driveL(int speed)
{
motor[C_F_Left] = speed;
motor[ycable1DriveL] = speed;
}

// Right Drive Void
void driveR(int speed)
{
motor[C_F_Right] = speed;
motor[ycable2DriveR] = speed;
}

// Lift Void
void lift(int speed)
{
motor[R_Lift] = speed;
motor[L_Lift] = speed;
}

// Claw Void
void flipper(int speed)
{
motor[Claw] = speed;
}

// Intake void
void _intake(int speed)
{
motor[Intake] = speed;
}

// Shooter void
void shooter(int speed)
{
motor[R_Shooter] = speed;
motor[L_Shooter] = speed;
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

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

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Go back and get the ball
  driveL(-100);
	driveR(100);
	// run shooter
  shooter(127);
  wait(23);
  // stop
  driveL(0);
	driveR(0);
	// run intake
  _intake(127);
  wait(18.1);
  _intake(0);
  // go back to tile
  driveL(100);
	driveR(-100);
	wait(23.5);
	// turn to flags
	driveL(-100);
	driveR(-100);
	wait(12);

	// go back a bit
	driveL(100);
	driveR(-100);
	wait(2);

	// stop chassis
	driveL(0);
	driveR(0);
	wait(23);

	// run intake to shoot middle flag
	_intake(127);
  wait(25);
  _intake(0);

  /*
  // allign to top flag
  driveL(-100);
	driveR(100);
	wait(12);
	// stop chassis
	driveL(0);
	driveR(0);
	wait(8);
		// run intake to shoot middle flag
	_intake(127);
  wait(27);
  _intake(0);
  	// turn to bottom flags
	driveL(-100);
	driveR(-100);
	wait(2);
	  // hit bottom flag
  driveL(-100);
	driveR(100);
	wait(12.5);

	// go straight
  driveL(100);
	driveR(-100);
	wait(15);
	// turn to platform
	driveL(100);
	driveR(100);
	wait(1);
	// go straight
  driveL(100);
	driveR(-100);
	wait(28.5);
  // turn to platform
	driveL(100);
	driveR(100);
	wait(8.5);
	driveL(0);
  driveR(0);
  // lift up lift
	lift(127);
	wait(2);
	lift(0);
	// go straight to the wall to line up
  driveL(100);
	driveR(-100);
	wait(5);
  // stop chassis motor
	driveL(0);
	driveR(0);
	wait(10);
  // go straight on platform
  driveL(-100);
	driveR(100);
	wait(49.5);
	*/
	// stop chassis motor
	driveL(0);
	driveR(0);


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  // User control code here, inside the loop

while(true){

 // Drive button to flip front and back
 if (vexRT[Btn5U] ==1){
  driveL(-vexRT[Ch3]);
 	driveR(vexRT[Ch2]);
 }
 else{
 driveL(vexRT[Ch2]);
 driveR(-vexRT[Ch3]);
 }

 // Button for the lift up and down
 if (vexRT[Btn6DXmtr2] == 1){
 	lift(120);
 }
 else if(vexRT[Btn6UXmtr2] == 1){
 	lift(-120);
 }
 else if(vexRT[Btn8LXmtr2] == 1){
   lift(-20);
 }
 else{
 	lift(0);
 }

 // Button for the shooter for top flag and middle flag
 // This is for the top flag running shooter at full speed
 if (vexRT[Btn5UXmtr2] == 1){
 	shooter(127);
 }
 // This is for the middle flag running shooter at 100 speed
 else if(vexRT[Btn5DXmtr2] == 1){
 	shooter(100);
 }
 // If none of those buttons are pressed the shooter will not continue
 else{
 	shooter(0);
 }

 // Button for the flipper/claw
 // This is to flip the cap while it is in the claw
 if (vexRT[Btn7UXmtr2] == 1){
 	flipper(45);
 }
 else if (vexRT [Btn7DXmtr2] == 1){
 	flipper (-45);
 }
 else{
 	flipper(0);
 }

 // Button for the rubberband intake to bring up to the shooter
 // So the intake can pick up the balls
 if (vexRT[Btn6U] == 1){
 	_intake(120);
 }
 // So the intake will let the balls out
 else if(vexRT[Btn6D] == 1){
 	_intake(-120);
 }
 else{
 	_intake(0);
 }

 // Brake for the chassis
 if (vexRT[Btn5D] == 1){
   motor[C_F_Left] = -30;
   motor[ycable2DriveR] = 20;
   motor[C_F_Right] = -30;
   motor[ycable1DriveL] = 20;
 }
 else{
   motor[C_F_Left] = 0;
   motor[ycable2DriveR] = 0;
   motor[C_F_Right] = 0;
   motor[ycable1DriveL] = 0;
 }


}
}