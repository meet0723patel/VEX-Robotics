#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    Catapult_Pot,   sensorPotentiometer)
#pragma config(Sensor, in2,    power,          sensorAnalog)
#pragma config(Sensor, in3,    D_gyro,         sensorGyro)
#pragma config(Sensor, dgtl1,  SONAR_F,        sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  SONAR_B,        sensorSONAR_cm)
#pragma config(Motor,  port1,           Chasis_L1,     tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveLeft)
#pragma config(Motor,  port2,           Chasis_L2,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           Chasis_L3,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           Ball_Intake_1, tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           Catapult_1,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           Catapult_2,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           Ball_Intake_2, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           Chasis_R3,     tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port9,           Chasis_R2,     tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port10,          Chasis_R1,     tmotorVex393HighSpeed_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int R_Freq = 50;
int R_Batt = 8628;
int P_Freq = R_Freq * (R_Batt / nImmediateBatteryLevel);
// Initial values for Sensors: in 1 = 854  in 2 = 2288
// Initial values for IMEs: port 1 = 0  port 2 = 0  port 3 = 0
int ERROR_GYRO = 120;

// TIME VOID FOR TIME THEORY
void wait(int temp)
{
	wait1Msec( P_Freq * temp);
}

// BALL INTAKE VOID
void Ball_Intake(int power)
{
	motor[Ball_Intake_1] = power;
	motor[Ball_Intake_2] = power;
}

int Initial_Value = 50;
int Final_Value = 650;
int Error_Margin = 75;
int intake_speed = 0;
int Descorer_Time = 100;
int wait_time = 20;

void Sonar_Chasis_RB(int distance, int speed)
{
	while(abs(SensorValue[SONAR_F]) > distance)
	{
		motor[Chasis_R1]=speed;
		motor[Chasis_R2]=speed;
		motor[Chasis_R3]=speed;
		motor[Chasis_L1]=speed;
		motor[Chasis_L2]=speed;
		motor[Chasis_L3]=speed;
	}
}


void Sonar_Chasis_FB(int distance, int speed)
{
	while(abs(SensorValue[SONAR_F]) < distance)
	{
		motor[Chasis_R1]=speed;
		motor[Chasis_R2]=speed;
		motor[Chasis_R3]=speed;
		motor[Chasis_L1]=speed;
		motor[Chasis_L2]=speed;
		motor[Chasis_L3]=speed;
	}
}

void Sonar_Chasis_RF(int distance, int speed)
{
	while(abs(SensorValue[SONAR_B]) >= distance)
	{
		motor[Chasis_R1]=speed;
		motor[Chasis_R2]=speed;
		motor[Chasis_R3]=speed;
		motor[Chasis_L1]=speed;
		motor[Chasis_L2]=speed;
		motor[Chasis_L3]=speed;
	}
}


void Sonar_Chasis_FF(int distance, int speed)
{
	while(abs(SensorValue[SONAR_B]) <= distance)
	{
		motor[Chasis_R1]=speed;
		motor[Chasis_R2]=speed;
		motor[Chasis_R3]=speed;
		motor[Chasis_L1]=speed;
		motor[Chasis_L2]=speed;
		motor[Chasis_L3]=speed;
	}
}


task LCD(){
	while(true){
		bLCDBacklight = true;
		string mainBattery;
		string expanderBattery;
		sprintf(mainBattery," %0.2f Volts",(float)nImmediateBatteryLevel/1000.0);
		sprintf(expanderBattery," %0.2f Volts",(float)SensorValue[power]/270.0);
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0,0,mainBattery);
		displayLCDString(1,0,expanderBattery);
		wait1Msec(1000);
	}
}

// This Shoots the ball and reloads the catapult, Just need to call the function
// Req: None
void Catapult_Launch() {
	while(SensorValue[Catapult_Pot] >= Initial_Value){
		motor[Catapult_1]=127;
		motor[Catapult_2]=127;
	}
	while(SensorValue[Catapult_Pot] <= Final_Value - Error_Margin){
		motor[Catapult_1]=127;
		motor[Catapult_2]=127;
	}
	motor[Catapult_1] = -50;
	motor[Catapult_2] = -50;
	wait1Msec(5);
	motor[Catapult_1] = 0;
	motor[Catapult_2] = 0;
}
void Brake(){
	motor[Chasis_L1]=50;
	motor[Chasis_L2]=-50;

	motor[Chasis_R1]=50;
	motor[Chasis_R2]=-50;
	wait1Msec(5);
	motor[Chasis_L1]=0;
	motor[Chasis_L2]=0;

	motor[Chasis_R1]=0;
	motor[Chasis_R2]=0;
}

