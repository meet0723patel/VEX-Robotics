#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(Sensor, in2,    power,          sensorAnalog)
#pragma config(Sensor, in3,    gyro,         sensorGyro)
#pragma config(Sensor, in4,    Catapult_Pot,   sensorPotentiometer)
#pragma config(Sensor, dgtl1,  SONAR_F,        sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  SONAR_B,        sensorSONAR_cm)
#pragma config(Sensor, dgtl5,  Encod_R,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  Encod_L,        sensorQuadEncoder)
#pragma config(Motor,  port1,           Chasis_R1,     tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveRight, encoderPort, dgtl5)
#pragma config(Motor,  port2,           Ball_Intake_1, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           Chasis_R2,     tmotorVex393HighSpeed_MC29, openLoop, driveRight, encoderPort, dgtl5)
#pragma config(Motor,  port4,           Chasis_R3,     tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight, encoderPort, dgtl5)
#pragma config(Motor,  port5,           Catapult_1,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           Catapult_2,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           Chasis_L3,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, dgtl7)
#pragma config(Motor,  port8,           Chasis_L2,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, dgtl7)
#pragma config(Motor,  port9,           Ball_Intake_2, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          Chasis_L1,     tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveLeft, encoderPort, dgtl7)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("Motors")
#pragma platform(VEX)

#include "library/pid_h.h"
#define RD_ENC SensorValue[Encod_R]
#define left_enc SensorValue[Encod_L]

//function for the right chassis
void right_chassis(int speed){
	motor[Chasis_R1]=speed;
	motor[Chasis_R2]=speed;
	motor[Chasis_R3]=speed;
}
//function for the left chassis
void left_chassis(int speed){
	motor[Chasis_L1]=speed;
	motor[Chasis_L2]=speed;
	motor[Chasis_L3]=speed;
}

void drive_chassis_init(){
	right_enc = 0;
	left_enc = 0;
}

pid drivebase;
void drivebase_PID_init(){
	drivebase.kP = 0.5;
	drivebase.kI = 0.0009;
	drivebase.kD = 2.5;
}
void drive_chassis(int speed){
	left_chassis(speed);
	right_chassis(speed);
}
void setDriveTarget(int distance){
	drivebase.target = distance;
}

task drivebase_PID() {
	drivebase_PID_init();
	while(true){

		if (drivebase.target > 0)
		{
			drivebase.error = drivebase.target - abs(left_enc);
		}
		else
		{
			drivebase.error = drivebase.target + abs(left_enc);
		}

		if(abs(drivebase.error)<250)
		drivebase.integral += drivebase.error;
		else
		drivebase.integral = 0;

		if(abs(drivebase.error)<200)
			drivebase.integral += 1;
		else
			drivebase.integral = 0;


		if(drivebase.error == 0) { drivebase.integral = 0; }

		drivebase.derivative = drivebase.error - drivebase.last_error;
		drivebase.last_error = drivebase.error;

		drive_chassis((drivebase.kP*drivebase.error)+(drivebase.integral*drivebase.kI)+(drivebase.derivative*drivebase.kD));
		delay(25)
}}

void turn(int speed, int val){
	while((abs(RD_ENC)) < abs(val)){
		left_chassis(speed);
		right_chassis(-speed);
	}
}

task main()
{
	//drive_chassis_init();
	turn(100, 82);
}
