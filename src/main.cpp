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
// rB                   motor_group   3, 8            
// plungerRot           motor         11              
// pF                   digital_out   A               
// pB                   digital_out   B               
// pP                   digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;



bool driveMode = 0; 

bool buttonLeftPressing = 0;

bool buttonDownPressing = 0;

bool pneumaticFront = 0;

bool pneumaticBack = 0;

/*---Runs all the basic functions of the base with one command excluding run time---*/
void aBase(bool isTurning, directionType dir, int num, velocityUnits unit){
  lB.spin(dir, num, unit);
  if(isTurning == 1){
    rB.spin(dir, -num, unit);
  }else{
    rB.spin(dir, num, unit);
  }
}

/*---Stops the base with one command---*/
void aBaseStop(){
  lB.stop();
  rB.stop();
}

/*---Activates the tower lift with one command---*/
void aPF(){
  if(pneumaticFront == 0){
    pF.set(1);
    pneumaticFront = 1;
  }else{
    pF.set(0);
    pneumaticFront = 0;
  }
}

void pre_auton(void) {
  vexcodeInit();
  lift.setStopping(brake);
  plungerRot.setStopping(brake);
}

void autonomous(void) {
  plungerRot.spin(fwd, 100, rpm); // -
                                  //  |
  wait(1, sec);                   //  |
                                  //  |- Sets up our bar to lower the platforms
  plungerRot.stop();              //  |
  pB.set(1);                      // -
  aBase(0, fwd, 100, rpm);

  wait(5, sec);

  aBaseStop();
  aPF();

  wait(1, sec);

  aBase(0, reverse, 100, rpm);

  wait(5, sec);

  aBaseStop();
}

void usercontrol(void) {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Arcade");
  while (1) {


    /*---Used to switch between 'Tank' and 'Arcade' controls---*/
    if(Controller1.ButtonLeft.pressing()){
      if(buttonLeftPressing == 0){
        Controller1.Screen.clearLine(1);
        Controller1.Screen.setCursor(1, 1);
        if(driveMode == 0){
          driveMode = 1;
          Controller1.Screen.print("Tank");
        }else{
          driveMode = 0;
          Controller1.Screen.print("Arcade");
        }
      }
      buttonLeftPressing = 1;
    }else{
      buttonLeftPressing = 0;
    }


    /*---Drive---*/
    if(driveMode == 0){

      /*---'Arcade'---*/
      lB.spin(fwd, Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent), rpm);
      rB.spin(fwd, Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent), rpm);
    }else{

      /*---'Tank'---*/
      lB.spin(fwd, Controller1.Axis3.position(percent), rpm);
      rB.spin(fwd, Controller1.Axis2.position(percent), rpm);
    }


    /*---Used to rotate the main lift unit---*/
    if(Controller1.ButtonL1.pressing()){
      lift.spin(fwd, 100, rpm);
    }else if(Controller1.ButtonL2.pressing()){
      lift.spin(reverse, 100, rpm);
    }else{
      lift.stop();
    }


    /*---Used to rotate the 'Plunger' unit---*/
    if(Controller1.ButtonR1.pressing()){
      plungerRot.spin(fwd, 25, rpm);
    }else if(Controller1.ButtonR2.pressing()){
      plungerRot.spin(reverse, 25, rpm);
    }else{
      plungerRot.stop();
    }


    /*---When pushed, will cause the front tower lift to raise or lower---*/
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


    /*---While pushed, the 'Plunger' will release---*/
    if(Controller1.ButtonB.pressing()){
      pP.set(1);
    }else{
      pP.set(0);
    }


    /*---Puts the battery percent onto the controller---*/
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.clearLine(2);
    Controller1.Screen.print("Battery Percent: ");
    Controller1.Screen.print(Brain.Battery.capacity());

    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
