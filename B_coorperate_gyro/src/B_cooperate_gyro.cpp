#include <Drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <Spark.h>
#include <VictorSP.h>
#include <Encoder.h>
#include <PIDController.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <WPILib.h>
#include <SampleRobot.h>
#include <Victor.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <CameraServer.h>
#include <AnalogGyro.h>
#include <GyroBase.h>
#include <String.h>
#include <ADXRS450_Gyro.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

using namespace std;
class GyroSample : public frc::IterativeRobot {

	WPI_TalonSRX *leftDrive = new WPI_TalonSRX(1);
	WPI_TalonSRX *rightDrive = new WPI_TalonSRX(2);
	VictorSP armBack {4};
	VictorSP armLeft {5};
	VictorSP armRight {0};
	VictorSP dumpleft {3};
	VictorSP dumpright {2};
	VictorSP intakeRight {1};
	VictorSP intakeLeft {6};
	AnalogGyro gyro;
	float kP = 0.03;
//	string gameData;
	Timer t;
	double angle = 0, kp = 0.03, turningValue = 0;
	int flag = 0;
	class RobotDrive myRobot { leftDrive, rightDrive};
	class Joystick *m_stick = new Joystick(0);
	class Joystick *m_stick2 = new Joystick(1);

public:

	GyroSample():
	// initialize the sensors in initilization list
	gyro(1)
	{

	}


	void RobotInit()
	{
		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->StartAutomaticCapture(1);
		CameraServer::GetInstance()->StartAutomaticCapture(2);
	}

	void AutonomousInit(){
		gyro.Calibrate();
		gyro.Reset();
		t.Reset();
		t.Start();
	}

	void AutonomousPeriodic(){


		if( t.Get() < 3.0)
		{
			angle=gyro.GetAngle();
			turningValue = (0-angle) * 3.0;
			myRobot.ArcadeDrive( 0.6 , turningValue);
		}
		else
		{
			myRobot.ArcadeDrive( 0.0 , 0.0 );
		}



	}

	void TeleopInit(){

	}

	void TeleopPeriodic(){

		if(m_stick->GetRawButton(1)){
			intakeLeft.Set(-1);
			intakeRight.Set(1);
		}
		else if(m_stick->GetRawButton(2)){
			intakeLeft.Set(1);
			intakeRight.Set(-1);
		}
		else {
			intakeLeft.Set(0);
			intakeRight.Set(0);
		}

		if(m_stick->GetRawButton(3)){
			dumpleft.Set(-1);
			dumpright.Set(-1);
		}
		else if(m_stick->GetRawButton(4)){
			dumpleft.Set(1);
			dumpright.Set(1);
		}
		else
		{
			dumpleft.Set(0);
			dumpright.Set(0);
		}


		armBack.Set( m_stick2->GetRawAxis(1) * 1.0 );

		if( m_stick2->GetRawAxis(2) )
		{
			armLeft.Set(0.4);
		}
		else if( m_stick2->GetRawButton(5) )
		{
			armLeft.Set(-0.4);
		}
		else
		{
			armLeft.Set( m_stick2->GetRawAxis(4) * 0.6 );
		}

		if( m_stick2->GetRawAxis(3) )
		{
			armRight.Set(-0.5);
		}
		else if( m_stick2->GetRawButton(6) )
		{
			armRight.Set(0.5);
		}
		else
		{
			armRight.Set( m_stick2->GetRawAxis(4) * -0.7 );
		}





		if( m_stick->GetRawAxis(2) )
		{
			myRobot.ArcadeDrive( m_stick->GetRawAxis(1) * -0.8, m_stick->GetRawAxis(0) * -0.8 );
		}
		else
		{
			myRobot.ArcadeDrive( m_stick->GetRawAxis(1) * -0.6, m_stick->GetRawAxis(0) * -0.6 );
		}


		frc::Wait(0.005);

	}



};


START_ROBOT_CLASS(GyroSample)
