#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl3,  Encod_L,        sensorQuadEncoder)
#pragma config(Sensor, dgtl11, Encod_R,        sensorQuadEncoder)
#pragma config(Motor,  port2,           right_front,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           shooter_right, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           right_mid,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           left_back,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           right_back,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           intake,        tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           shooter_left,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           left_front,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          left_mid,      tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("Motors")
#pragma platform(VEX)


// TIME THEORY BY TISSAN AND YAHYA
int R_Freq = 50;
int R_Batt = 8628;
int P_Freq = R_Freq * (R_Batt / nImmediateBatteryLevel);
// Initial values for Sensors: in 1 = 854  in 2 = 2288
// Initial values for IMEs: port 1 = 0  port 2 = 0  port 3 = 0

// TIME VOID FOR TIME THEORY
void wait(int temp)
{
	wait1Msec( P_Freq * temp);
}


void moveBase(int speed)
{
	motor[right_front] = speed;
	motor[right_mid] = speed;
	motor[right_back] = speed;
	motor[left_front] = speed;
	motor[left_mid] = speed;
	motor[left_back] = speed;
}

void brake()
{
  motor[right_front] = 50;
  motor[right_mid] = -50;
  motor[left_front] = 50;
  motor[left_mid] = -50;
}

void _chasis(int speed, int time, bool temp)
{
	moveBase(speed);
	wait(time);
	if (temp == true)
	{
		brake();
		wait1Msec(1000);
	}
}

void rightBase(int speed)
{
	motor[right_front] = speed;
	motor[right_mid] = speed;
	motor[right_back] = speed;
}
void leftBase(int speed)
{
	motor[left_front] = speed;
	motor[left_mid] = speed;
	motor[left_back] = speed;
}

void turnBase(int speed) // positve is clockwise
{
	motor[right_front] = speed;
	motor[right_mid] = speed;
	motor[right_back] = speed;
	motor[left_front] = -speed;
	motor[left_mid] = -speed;
	motor[left_back] = -speed;
}
void break_drive(){
	rightBase(0);
	leftBase(0);
}
void straight (int speed)
{
	//one of the encoder values will be negative just multiple the value by -1 at the beginning and set it to a variable to make it easier
	leftBase(speed);
	rightBase(speed);
	if (SensorValue(abs(Encod_R))>SensorValue (abs(Encod_L)))
	{
		leftBase(speed);
		rightBase(speed-2);
	}
	else if (SensorValue (abs(Encod_R))< SensorValue(abs (Encod_L)))
	{
		leftBase(speed-2);
		rightBase(speed);
	}
}

void straight_dist (int dist, int power)
{
	//Encoder ticks = (360 / circumference) * Distance to travel
	//circumference = 4* pi = 28.67 rounded up to 29 due to floating point error in robotc
	//use this formula to drive straight for a certain distance



	int tickGoal = (29*dist)/10;
	int totalTicks = 0;
	int slavePower = power -5;
	int error =0;

	int kp =5;

	SensorValue[Encod_L] =0;
	SensorValue[Encod_R] =0;

	while (abs (totalTicks ) <tickGoal )
	{
		motor[right_front] = power;
		motor[right_mid] = power;
		motor[right_back] = power;
		motor[left_front] = power;
		motor[left_mid] = power;
		motor[left_back] = power;
		error = SensorValue[Encod_L] -(-1*(SensorValue [Encod_R] ));
		slavePower += error / kp;

		SensorValue [Encod_L] =0;
		SensorValue [Encod_R] =0;

		wait1Msec (100);

		totalTicks += SensorValue[Encod_L];
	}
	leftBase(0);
	rightBase(0);
}

void slow_straight (int dist)
{
	straight_dist (dist, 20);
}

//TICKS/INCH FORMULA                                                 //TEST THIS OUT
//reading: ticks -- 627.2 ticks/revolution
//1 turn of the wheels -- 4 inch wheels == 627.2*2 ticks
//1 turn of each wheel 4*pi inches
//4*pi inches = 627.2*2 ticks
//ticks/inch = 627.2*2/(4*pi) = 99.82198

//when my error is 30
//the actual error is inches - 30

const float ticksperinch = 99.82198;
const float ticksPerTurn = 2207; // ? not sure you might want to test it first // when you doing this turn robot 360 and add bot encoder values together
const int wheel_base = 11.5; // make sure its in inches
const int wheel_dia = 360;

int fixTimerValue(float rawSeconds)
{
	int miliseconds;
	miliseconds = rawSeconds*1000;
	if(miliseconds < 250)
	{
		miliseconds = 250;
	}
	return miliseconds;
}

