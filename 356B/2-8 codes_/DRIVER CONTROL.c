#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in4,    power,          sensorAnalog)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl11, rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,            ,             tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           right_front,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           shooter_right, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           right_mid,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           left_back,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           right_back,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           intake,        tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           shooter_left,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           left_front,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          left_mid,      tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task LCD(){
	while(true)
	{
   bLCDBacklight = true;
   string mainBattery;
   string expanderBattery;
   sprintf(mainBattery," %0.2f Volts", (float)nImmediateBatteryLevel/1000.0);
   sprintf(expanderBattery," %0.2f Volts", (float)SensorValue[power]/270.0);
   clearLCDLine(0);
   clearLCDLine(1);
   displayLCDString(0,0,mainBattery);
   displayLCDString(1,0,expanderBattery);
   wait1Msec(1000);
	}

}

// TIME THEORY BY TISSAN AND YAHYA
int R_Freq = 50;
int R_Batt = 8628;
int P_Freq = R_Freq * (R_Batt / nImmediateBatteryLevel);
// Initial values for Sensors: in 1 = 854  in 2 = 2288
// Initial values for IMEs: port 1 = 0  port 2 = 0  port 3 = 0

//power expander

// TIME VOID FOR TIME THEORY
void wait(int temp)
{
	wait1Msec( P_Freq * temp);
}


void right_drive (int speed){   //function to combine all right motors and takes in the speed when called
	// all right motors are set to the same speed
	motor[right_mid] = speed;
	motor[right_front] = speed;
	motor[right_back] = speed;
}
void left_drive (int speed){   //function to combine all left motors
	//all left motors are set to the same speed
	motor[left_mid] = speed;
	motor[left_front] = speed;
	motor[left_back] = speed;
}

void forward_drive (int speed){
	right_drive(speed);
	left_drive (speed);
}
void shooter(int speed)
{
	motor[shooter_left]=speed;
	motor[shooter_right]=speed;
}
void break_drive(){
	right_drive(0);
	left_drive(0);
}
void red_front (){
	shooter(120);
	wait (50);
	motor[intake]= -120;
	wait(30);
	shooter(0);
	motor[intake]= 0;
	left_drive(35);
	right_drive(0);
	wait(8);
	break_drive();
	wait(5);
	forward_drive(120);
	wait(50);
	left_drive(0);
	right_drive(0);
}
void blue_front (){
	shooter(120);
	wait (50);
	motor[intake]= -120;
	wait(30);
	shooter(0);
	motor[intake]= 0;
	left_drive(-35);
	right_drive(0);
	wait(8);
	break_drive();
	wait(5);
	forward_drive(120);
	wait(50);
	left_drive(0);
	right_drive(0);
}
void red_back_mid (){
	shooter(127);
	wait(80);
	motor[intake] =-120;
	wait(35);
}
void red_back_for(){
	shooter(127);
	wait(100);
	motor[intake] =-120;
	wait(50);
}

void blue_back_mid(){
	forward_drive(30);
	wait(40);
	left_drive (10);
	wait(5);
	break_drive();
	shooter(127);
	wait(100);
	motor[intake] =-120;
	wait(50);
	forward_drive(-30);
	wait(40);
}
void blue_front(){
	shooter(120);
	wait (50);
	motor[intake]= -120;
	wait(30);
	shooter(0);
	motor[intake]= 0;
	left_drive(0);
	right_drive(35);
	wait(8);
	break_drive();
	wait(5);
	motor[intake]=-120;
	forward_drive(120);
	wait(50);
	left_drive(0);
	right_drive(0);
	motor[intake]=0;
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
	//shooter(120);
	//wait (50);
	//motor[intake]= -120;
	//wait(30);
	//shooter(0);
	//motor[intake]= 0;
	//left_drive(35);
	//right_drive(0);
	//wait(8);
	//break_drive();
	//wait(5);
	//motor[intake]= -120 ;
	//forward_drive(120);
	//wait(50);
	//motor[intake]=0;
	//left_drive(0);
	//right_drive(0);
	//2nd code reddd finallsss

	//shooter(127);
	//forward_drive (180);
	//wait(10);
	//break_drive();
	//wait(50);
	//motor[intake] =-120;
	//wait(45);
	//motor[intake] =0;
	//shooter(0);
	//forward_drive (-180);
	//wait(5);
	//right_drive (180);
	//wait(15);
	//left_drive(0);
	//break_drive();
	//wait (5);
	shooter(127);
	forward_drive (180);
	wait(10);
	break_drive();
	wait(50);
	motor[intake] =-120;
	wait(45);
	motor[intake] =0;
	shooter(0);
	forward_drive (-180);
	wait(5);
	//left_drive (180);
	//right_drive (-180);
	//wait(8);
	left_drive(0);
	break_drive();
	wait (5);



	//
	//shooter(120);
	//wait (50);
	//motor[intake]= -120;
	//wait(30);
	//shooter(0);
	//motor[intake]= 0;
	//left_drive(-23);
	//right_drive(0);
	//wait(8);
	//break_drive();
	//wait(5);
	//forward_drive(120);
	//wait(50);
	//left_drive(0);
	//right_drive(0);
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
	startTask (LCD);

	while(true){
			//bLCDBacklight = true;

				left_drive(vexRT[Ch2]);
				right_drive(vexRT[Ch3]);

			if (vexRT[Btn5U] == true){

				motor[shooter_right] =127;
				motor[shooter_left] =127;
			}
			else if (vexRT [Btn5D] ==true){
				motor[shooter_right] =120;
				motor[shooter_left] =120;
			}
			else{

				motor[shooter_right] =0;
				motor [shooter_left] =0;
			}
			if (vexRT [Btn6U] ==true){
				motor [intake]=-127;
			}
			else if (vexRT [Btn6D] ==true) {
				motor[intake]=127;
			}
			else {
				motor[intake] = 0;
			}
			if (vexRT [Btn7U] ==0){

				motor[right_mid] = 0;
				motor[right_front] = 0;
				motor[right_back] = 0;
				motor[left_mid] = 0;
				motor[left_front] = 0;
				motor[left_back] = 0;
				motor[shooter_right] =0;
				motor[shooter_left]=0;
				motor[intake]=0;
			}


		}

}
