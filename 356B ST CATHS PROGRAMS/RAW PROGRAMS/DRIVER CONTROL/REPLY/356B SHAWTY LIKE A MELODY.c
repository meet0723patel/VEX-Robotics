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

#pragma DebuggerWindows("debugStream")

// -------------------------------------------------- AUTONOMOUS RECORDER -------------------------------------------------- //
//            Records driver control actions to motor statements that can be used as an autonomous program.                  //
// ------------------------------------------------------------------------------------------------------------------------- //

// HOW TO USE THIS RECORDER:
// 1. Paste the motor control code from your competition template at line 1 above.
// 2. Paste the user control code from your competition template in the userControlCode function below.
// 3. Adjust R_mSec or R_Freq values if you want a different length or frequency of recording
// 4. Adjust minBattVoltage as desired.  Using a high-charge battery for recording and playback will improve playback consistancy.
// 5. Have a game field set up and a driver ready to drive the bot for an autonomous run.
// 6. While using the programming cable with the controller connected to the robot via vexNet, download this code.
// 7. Press start to run the code. There will be a 3 second count down before user control and recording starts.
// 8. Copy the text from the debug stream window into your program's autonomous task.
// 9. Downdoad your program and test the autonomous using the competition control debug window or a field switch.

int R_mSec = 15000; 				// 15000, length of autonomous redording in milliseconds
int R_Freq = 50; 						// 50, the frequency of the recording in milliseconds. A lower number may result in errors.
int minBattVoltage = 7800; 	// 7800, the minimum battery voltage at which a recording will be made
/*------------------------*/



