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

/*Notes from programmer Zak, I make reference to something known as 'Pong' code,
  this is purely for aesthetics and can be removed without consequenses*/

#include "vex.h"

using namespace vex;

competition Competition;


/*---Sets up booleans and variables for the match---*/
bool driveMode = 0; 

bool buttonLeftPressing = 0;

bool buttonDownPressing = 0;

bool pneumaticFront = 0;

bool pneumaticBack = 0;


/*---'Pong' code setup---*/
int circleX = 240;

int circleY = 120;

int cSX = (rand() % 450) + 15;

int cSY = (rand() % 210) + 15;

int matchCounter = 0;

int cColor = 0;

bool negX = 0;

bool negY = 0;

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
  /*aBase(0, fwd, 100, rpm); //Drive forward

  wait(3, sec); //~2 tiles at 100 rpm

  aBaseStop();
  aPF(); //Lower goal lift

  wait(.1, sec);

  aBase(0, fwd, 25, rpm); //Slowly drive forward to hopfully hook the tower

  wait(.25, sec);

  aPF(); //Raise goal lift

  wait(.1, sec);

  aBase(0, reverse, 100, rpm);

  wait(3.1, sec); //~2+ a little tiles

  aBaseStop();*/
}

void usercontrol(void) {
  /*---Setting up the 'Pong' code---*/
  Brain.Screen.setPenColor(cyan);
  Brain.Screen.setFillColor(cyan);
  Brain.Screen.drawRectangle(1, 1, 479, 239);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(10, 10, 461, 221);
  Brain.Screen.setPenColor(purple);
  Brain.Screen.setFillColor(purple);
  circleX = cSX;
  circleY = cSY;
  Brain.Screen.drawCircle(circleX, circleY, 20);

  /*---Sets up driver information---*/
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
      lB.spin(fwd, 2*Controller1.Axis3.position(percent) + 2*Controller1.Axis1.position(percent), rpm);
      rB.spin(fwd, 2*Controller1.Axis3.position(percent) - 2*Controller1.Axis1.position(percent), rpm);
    }else{

      /*---'Tank'---*/
      lB.spin(fwd, 2*Controller1.Axis3.position(percent), rpm);
      rB.spin(fwd, 2*Controller1.Axis2.position(percent), rpm);
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
      plungerRot.spin(fwd, 100, rpm);
    }else if(Controller1.ButtonR2.pressing()){
      plungerRot.spin(reverse, 100, rpm);
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

    /*---Actual 'Pong' section of the 'Pong' code---*/
    /*matchCounter += 1;
    if(matchCounter >= 2){*/
      Brain.Screen.setFillColor(black);
      Brain.Screen.setPenColor(black);
      Brain.Screen.drawCircle(circleX, circleY, 20);
      if(circleX >= 450 || circleX <= 30 || circleY >= 210 || circleY <= 30){
        cColor = rand() % 4;
        Brain.Screen.setPenColor(cyan);
        Brain.Screen.setFillColor(cyan);
        Brain.Screen.drawRectangle(1, 1, 479, 10);
        Brain.Screen.drawRectangle(1, 10, 10, 220);
        Brain.Screen.drawRectangle(470, 10, 10, 220);
        Brain.Screen.drawRectangle(1, 230, 479, 10);
        if(circleX >= 450){
          negX = 1;
        }else{
          negX = 0;
        }
        if(circleY >= 210){
          negY = 1;
        }else{
          negY = 0;
        }
      }
    }

    if(negX == 1){
      circleX -= 4.5;
    }else{
      circleX += 4.5;
    }

    if(negY == 1){
      circleY -= 3.5;
    }else{
      circleY += 3.5;
    }

    if(cColor == 0){
      Brain.Screen.setPenColor(purple);
      Brain.Screen.setFillColor(purple);
    }else if(cColor == 1){
      Brain.Screen.setPenColor(green);
      Brain.Screen.setFillColor(green);
    }else if(cColor == 2){
      Brain.Screen.setPenColor(orange);
      Brain.Screen.setFillColor(orange);
    }else if(cColor == 3){
      Brain.Screen.setPenColor(yellow);
      Brain.Screen.setFillColor(yellow);
    }
    Brain.Screen.drawCircle(circleX, circleY, 20);
    matchCounter = 0;
  //}
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(20, msec);
  }
}
