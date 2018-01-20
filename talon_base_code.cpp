#include<iostream>
#include<string>
#include<TimeRobot.h>
#include"ctre/Phoenix.h"
#include<Joystick.h>

class Robot: public frc::TimedRobot{
public:

	TalonSRX * talon = new TalonSRX(4);

	Joystick * stick = new Joystick(0);

	void TeleopPeriodic(){

		talon->Set(ControlMode::PercentOutput, stick->Gety());

	}
private:

};

START_ROBOT_CLASS(Robot)
