/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// lift                 motor_group   5, 6            
// lB                   motor_group   1, 2            
// rB                   motor_group   3, 4            
// plungerRot           motor         7               
// pF                   digital_out   A               
// pB                   digital_out   B               
// pP                   digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

bool driveMode = 0;

bool buttonLeftPressing = 0;

bool pneumaticFront = 0;

bool pneumaticBack = 0;

bool buttonDownPressing = 0;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  lift.setStopping(brake);
  plungerRot.setStopping(brake);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Arcade");
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    if(Controller1.ButtonLeft.pressing()){
      if(buttonLeftPressing == 0){
        if(driveMode == 0){
          driveMode = 1;
          Controller1.Screen.clearLine(1);
          Controller1.Screen.setCursor(1, 1);
          Controller1.Screen.print("Tank");
        }else{
          driveMode = 0;
          Controller1.Screen.clearLine(1);
          Controller1.Screen.setCursor(1, 1);
          Controller1.Screen.print("Arcade");
        }
      }
      buttonLeftPressing = 1;
    }else{
      buttonLeftPressing = 0;
    }

    if(driveMode == 0){
      lB.spin(fwd, Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent), rpm);
      rB.spin(fwd, Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent), rpm);
    }else{
      lB.spin(fwd, Controller1.Axis3.position(percent), rpm);
      rB.spin(fwd, Controller1.Axis2.position(percent), rpm);
    }

    if(Controller1.ButtonL1.pressing()){
      lift.spin(fwd, 100, rpm);
    }else if(Controller1.ButtonL2.pressing()){
      lift.spin(reverse, 100, rpm);
    }else{
      lift.stop();
    }

    if(Controller1.ButtonR1.pressing()){
      plungerRot.spin(fwd, 100, rpm);
    }else if(Controller1.ButtonR2.pressing()){
      plungerRot.spin(reverse, 100, rpm);
    }else{
      plungerRot.stop();
    }

    if(Controller1.ButtonDown.pressing()){
      if(buttonDownPressing == 0){
        if(pneumaticFront == 0){
          pF.set(1);
          pneumaticFront = 1;
        }else{
          pF.set(0);
          pneumaticFront = 0;
        }
      }
      buttonDownPressing = 1;
    }else{
      buttonDownPressing = 0;
    }

    if(Controller1.ButtonB.pressing()){
      pP.set(1);
    }else{
      pP.set(0);
    }

    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.clearLine(2);
    Controller1.Screen.print("Battery Percent: ");
    Controller1.Screen.print(Brain.Battery.capacity());
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