// This runs both sides of the chasis
// Reg: speed and time
void Chasis(int speed,int time, bool brake){
	motor[Chasis_R1]=speed;
	motor[Chasis_R2]=speed;
	motor[Chasis_R3]=speed;
	motor[Chasis_L1]=speed;
	motor[Chasis_L2]=speed;
	motor[Chasis_L3]=speed;
	wait(time);
	motor[Chasis_R1]=0;
	motor[Chasis_R2]=0;
	motor[Chasis_R3]=0;
	motor[Chasis_L1]=0;
	motor[Chasis_L2]=0;
	motor[Chasis_L3]=0;
	if (brake == true)
	{
		Brake();
	}
}

// This runs only the right side of the chasis
// Req: speed and time
void Chasis_R(int speed,int time, bool brake){
	motor[Chasis_R1]=speed;
	motor[Chasis_R2]=speed;
	motor[Chasis_R3]=speed;
	wait(time);
	motor[Chasis_R1]=0;
	motor[Chasis_R2]=0;
	motor[Chasis_R3]=0;
	motor[Chasis_L1]=0;
	motor[Chasis_L2]=0;
	motor[Chasis_L3]=0;
	if (brake == true)
	{
		Brake();
	}
}

// This runs only the left side of the chasis
// Req: speed and time
void Chasis_L(int speed,int time, bool brake){
	motor[Chasis_L1]=speed;
	motor[Chasis_L2]=speed;
	motor[Chasis_L3]=speed;
	wait(time);
	motor[Chasis_R1]=0;
	motor[Chasis_R2]=0;
	motor[Chasis_R3]=0;
	motor[Chasis_L1]=0;
	motor[Chasis_L2]=0;
	motor[Chasis_L3]=0;
	if (brake == true)
	{
		Brake();
	}
}

// This turns the robot right
// Req: speed and time
void Turn_Right(int speed,int time, bool brake){
	motor[Chasis_L1]=-speed;
	motor[Chasis_L2]=-speed;
	motor[Chasis_L3]=-speed;
	motor[Chasis_R1]=speed;
	motor[Chasis_R2]=speed;
	motor[Chasis_R3]=speed;
	wait(time);
	motor[Chasis_R1]=0;
	motor[Chasis_R2]=0;
	motor[Chasis_R3]=0;
	motor[Chasis_L1]=0;
	motor[Chasis_L2]=0;
	motor[Chasis_L3]=0;
	if (brake == true)
	{
		Brake();
	}
}

// This turns the robot left
// Req: speed and time
void Turn_Left(int speed,int time, bool brake){
	motor[Chasis_L1]=speed;
	motor[Chasis_L2]=speed;
	motor[Chasis_L3]=speed;
	motor[Chasis_R1]=-speed;
	motor[Chasis_R2]=-speed;
	motor[Chasis_R3]=-speed;
	wait(time);
	motor[Chasis_R1]=0;
	motor[Chasis_R2]=0;
	motor[Chasis_R3]=0;
	motor[Chasis_L1]=0;
	motor[Chasis_L2]=0;
	motor[Chasis_L3]=0;
	if (brake == true)
	{
		Brake();
	}
}


// This spins the ball intake
// Change variable intake_speed anytime within code to change speed
// Req: none
task Intake(){
	while(true){
		Ball_Intake(intake_speed);
	}
}

// GYRO SENSOR
void turn(int degrees10, int speed){
	SensorValue[D_gyro] = 0;

	while(abs(SensorValue[D_gyro]) < degrees10 - ERROR_GYRO){
		motor[Chasis_R1]=speed;
		motor[Chasis_R2]=speed;
		motor[Chasis_R3]=speed;
		motor[Chasis_L1]=-speed;
		motor[Chasis_L2]=-speed;
		motor[Chasis_L3]=-speed;
	}
	Brake();
	motor[Chasis_R1]=0;
	motor[Chasis_R2]=0;
	motor[Chasis_R3]=0;
	motor[Chasis_L1]=0;
	motor[Chasis_L2]=0;
	motor[Chasis_L3]=0;
}

