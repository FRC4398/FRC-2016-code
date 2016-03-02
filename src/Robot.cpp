#include "WPILib.h"

class Robot: public IterativeRobot
{

	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	Victor ball; // for collecting balls
	LiveWindow *lw;
	int autoLoopCounter;

public:
	Robot() :
		myRobot(0, 1),	// these must be initialized in the same order
		stick(1),		// as they are declared above.
		ball(2),
		lw(LiveWindow::GetInstance()),
		autoLoopCounter(0)
	{
		myRobot.SetExpiration(0.1);
	}
public:
	void RobotInit() override {
		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	}


private:
	void AutonomousInit()
	{
		autoLoopCounter = 0;
	}

	void AutonomousPeriodic()
	{
		if(autoLoopCounter < 100) //Check if we've completed 100 loops (approximately 2 seconds)
		{
			myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
			autoLoopCounter++;
			} else {
			myRobot.Drive(0.0, 0.0); 	// stop robot
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)

		if (stick.GetRawButton(3) == 1)   // for collecting and shooting
			ball.Set(0.5);

		else if (stick.GetRawButton(2) == 1)
			ball.Set(-0.5);

		else
			ball.Set(0);


		while (IsOperatorControl() && IsEnabled())
		{
			Wait(0.005);				// wait for a motor update time
		}
	}


	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
