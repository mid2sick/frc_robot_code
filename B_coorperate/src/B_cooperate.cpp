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

	WPI_TalonSRX *leftDrive_3 = new WPI_TalonSRX(1);
	WPI_TalonSRX *rightDrive_1 = new WPI_TalonSRX(2);
//	WPI_TalonSRX *leftDrive_4 = new WPI_TalonSRX(4);
//	WPI_TalonSRX *rightDrive_2 = new WPI_TalonSRX(2);
	VictorSP armBack {4};
	VictorSP armLeft {5};
	VictorSP armRight {0};
	VictorSP dumpleft {3};
	VictorSP dumpright {2};
	VictorSP intakeRight {1};
	VictorSP intakeLeft {6};
	string gameData;
	Timer t;
//	AnalogGyro gyro;
	double angle = 0, kp = 0.03;
	int flag = 0;
	class RobotDrive myRobot { leftDrive_3, rightDrive_1};
	class Joystick *m_stick = new Joystick(0);
	class Joystick *m_stick2 = new Joystick(1);
	AnalogInput *encoderArmBack = new AnalogInput(0);
	PIDController ParmBack{0.02, 0, 0, encoderArmBack, &armBack};
	long value = encoderArmBack->GetAccumulatorValue();
	long count = encoderArmBack->GetAccumulatorCount();
//	encoderArmBack->SetAccumul atorInitialValue(0);

	//int value = encoderArmBack->GetAccumulatorValue();

public:


/*	GyroSample():
	  gyro(1)
	  {

	  }

*/


	void RobotInit()
	{
		CameraServer::GetInstance()->StartAutomaticCapture(0);
		CameraServer::GetInstance()->StartAutomaticCapture(1);
	//	CameraServer::GetInstance()->StartAutomaticCapture(2);
	}

	void AutonomousInit(){
		t.Reset();
		t.Start();
//		gyro.Reset();
//		gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	/*	if( angle != 0 )
		{
			myRobot.ArcadeDrive( 0, 0.3 );
		}*/
	}

	void AutonomousPeriodic(){

//		if( t.Get() < 1.0 )
//		{
//			gyro.Calibrate();
//		}

/*		if(gameData.length() > 0)
		{
			if(gameData[0] == 'L')
			{
							//Put left auto code here
			}
			else
			{
							//Put right auto code here
			}
		}


		if( t.Get() < 5.0  && t.Get() > 1.0 )
		{
			angle=gyro.GetAngle();
			double turningValue = (0-angle) * 2.5;
			myRobot.ArcadeDrive( 0.6 , -0.25);
			cout<<"angle:"<<angle<<endl;
			cout<<"turningValue:"<<turningValue<<endl;
		}
		else if( t.Get() >= 8.0 )
		{
			myRobot.ArcadeDrive( 0.0 ,0.0 );
			t.Stop();
		}
*/
		if( t.Get() < 3.0   )
		{
		//	angle=gyro.GetAngle();
		//	double turningValue = (0-angle) * 2.5;
			myRobot.ArcadeDrive( 0.6 , 0);
		//	cout<<"angle:"<<angle<<endl;
		//	cout<<"turningValue:"<<turningValue<<endl;
		}
		else if( t.Get() >= 3.0)
		{
			myRobot.ArcadeDrive( 0.0 ,0.0 );
			t.Stop();
		}

	}

	void TeleopInit(){
//		gyro->Reset();
//		gyro->Calibrate();
		encoderArmBack->ResetAccumulator();
	}

	void TeleopPeriodic(){

		// AccumulatorResult *result = new AccumulatorResult();
		value = encoderArmBack->GetAccumulatorValue();
		count = encoderArmBack->GetAccumulatorCount();
		cout<<"value:"<<value<<" count:"<<count<<endl;

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

/*		if( m_stick2->GetRawAxis(3) )
		{
			armBack.Set(0.8);
		}
		else if( m_stick2->GetRawButton(6) )
		{
			armBack.Set(-0.8);
		}
		else
		{
			armBack.Set(0);
		}
*/

		armBack.Set( m_stick2->GetRawAxis(1) * 1.0 );

		///cout<<"flag="<<flag<<endl;
/*   	if( m_stick->GetRawButton(8) )
		{
			flag=!flag;
		}
*/
//		if( flag )
//		{

		if( m_stick2->GetRawAxis(2) )
		{
			armLeft.Set(-0.4);
		}
		else if( m_stick2->GetRawButton(5) )
		{
			armLeft.Set(0.4);
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
			armRight.Set( m_stick2->GetRawAxis(4) * 0.7 );
		}
//		}



//		angle=gyro->GetAngle();
//		turningValue = (0-angle)*0.005;

		if( m_stick->GetRawAxis(2) )
		{
			myRobot.ArcadeDrive( m_stick->GetRawAxis(1) * -0.8, m_stick->GetRawAxis(0) * -0.8 );
		}
		else
		{
			myRobot.ArcadeDrive( m_stick->GetRawAxis(1) * -0.6, m_stick->GetRawAxis(0) * -0.6 );
		}

	//	cout<< m_stick->GetRawAxis(0) * (-0.6) <<endl;

/*		if( !flag )
		{
			armRight.Set( m_stick->GetRawAxis(4) * 1.0 );
            armLeft.Set( m_stick->GetRawAxis(4) * 1.0 );
		}
*/
   //     cout<< m_stick->GetRawAxis(0) *0.6 <<endl;

		frc::Wait(0.005);

	}



};

START_ROBOT_CLASS(GyroSample);
