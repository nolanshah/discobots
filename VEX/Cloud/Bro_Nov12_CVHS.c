#pragma config(Sensor, in1,    armPot,              sensorPotentiometer)
#pragma config(Sensor, in2,    clawPot,             sensorPotentiometer)
#pragma config(Sensor, in3,    lineFollower,        sensorLineFollower)
#pragma config(Sensor, dgtl1,  rightEnc,            sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEnc,             sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  sonar,               sensorSONAR_cm)
#pragma config(Motor,  port1,           arm,           tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           right,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           left,          tmotorNormal, openLoop)
#pragma config(Motor,  port6,           right2,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           left2,         tmotorNormal, openLoop)
#pragma config(Motor,  port8,           claw,          tmotorNormal, openLoop)
#pragma config(Motor,  port10,          arm2,          tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

void pre_auton()
{
	SensorValue[armPot] = 0;
	SensorValue[clawPot] = 0;
	SensorValue[rightEnc] = 0;
	SensorValue[leftEnc] = 0;
}

void StopDrive();
void Stop();

//Variables for program to run

//variables for positions of the potentiometers
int goal_high_high = 3289;
int goal_high_low = 2900;
int goal_low_high = 3265;
int goal_low_low = 2470;
int floor_pos = 2220;
int claw_open = 2006;
int claw_closed = 3520;
int safety_time = 4;

//variables dealing with the dimensions of robot.
int robot_width = 26;//width of base of robot in cm.

/*
MoveRobot moves the robot either forward or backwards.
Ticks is the number of ticks to move the robot forward by. Enter 0 to disable ticks.
Time is how long the robot will run if encoders are disabled. Enter 0 to disable time.
If time and ticks are both disabled, then the robot will run forward at the specified speed without end.
*/
void MoveRobot (int power, int time, int ticks)
{
  SensorValue[leftEnc] = 0;
  SensorValue[rightEnc] = 0;
  ClearTimer(T2);
  if (ticks > 0){
    while((abs(SensorValue[rightEnc]) + abs(SensorValue[leftEnc]))/2 < ticks && time1[T2] < time*2000){
      motor[left] = power;
      motor[left2] = power;
      motor[right] = power;
      motor[right2] = power;
    }
    StopDrive();
  }
  else if(time > 0){
    time1[T2] = 0;
    while(time1[T2] < time){
      motor[left] = power;
      motor[left2] = power;
      motor[right] = power;
      motor[right2] = power;
    }
    StopDrive();
  }
  else{
    motor[left] = power;
    motor[left2] = power;
    motor[right] = power;
    motor[right2] = power;
  }
}

/*
MoveArm moves the arm to a certain position that is specified at the power that is specified.
The program doesnt care what position the arm starts at and will move to the specified position.
*/
void MoveArm (int power, int pos){
  do{
    if (SensorValue[armPot] < pos){
      motor[arm] = power;
      motor[arm2] = power;
    }
    else if(SensorValue[armPot] > pos){
      motor[arm] = -0.1*power;
      motor[arm2] = -0.1*power;
    }
    else{
      motor[arm] = 15;
      motor[arm2] = 15;
    }
  }while(SensorValue[armPot] < pos-20 || SensorValue[armPot] > pos+20);
  Stop();
  motor[arm] = 15;
  motor[arm2] = 15;
}

/*
MoveClaw opens or closes the claw to match the specified position at the specified power.
*/
void MoveClaw (int power, int pos){
  do{
    if (SensorValue[clawPot] < pos){
      motor[claw] = power;
    }
    else if(SensorValue[clawPot] > pos){
      motor[claw] = -power;
    }
    else{
      motor[claw] = 0;
    }
  }while(SensorValue[clawPot] <= pos-35 || SensorValue[clawPot] >= pos+35);
  motor[claw] = 0;
  Stop();
}