// function to hold user control code
void userControlCode()
{
	while(true){

		// Drive button to flip front and back
		if (vexRT[Btn5U] ==1){
			driveL(-vexRT[Ch2]);
			driveR(vexRT[Ch3]);
		}
		else{
			driveL(vexRT[Ch3]);
			driveR(-vexRT[Ch2]);
		}

		// Button for the lift up and down
		if (vexRT[Btn6UXmtr2] == 1){
			lift(120);
		}
		else if(vexRT[Btn6DXmtr2] == 1){
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
		if (vexRT[Btn8UXmtr2] == 1){
			_intake(120);
		}
		// So the intake will let the balls out
		else if(vexRT[Btn8DXmtr2] == 1){
			_intake(-120);
		}
		else{
			_intake(0);
		}

		// Brake for the chassis
		if (vexRT[Btn6U] == 1){
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

		// ycable 1 is Left side
		// ycable 2 is Right side
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////                        NOTHING BELOW NEEDS TO BE EDITED FOR THE PROGRAM TO WORK                         ////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int loopCounter; 							// the number of each loop of code
int	loopOfLastChange; 				// last loop any motor value changed
int motorValue_Last[10]; 			// motor value of the previous loop
int sensorValue_Last[20]; 		// sensor values of the previous loop
int imeValue_Last[10]; 				// ime values of the previous loop

bool motorChange = false; 		// any motor change within the current loop sets to true
bool sensorPresent = true; 	// if any sensor is installed, code sets to true
bool sensorChange = false; 		// any sensor change within the current loop sets to true
bool imePresent = false; 			// if any IME is installed, code sets to true
bool imeChange = false; 			// any IME change within the current loop sets to true

// task to record motor and sensor value changes to the debug stream
task recordAutonomous()
{
	// write initial sensor values for all sensors to debug stream as comments
	if (sensorPresent == true) // only record sensors if present
	{
		writeDebugStream("// Initial values for Sensors: ");
		for (int s = 0; s < 8; s++) // analogue sensors
		{
			if (SensorType[s] != 0) // sensor exists
			{
				writeDebugStream("in %d", s+1); // write values to the debugStream as comments
				writeDebugStream(" = %d  ", SensorValue(s));
				sensorValue_Last[s] = SensorValue(s);
			}
		}
		for (int s = 8; s < 20; s++)  // digital sensors
		{
			if (SensorType[s] != 0 && SensorType[s] != 81 && SensorType[s] != 56) // sensor exists, is not OSE/sonic 2
			{
				writeDebugStream("dgtl %d", s-7); // write values to the debugStream as comments
				writeDebugStream(" = %d  ", SensorValue(s));
				sensorValue_Last[s] = SensorValue(s);
			}
		}
		writeDebugStreamLine(" ");
	}
	if (imePresent == true) // only record ime if present
	{
		writeDebugStream("// Initial values for IMEs: ");
		for (int m = 0; m < 10; m++)
		{
			if (getEncoderForMotor(m) != -1) // IME exists
			{
				writeDebugStream("port %d", m+1); // write IME values to the debugStream as comments
				writeDebugStream(" = %d  ", nMotorEncoder[m]);
				imeValue_Last[m] = nMotorEncoder[m];
			}
		}
		writeDebugStreamLine(" ");
	}

	while(true)
	{
		for (int m = 0; m < 10; m++)
		{
			// create comments following and preceeding the motor command lines
			if(abs(motor[m] - motorValue_Last[m]) >= 3 && motorChange == false) // first motor change in a loop
			{
				// wait command and comment appended to previous loop motor lines so that wait of that loop can be calculated
				writeDebugStream("wait1Msec( P_Freq * %d );", (loopCounter - loopOfLastChange)); // wait command
				writeDebugStreamLine("		// wait %d", (loopCounter - loopOfLastChange) * R_Freq);	// wait comment
				writeDebugStreamLine(" ");
				writeDebugStream("// %d  ", loopCounter * R_Freq);	//print the current time of the autonomous

				// RECORD SENSOR VALUES
				if (sensorPresent == true) // only record sensors if present
				{
					writeDebugStream("Sensors: ");
					for (int s = 0; s < 8; s++)  // analogue sensors
					{
						if (SensorType[s] != 0 && abs(SensorValue(s) - sensorValue_Last[s]) >= 3) // sensor exists and has changed by 3
						{
							writeDebugStream("in %d", s+1); // write values to the debugStream as comments
							writeDebugStream(" = %d  ", SensorValue(s));
							sensorValue_Last[s] = SensorValue(s);
							sensorChange = true;
						}
					}
					for (int s = 8; s < 20; s++)   // digital sensors
					{
						if (SensorType[s] != 0 && SensorType[s] != 81 && SensorType[s] != 56 && abs(SensorValue(s) - sensorValue_Last[s]) >= 3) // sensor exists, is not OSE/sonic 2 and has changed by 3
						{
							writeDebugStream("dgtl %d", s-7); // write values to the debugStream as comments
							writeDebugStream(" = %d  ", SensorValue(s));
							sensorValue_Last[s] = SensorValue(s);
							sensorChange = true;
						}
						if (s == 19 && sensorChange == false) // all sensors checked and none changed
						{
							writeDebugStream("no change  ");
						}
					}
				}

				// RECORD IME VALUES
				if (imePresent == true) // only record ime if present
				{
					writeDebugStream("IMEs: ");
					for (int m = 0; m < 10; m++)
					{
						if (getEncoderForMotor(m) != -1 && nMotorEncoder[m] != imeValue_Last[m]) // IME exists and has changed
						{
							writeDebugStream("port %d", m+1); // write IME values to the debugStream as comments
							writeDebugStream(" = %d  ", nMotorEncoder[m]);
							imeValue_Last[m] = nMotorEncoder[m];
							imeChange = true;
						}
						if (m == 9 && imeChange == false) // all IMEs checked and none changed
						{
							writeDebugStream("no change  ");
						}
					}
				}
				writeDebugStreamLine(" ");
			}

			// CREATE MOTOR COMMANDS
			if(abs(motor[m] - motorValue_Last[m]) >= 3 ) // if motorValue changes from last loop by 3 or more
			{
				writeDebugStream("motor[ port%d", m+1); // write changed values to the debugStream as motor[] commands
				writeDebugStream(" ] = %d;", motor[m]);
				writeDebugStreamLine(" ");
				motorValue_Last[m] = motor[m]; // update motorVaule_Last
				motorChange = true;
			}
		}

		// UPDATE VARIABLES
		if ( motorChange == true ) // if any motor value changed this loop
		{
			loopOfLastChange = loopCounter; // restart LastChange count
		}
		motorChange = false;
		sensorChange = false;
		imeChange = false;
		loopCounter++;

		wait1Msec(R_Freq);
	}
}

task main()
{
	clearDebugStream();	// clear previous recordings

	if (nImmediateBatteryLevel >= minBattVoltage)
	{
		// initialize sensorValue_Last array to 0
		for (int s = 0; s < 20; s++)
		{
			sensorValue_Last[s] = 0;
			if (SensorType[s] == 46)
			{
				writeDebugStreamLine("// Hang on 2 seconds, resetting gyro.");
				SensorType[s] = sensorNone;
				wait1Msec(500);
				SensorType[s] = sensorGyro; // reset gyro(s) to 0
				wait1Msec(1500);
			}
			if (SensorType[s] == 80)
			{
				SensorValue(s) = 0; // set OSE sensors to 0
			}
			if (SensorValue[s] != 0)
			{
				if (sensorPresent == false){writeDebugStreamLine("// Sensor(s) detected, nice!");}
				sensorPresent = true;
			}
		}

		// initialize motorValue_Last array to 0
		for (int m = 0; m < 10; m++)
		{
			motorValue_Last[m] = 0;
			imeValue_Last[m] = 0;
			if (getEncoderForMotor(m) != -1) // if there is an IME
			{
				nMotorEncoder[m] = 0; // set IME to 0
				if (imePresent == false){writeDebugStreamLine("// Integeated Encoder Module(s) detected, sweet!");}
				imePresent = true;
			}
		}

		// write sensor status to debug stream
		if (sensorPresent == false)
		{
			writeDebugStreamLine("// Sensors NOT detected.");
		}
		if (imePresent == false)
		{
			writeDebugStreamLine("// Integeated Encoder Module(s) NOT detected.");
		}
		if (sensorPresent == false && imePresent == false)
		{
			writeDebugStreamLine("// If you install sensors or IMEs, this program will record their value at each motor change as a comment.");
		}

		// countdown in debug stream
		writeDebugStream("// Begin recording in: ");
		wait1Msec(250);
		for (int n = 3; n>0 ; n--)
		{
			writeDebugStream (" %d", n);
			wait1Msec(250);
			for (int i = 0; i<4 ; i++)
			{
				writeDebugStream (" .");
				wait1Msec(250);
			}
		}

		// write header for autonomous code
		writeDebugStreamLine(" ");
		writeDebugStreamLine("// BEGIN AUTONOMOUS RECORDING");
		writeDebugStreamLine("/*<<<<---- START COPY ----------------------------------------------------------------------*/");
		writeDebugStreamLine("int R_Freq = %d;", R_Freq);
		writeDebugStreamLine("int R_Batt = %d;", nImmediateBatteryLevel);
		writeDebugStreamLine("int P_Freq = R_Freq * (R_Batt / nImmediateBatteryLevel)");

		// start recording
		startTask (recordAutonomous);

		// allow driver control for R_mSec milliseconds
		clearTimer(T1);
		while (time1[T1] < R_mSec)
		{
			userControlCode();
		}

		// stop recording
		stopTask (recordAutonomous);

		// write footer for recording to debug window
		writeDebugStream("wait1Msec( P_Freq * %d );", (loopCounter - loopOfLastChange)); // wait command
		writeDebugStreamLine("		// wait %d", (loopCounter - loopOfLastChange) * R_Freq);	// wait comment
		writeDebugStreamLine(" ");
		writeDebugStreamLine("// %d ", R_mSec); // end time comment

		writeDebugStreamLine("for (int i = 0; i < 10; i++){ motor[i] = 0; } // stop all motors");
		writeDebugStreamLine("/*--------------------------------------------------------------------------END COPY---->>>>*/");
		writeDebugStreamLine("// END AUTONOMOUS RECORDING");

		// stop all motors
		for (int i; i < 10; i++){	motor[i] = 0; }
	}
	else
	{
		writeDebugStream("RECORDING ABORTED, BATTERY VOLTAGE IS BELOW %d", minBattVoltage);
		writeDebugStreamLine(" ( %d )", nImmediateBatteryLevel);
		writeDebugStream("replace battery and try again");
	}
}