// TURN GYRO
/*void turn_other(int degrees10, int speed){
while(abs(SensorValue[D_gyro]) > degrees10 - 100){
motor[Chasis_R1]=speed;
motor[Chasis_R2]=speed;
motor[Chasis_R3]=speed;
motor[Chasis_L1]=-speed;
motor[Chasis_L2]=-speed;
motor[Chasis_L3]=-speed;
}
motor[Chasis_R1]=0;
motor[Chasis_R2]=0;
motor[Chasis_R3]=0;
motor[Chasis_L1]=0;
motor[Chasis_L2]=0;
motor[Chasis_L3]=0;
}*/


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
task Catapult(){
	while(true){
		if (vexRT(Btn5UXmtr2)==1){
			while(SensorValue[Catapult_Pot] >= Initial_Value){
				motor[Catapult_1]=127;
				motor[Catapult_2]=127;
			}
			while(SensorValue[Catapult_Pot] <= Final_Value - Error_Margin){
				motor[Catapult_1]=127;
				motor[Catapult_2]=127;
			}
			motor[Catapult_1] = -50;
			motor[Catapult_2] = -50;
			wait1Msec(5);
			motor[Catapult_1] = 0;
			motor[Catapult_2] = 0;
		}
		else if (vexRT(Btn5DXmtr2)==1){
			motor[Catapult_1]=127;
			motor[Catapult_2]=127;
		}
		else{
			motor[Catapult_1] = 0;
			motor[Catapult_2] = 0;
		}
	}
}
void pre_auton()
{
	startTask (LCD);
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
	startTask(Catapult);
	// sk (LCD);
	while (true)
	{
		if (vexRT(Btn6U)==1){
			//BRAKE
			//main controller
			motor[Chasis_L1]=50;
			motor[Chasis_L2]=-50;

			motor[Chasis_R1]=50;
			motor[Chasis_R2]=-50;
		}
		/*else if (vexRT(Btn6D)==1){
		//Opposite drive
		//main controller
		motor[Chasis_L1]=-vexRT(Ch2);
		motor[Chasis_L2]=-vexRT(Ch2);
		motor[Chasis_L3]=-vexRT(Ch2);

		motor[Chasis_R1]=-vexRT(Ch3);
		motor[Chasis_R2]=-vexRT(Ch3);
		motor[Chasis_R3]=-vexRT(Ch3);
		}*/
		else{
			//Normal Chasis drive
			//main controller
			motor[Chasis_L1]=vexRT(Ch3);
			motor[Chasis_L2]=vexRT(Ch3);
			motor[Chasis_L3]=vexRT(Ch3);

			motor[Chasis_R1]=vexRT(Ch2);
			motor[Chasis_R2]=vexRT(Ch2);
			motor[Chasis_R3]=vexRT(Ch2);
		}


		//INTAKE DRIVE
		//Move to partner eventually
		if (SensorValue(Catapult_Pot ) > Final_Value-200){
			Ball_Intake((127*vexRT(Btn6UXmtr2)) + (-127*vexRT(Btn6DXmtr2)));
		}
		else{
			Ball_Intake(0);
		}

}}

/*---------------------------------------------------------------------------*/