/*
PivotTurn turns the robot in place at the specified power.
The disabling of time and ticks works the same way as in the MoveRobot function.
Positive power turns left and negative power turns right. THINK RADIANS!!!
*/
void PivotTurn (int power, int time, int ticks){
  SensorValue[leftEnc] = 0;
  SensorValue[rightEnc] = 0;
  ClearTimer(T2);
  if (ticks > 0){
    while((abs(SensorValue[rightEnc]) + abs(SensorValue[leftEnc]))/2 < ticks && time1[T2] < time*2000){
      motor[left] = -power;
      motor[left2] = -power;
      motor[right] = power;
      motor[right2] = power;
    }
    StopDrive();
  }
  else if(time > 0){
    time1[T2] = 0;
    while(time1[T2] < time){
      motor[left] = -power;
      motor[left2] = -power;
      motor[right] = power;
      motor[right2] = power;
    }
    StopDrive();
  }
  else{
    motor[left] = -power;
    motor[left2] = -power;
    motor[right] = power;
    motor[right2] = power;
  }
}

/*
VeerTurn has the robot move forward while veering to one side or the other at a specified speed.
The speed is for the speed of the center of the robot. Radius should be entered in cm.
Positive radius turns left, negative radius turns right.
*/
void VeerTurn (int power, int radius, int ticks, int time){
  int right = 0;
  int left = 0;

  right = (power*(radius + (robot_width/2)))/radius;
  left = (power*(radius - (robot_width/2)))/radius;

  SensorValue[leftEnc] = 0;
  SensorValue[rightEnc] = 0;
  ClearTimer(T2);
  if(ticks > 0){
    while((abs(SensorValue[rightEnc]) + abs(SensorValue[leftEnc]))/2 < ticks && time1[T2] < time*2000){
      motor[right] = right;
      motor[right2] = right;
      motor[left] = left;
      motor[left2] = left;
    }
    StopDrive();
  }
  else if(time > 0){
    time1[T2] = 0;
    while(time1[T2] < time){
      motor[right] = right;
      motor[right2] = right;
      motor[left] = left;
      motor[left2] = left;
    }
    StopDrive();
  }
  else{
    motor[right] = right;
    motor[right2] = right;
    motor[left] = left;
    motor[left2] = left;
  }
}

//Stop is a function to stop all used motors for use in both autonomous and tele-op modes.
void Stop(){
  motor[arm] = 0;
  motor[arm2] = 0;
  motor[claw] = 0;
  motor[right] = 0;
  motor[right2] = 0;
  motor[left] = 0;
  motor[left2] = 0;
}

void StopDrive(){
  motor[left] = 0;
  motor[right] = 0;
  motor[right2] = 0;
  motor[left2] = 0;
}

task autonomous()
{
  SensorValue[leftEnc] = 0;
  SensorValue[rightEnc] = 0;
  MoveClaw(128,claw_closed);//close claw on stck with full power.
  wait1Msec(100);
  PivotTurn(-64,4,33);//Turn right to face goal
  wait1Msec(100);
  MoveArm(80, goal_low_high);//Raises arm to above the low goal's top.
  MoveRobot(64,2,70);//move robot forward to go after first stack
  wait1Msec(100);
  MoveArm(50, goal_low_low);//Lower arm to score on goal
  wait1Msec(100);
  MoveClaw(64,claw_open);//open claw to release tubes on goal

}

task usercontrol()
{
	while (true)
	{

	  if(abs(vexRT[Ch3]) > 20 || abs(vexRT[Ch4]) > 20){
	    motor[right] = vexRT[Ch3] - vexRT[Ch4];        // arcade drive
      motor[right2] = vexRT[Ch3] - vexRT[Ch4];
      motor[left] = vexRT[Ch3] + vexRT[Ch4];
      motor[left2] = vexRT[Ch3] + vexRT[Ch4];
	  }
	  else{
	    StopDrive();
	  }

	  if (vexRT[Btn6U] != 0 ||vexRT[Btn5U] != 0 )
      motor[claw]= 110;
    else if(vexRT[Btn6D] != 0 || vexRT[Btn5D] != 0)
      motor[claw] = -63;
    else
      motor[claw] = 0;

    motor[arm] = vexRT[Ch2];
    motor[arm2] = vexRT[Ch2];

	}
}
