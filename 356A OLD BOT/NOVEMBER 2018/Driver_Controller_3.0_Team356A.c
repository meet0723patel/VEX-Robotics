#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    Catapult_Pot,   sensorPotentiometer)
#pragma config(Sensor, in2,    power,          sensorAnalog)
#pragma config(Motor,  port1,           Chasis_L1,     tmotorVex393HighSpeed_HBridge, openLoop, reversed, driveLeft, encoderPort, dgtl3)
#pragma config(Motor,  port2,           Chasis_L2,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, dgtl3)
#pragma config(Motor,  port3,           Chasis_L3,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, dgtl3)
#pragma config(Motor,  port4,           Ball_Intake,   tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           Catapult_1,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           Catapult_2,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           Descorer,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           Chasis_R3,     tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight, encoderPort, dgtl1)
#pragma config(Motor,  port9,           Chasis_R2,     tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight, encoderPort, dgtl1)
#pragma config(Motor,  port10,          Chasis_R1,     tmotorVex393HighSpeed_HBridge, openLoop, driveRight, encoderPort, dgtl1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//--------------------------------//
// YAHYA MUHAMMAD ----------------//
// 356A PRE-WOLBURN ROBOT --------//
// FOR A SINGLE CONTROLLER -------//
// NOVEMBER 18, 2018 -------------//
//--------------------------------//

int Initial_Value = 50;
int Final_Value = 775;
int Error_Margin = 75;

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


task main()
{
	//CATAPULT
	//IS IN TASK ABOVE
	//Switch to Partner Controller
	startTask(Catapult);
	startTask(LCD);


	while(true){


		if (vexRT(Btn6D)==1){
			//BRAKE
			//main controller
			motor[Chasis_L1]=50;
			motor[Chasis_L2]=-50;

			motor[Chasis_R1]=50;
			motor[Chasis_R2]=-50;
		}
		else if (vexRT(Btn6U)==1){
			//Opposite drive
			//main controller
			motor[Chasis_L1]=-vexRT(Ch2);
			motor[Chasis_L2]=-vexRT(Ch2);
			motor[Chasis_L3]=-vexRT(Ch2);

			motor[Chasis_R1]=-vexRT(Ch3);
			motor[Chasis_R2]=-vexRT(Ch3);
			motor[Chasis_R3]=-vexRT(Ch3);
		}
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
		motor[Ball_Intake] = (-127*vexRT(Btn6UXmtr2)) + (127*vexRT(Btn6DXmtr2));

		//Descorer for Cap
		//Move to partner eventually
		motor[Descorer] = (-127*vexRT(Btn5D)) + (127*vexRT(Btn5U));
	}
}