int inchToTicks (float inch)
{
	int ticks;
	ticks = inch*ticksperinch;
	return ticks;
}

int degreesToTicks(float degrees)
{
	int ticks;
	ticks = degrees*ticksPerTurn/360;
	return ticks;
}

/*int degreesToTicks(float degrees)
{
int ticks;
ticks = degrees*wheel_base/wheel_dia;
return ticks;
}*/

void PIDbaseControl(float target, float waitTime, float maxPower = 127)
{
	float Kp = 0.5;
	float Ki = 0.0009;
	float Kd = 0.5;
	int error;

	float proportion;
	int integralRaw;
	float integral;
	int lastError;
	int derivative;

	const float integralActiveZone = inchToTicks(3);
	float integralPowerLimit = 50/Ki;

	int finalPower;

	float Kp_C = 0.01;
	int error_drift;
	float proportion_drift;

	bool timerBool = true;

	SensorValue[Encod_L] = 0;
	SensorValue[Encod_R] = 0;

	clearTimer(T1);

	while(time1[T1] < fixTimerValue(waitTime))
	{
		error = inchToTicks(target) - (SensorValue[Encod_L] + SensorValue[Encod_R]);
		proportion = Kp*error;
		if(abs(error) < integralActiveZone && error != 0)
		{
			integralRaw = integralRaw + error;
		}
		else
		{
			integralRaw = 0;
		}
		if (integralRaw > integralPowerLimit)
		{
			integralRaw = integralPowerLimit;
		}
		if (integralRaw < -integralPowerLimit)
		{
			integralRaw = -integralPowerLimit;
		}
		integral = Ki*integralRaw;
		derivative = Kd*(error - lastError);
		lastError = error;
		if (error == 0)
		{
			derivative = 0;
		}
		finalPower = proportion + integral + derivative; //proportion+derivative+integral
		if (finalPower > maxPower)
		{
			finalPower = maxPower;
		}
		else if (finalPower < -maxPower)
		{
			finalPower = -maxPower;
		}

		error_drift = SensorValue[Encod_R] - SensorValue[Encod_L];
		proportion_drift = Kp_C * error_drift;

		leftBase(finalPower+proportion_drift);
		rightBase(finalPower-proportion_drift);
		wait1Msec(40);

		if (error < 30)
		{
			timerBool = false;
		}
		if (timerBool)
		{
			clearTimer(T1);
		}
	}
	moveBase(0);
}

void PIDbaseTurn(float target, float waitTime, float maxPower = 127)
{
	float Kp = 0.75;
	float Ki = -0.0009;
	float Kd = 0.5;
	int error;

	float proportion;
	int integralRaw;
	float integral;
	int lastError;
	int derivative;

	const float integralActiveZone = inchToTicks(3);
	float integralPowerLimit = 50/Ki;

	int finalPower;

	bool timerBool = true;

	SensorValue[Encod_L] = 0;
	SensorValue[Encod_R] = 0;

	clearTimer(T1);

	while(time1[T1] < fixTimerValue(waitTime))
	{
		error = degreesToTicks(target) - ((SensorValue[Encod_L]) - (-1*SensorValue[Encod_R]));
		proportion = Kp*error;
		if(abs(error) < integralActiveZone && error != 0)
		{
			integralRaw = integralRaw + error;
		}
		else
		{
			integralRaw = 0;
		}
		if (integralRaw > integralPowerLimit)
		{
			integralRaw = integralPowerLimit;
		}
		if (integralRaw < -integralPowerLimit)
		{
			integralRaw = -integralPowerLimit;
		}
		integral = Ki*integralRaw;
		derivative = Kd*(error - lastError);
		lastError = error;
		if (error == 0)
		{
			derivative = 0;
		}
		finalPower = proportion + integral + derivative; //proportion+derivative+integral
		if (finalPower > maxPower)
		{
			finalPower = maxPower;
		}
		else if (finalPower < -maxPower)
		{
			finalPower = -maxPower;
		}

		turnBase(finalPower);
		wait1Msec(40);

		if (error < 30)
		{
			timerBool = false;
		}
		if (timerBool)
		{
			clearTimer(T1);
		}
	}
	turnBase(0);
}

void shooter(int speed)
{
	motor[shooter_left] =speed;
	motor[shooter_right] =speed;
}


task main()
{

	SensorValue[Encod_L] = 0;
	SensorValue[Encod_R] = 0;
	/*function library
	moveBase (speed)
	rightBase(speed)
	leftBase(speed)
	turnBase(speed)
	break_Drive()
	straight_dist(dist, power)
	slow_straight(dist)
	shooter(speed)
	PIDbaseControl (target, waittime, maxpower) */

	//distance measured in 10ths of a inch



}
