/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package org.usfirst.frc.team6191.robot;

import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.SendableBase;
import edu.wpi.first.wpilibj.SensorBase;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.VictorSP;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import com.ctre.phoenix.motorcontrol.can.WPI_TalonSRX;
import edu.wpi.first.wpilibj.GyroBase;
import edu.wpi.first.wpilibj.AnalogGyro;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;
import edu.wpi.first.wpilibj.CameraServer;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;



/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 * 
 * 
 */
public class Robot extends IterativeRobot {
	private DifferentialDrive m_robotDrive
			= new DifferentialDrive(new WPI_TalonSRX(1), new WPI_TalonSRX(2));
	private Joystick m_stick = new Joystick(0);
	private Joystick m_stick2 = new Joystick(1);
	private Timer m_timer = new Timer();
	VictorSP armBack = new VictorSP(6);
	VictorSP armLeft = new VictorSP(5);
	VictorSP armRight = new VictorSP (0);
	VictorSP dumpleft = new VictorSP(3);
	VictorSP dumpright = new VictorSP(2);
	VictorSP intakeRight = new VictorSP(1);
	VictorSP intakeLeft = new VictorSP(4);
	Encoder enc = new Encoder(0, 1, false, Encoder.EncodingType.k4X);


	public void robotInit() {
	}


	public void autonomousInit() {
		m_timer.reset();
		m_timer.start();
	}


	public void autonomousPeriodic() {
		// Drive for 2 seconds
		if (m_timer.get() < 2.0) {
			m_robotDrive.arcadeDrive(0.5, 0.0); // drive forwards half speed
		} else {
			m_robotDrive.stopMotor(); // stop robot
		}
	}


	public void teleopInit() {
		enc.reset();
		enc.setDistancePerPulse(360/552);
	}


	public void teleopPeriodic() {
		int count = enc.get();
		double distance = enc.getDistance();
		double degrees = (double)count / 552 * 360;
		System.out.println("distance" + distance + " " + degrees);
		m_robotDrive.arcadeDrive(m_stick.getY(), m_stick.getX());
		if(m_stick.getRawButton(1)){
			intakeLeft.set(-1);
			intakeRight.set(1);
		}
		else if(m_stick.getRawButton(2)){
			intakeLeft.set(1);
			intakeRight.set(-1);
		}
		else {
			intakeLeft.set(0);
			intakeRight.set(0);
		}

		if(m_stick.getRawButton(3)){
			dumpleft.set(-1);
			dumpright.set(-1);
		}
		else if(m_stick.getRawButton(4)){
			dumpleft.set(1);
			dumpright.set(1);
		}
		else
		{
			dumpleft.set(0);
			dumpright.set(0);
		}



		armBack.set( m_stick2.getRawAxis(1) * 1.0 );


		if(m_stick2.getRawAxis(2) > 0.1)
		{
			armLeft.set(-0.4);
		}
		else if(m_stick2.getRawButton(5))
		{
			armLeft.set(0.4);
		}
		else
		{
			armLeft.set( m_stick2.getRawAxis(4) * 0.6 ); 
		}

		if(m_stick2.getRawAxis(3) > 0.1			)
		{
			armRight.set(-0.5);
		}
		else if(m_stick2.getRawButton(6))
		{
			armRight.set(0.5);
		}
		else
		{
			armRight.set( m_stick2.getRawAxis(4) * 0.7 );
		}
	}
}