task autonomous()
{
	// START INTAKE TASK
	startTask (Intake);

	//Start writing auton code from here on...

	/*---------------------------------------------------------------------------*/ /*GET THE BALL FROM THE BOTTOM OF THE CAP*/

	// RESET GYRO BEFORE MOVING
	SensorValue[D_gyro] = 0;

	// RUN INTAKE TO INTAKE BALL
	intake_speed = 127;

	// GO TO BALL UNDER THE CAP
	Sonar_Chasis_FB(115, 75);

	// COAST STOP
	Chasis(0, 5, false);

	// GO BACK TO RED TILE
	Sonar_Chasis_RB(15, -100);

	// COAST STOP
	Chasis(0, 2, false);

	// BACK UP A BIT FROM THE ARENA WALL
	Sonar_Chasis_FB(3.4,100);

	/*---------------------------------------------------------------------------*/ /*RED SECTION FLAGS*/

	// RESET GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN 90 DEGRESS TOWARDS THE FLAGS
	turn(950, -35);

	// GO TOWARDS THE FLAGS A BIT
	Sonar_Chasis_RB(70, -50);

	// ADJUST ROBOT POSITION
	//RESET GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN TO THE ARENA WALL TO ADJUST ROBOT POSITION
	turn(950, 35);

	// BANG INTO THE WALL TO STRAIGHT THE BOT A BIT
	Sonar_Chasis_RB(5, -50);

	// RESET THE GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN 90 DEGREES TOWARDS THE FLAGS
	turn(950, -35);

	// COAST STOP
	Chasis(0, 1, false);

	// GO AND HIT BOTTOM FLAG AND BANG ON THE WALL
	Sonar_Chasis_RB(5, -50);

	// COAST BRAKE
	Chasis(0, 2, false);

	// GO INTO POSITION TO HIT TOP AND MIDDLE FLAG
	Sonar_Chasis_FB(73, 70);

	// COAST STOP
	Chasis(0, 20, false);

	// LAUNCH THE TWO BALLS
	Catapult_Launch();

	// COAST STOP
	Chasis(0, 20, false);

	/*---------------------------------------------------------------------------*/ /* MIDDLE SECTION FLAGS*/

	// GO BACK A BIT
	Chasis(50, 5, false);

	// RESET GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN 90 DEGRESS TO FACE TOWARDS THE BLUE SIDE OF THE FIELD
	turn(950, 35);

	// BANG INTO THE WALL TO ALLIGN THE BOT
	Chasis(-50, 20, false);

	// SET INTAKE SPEED TO 127
	intake_speed = 127;

	// GO TO THE BALL THATS UNDER CAP IN THE FRONT OF THE ARENA
	Sonar_Chasis_FB(115, 75);

	// COAST STOP
	Chasis(0, 5, false);

	// GO BACK A BIT
	Sonar_Chasis_RB(110, -75);

	// COAST STOP
	Chasis(0, 12, false);

	// REVERSE INTAKE TO FLIP CAP
	intake_speed = -127;

	// LINE UP TO THE BOTTOM FLAG
	Sonar_Chasis_FB(112, 75);

	// RESET GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN 90 DEGREES TOWARDS THE MIDDLE SECTION OF THE FLAGS
	turn(950, -35);

	// STOP INATAKE
	intake_speed = 0;

	// ALLIGN BOT WITH PLATFORM
	Chasis(50, 2, false);

	// GO AND HIT BOTTOM FLAG AND BANG INTO THE WALL
	Sonar_Chasis_RB(5, -50);

	// COAST STOP
	Chasis(0, 2, false);

	// REVERSE THE BOT TO LINE UP TO HIT TOP FLAG
	Sonar_Chasis_FB(73, 70);

	// COAST STOP
	Chasis(0, 20, false);

	// INTAKE BALL
	intake_speed = 127;

	// LAUNCH CATAPULT
	Catapult_Launch();

	// COAST STOP
	Chasis(0, 20, false);



	/*---------------------------------------------------------------------------*/ /*BLUE SECTION FLAGS*/

	// GO UP A BIT
	Chasis(-127, 2, false);

	// RESET GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN 90 DEGRESS TOWARDS THE BLUE SIDE
	turn(950, -35);

	// GO AND BANG INTO THE WALL
	Sonar_Chasis_RB(5, -50);

	// REVERSE TO ALLIGN BOT TO BLUE SIDE SECTION OF THE FLAGS
	Sonar_Chasis_FB(53, 70);

	// RESET GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN 90 DEGRESS TOWARDS THE BLUE SIDE SECTION OF THE FLAGS
	turn(950, -35);

	// REVERSE INTAKE
	intake_speed = -127;

	// GO AND HIT BOTTOM FLAGS
	Chasis(70, 20, false);

	// GO FRONT AND BACK
	Chasis(-70, 20, false);
	Chasis(70, 20, false);

	// GO BACK FROM THE FLAGS
	Sonar_Chasis_FF(10, 50);

	// COAST STOP
	Chasis(0, 20, false);

	/*---------------------------------------------------------------------------*/ /*PARKING*/

	// GO BACK FROM THE FLAGS
	Sonar_Chasis_FF(70, -50);

	// COAST STOP
	Chasis(0, 2,false);

	// RESET GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN 90 DEGRESS TOWARDS THE WALL
	turn(950, 35);

	// GO AND BANG INTO THE WALL
	Sonar_Chasis_RB(5, -50);

	// RESET GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN 90 DEGRESS AWAY FROM THE E
	turn(950, 35);

	// GO TO LINE UP FOR PLATFORM
	Sonar_Chasis_FB(114, 75);                                 // TRY USING BACK SENSOR

	// STOP INTAKE
	intake_speed = 0;

	// RESET GYRO BEFORE TURNING
	SensorValue[D_gyro] = 0;

	// TURN 90 DEGRESS AWAY FROM THE FLAGS
	turn(950, 35);

	// LINE UP WITH PLATFORM
	Chasis(-25, 20, false);

	// BANG INTO THE WALL
	Sonar_Chasis_RF(10, 50);

	// GO UP THE PLATFORM
	Chasis(-127, 40, false);

	// BRAKE
	Chasis(0, 20, true);

}
