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
// lift                 motor_group   5, 9            
// lB                   motor_group   1, 2            
// rB                   motor_group   3, 4            
// mTLift               motor         16              
// pF                   digital_out   D               
// pB                   digital_out   B               
// pP                   digital_out   C               
// GPS                  gps           10              
// bTLift               motor         20              
// bTLSwitch            limit         A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;


/*---Sets up booleans and variables for the match---*/
bool driveMode = 0;
bool buttonLeftPressing = 0;
bool buttonDownPressing = 0;
bool buttonAPressing = 0;
bool buttonRPressing = 0;
bool upOrDown = 1;
bool pneumaticFront = 0;
bool pneumaticBack = 0;
bool direct = 0;
bool aMode = 0;
bool lORr = 0;

int uni = 0; //Universal variable
int n = 0;
int a = 2;
int x = 10;
int y = 30;
int auton = 0;
int xORyReach = 0;

float liPos = 0;
float mTPos = 0;
float pheta1 = 0;
float pheta2 = 0;
float pheta3 = 0;
float slackN = 0;
float slackP = 0;

/*---Auton Selector---*/
void autonSelect(){
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(purple);
  Brain.Screen.setPenColor(purple);
  Brain.Screen.drawRectangle(0, 0, 480, 120);
  Brain.Screen.setFillColor(green);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawRectangle(0, 121, 480, 120);
  Brain.Screen.setFillColor(white);
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawRectangle(240, 0, 2, 240);
  Brain.Screen.drawRectangle(0, 120, 480, 2);
  Brain.Screen.setFont(propXL);
  Brain.Screen.setFillColor(purple);
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.print("R. Qual.");
  Brain.Screen.setCursor(2, 15);
  Brain.Screen.print("L. Qual.");
  Brain.Screen.setFillColor(green);
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.print("R. Elim.");
  Brain.Screen.setCursor(5, 15);
  Brain.Screen.print("L. Elim");
  Brain.Screen.setFillColor(white);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFont(propM);
  Brain.Screen.drawRectangle(201, 91, 80, 60);
  Brain.Screen.setCursor(6, 23);
  Brain.Screen.print("Skills");
  
  if(aMode == 0){
    if(Brain.Screen.pressing()){
      if((Brain.Screen.xPosition() > 240 && Brain.Screen.yPosition() > 150) || (Brain.Screen.xPosition() > 280 && Brain.Screen.yPosition() > 120)){
        //Left Elimination
        Brain.Screen.setPenColor(green);
        Brain.Screen.setFillColor(green);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Left Elim.");
        auton = 4;
      }else if((Brain.Screen.xPosition() > 280 && Brain.Screen.yPosition() < 121) || (Brain.Screen.xPosition() > 240 && Brain.Screen.yPosition() < 91)){
        //Left Qualifier
        Brain.Screen.setPenColor(purple);
        Brain.Screen.setFillColor(purple);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Left Qual.");
        auton = 2;
      }else if((Brain.Screen.xPosition() < 241 && Brain.Screen.yPosition() > 150) || (Brain.Screen.xPosition() < 201 && Brain.Screen.yPosition() > 120)){
        //Right Elimination
        Brain.Screen.setPenColor(green);
        Brain.Screen.setFillColor(green);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Right Elim.");
        auton = 3;
      }else if((Brain.Screen.xPosition() < 241 && Brain.Screen.yPosition() < 91) || (Brain.Screen.xPosition() < 201 && Brain.Screen.yPosition() < 121)){
        //Right Qualifier
        Brain.Screen.setPenColor(purple);
        Brain.Screen.setFillColor(purple);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Right Qual.");
        auton = 1;
      }else{
        //Skills
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFillColor(white);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(black);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 6);
        Brain.Screen.print("Skills");
        auton = 5;
      }
      aMode = 1;
      Brain.Screen.setPenColor(black);
      Brain.Screen.setFillColor(black);
      while(n < 10){
        Brain.Screen.drawRectangle(x, y, 2, a);
        x += 2;
        y -= 2;
        a += 4;
        n += 1;
      }
      x = 10;
      y = 30;
      a = 2;
      n = 0;
    }
  }else{
    if(Brain.Screen.pressing()){
      if(Brain.Screen.xPosition() <= 50 && Brain.Screen.yPosition() <= 50){
        aMode = 0;
      }
    }
  }
}

/*---Runs all the basic functions of the base with one command excluding run time---*/
void aBase(bool isTurning, directionType dir, int num, bool isArc, bool rl, float offset){
  /*---isTurning dictates whether the robot turns or not---*/
  if(isTurning == 1){
    if(rl == 1){
      lB.spin(dir, -num, rpm);
      rB.spin(dir, num, rpm);
    }else{
      lB.spin(dir, num, rpm);
      rB.spin(dir, -num, rpm);
    }
  /*---isArc dictates whether the robot goes in an arcing motion---*/
  }else if(isArc == 1){
    if(rl == 0){
      lB.spin(dir, num, rpm);
      /*---offset is how much it arcs by---*/
      rB.spin(dir, num - (offset / num) * 100, rpm);
    }else{
      lB.spin(dir, num - (offset / num) * 100, rpm);
      rB.spin(dir, num, rpm);
    }
  }else{
    lB.spin(dir, num, rpm);
    rB.spin(dir, num, rpm);
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


/*---Activate the Main Tower Lift---*/
void aML(){
  if(direct == 0){
    mTLift.spin(fwd, 100, percent);
    direct = 1;
  }else{
    mTLift.spin(reverse, 100, percent);
    direct = 0;
  }

  wait(.3, sec);

  mTLift.stop();
}


/*---Drive to a certain point and position and face a certain direction---*/
void driveToPoint(float xPos, float yPos, float head){
  while(/*GPS.xPosition(mm) == (xPos +- 5) && GPS.yPosition(mm) == (yPos +- 5)*/ 1){
    pheta1 = atan((yPos-GPS.yPosition(mm))/(xPos-GPS.xPosition(mm)));
    if(pheta1 < 0){
      pheta1 = pheta1 + 360;
    }
    if(pheta1 < 50){
      slackN = pheta1 + 310;
      slackP = pheta1;
    }else if(pheta1 >= 310){
      slackN = pheta1;
      slackP = pheta1 - 310;
    }else{
      slackN = pheta1;
      slackP = pheta1;
    }
    aBase(1, fwd, 50, 0, 1, 0);
    while(GPS.heading() < slackN || GPS.heading() > slackP){
      wait(1, msec);
      Controller1.Screen.clearScreen();
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print(pheta1);
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print(GPS.heading());
      /*Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print(GPS.xPosition(mm));
      Controller1.Screen.setCursor(3, 10);
      Controller1.Screen.print(GPS.yPosition(mm));*/
    }
    aBaseStop();
    break;
  }
}

void pre_auton(void) {
  vexcodeInit();
  lift.setStopping(brake);
  mTLift.setStopping(hold);
  bTLift.setStopping(brake);
  autonSelect();
  Brain.Screen.pressed(autonSelect);
  pF.set(0);
}

void autonomous(void) {

  /*---Right Qualifier---*/
  if(auton == 1){
    aBase(0, fwd, 150, 0, 0, 0); //Drive towards the alliance tower on the AWP line

    wait(.75, sec);

    aBaseStop();
    aML(); //Grab the tower

    aBase(0, reverse, 75, 0, 0, 0); //Back off of the AWP line

    wait(1, sec);

    aBaseStop(); //Stop
    aML(); //Drop the Tower

    aBase(0, reverse, 75, 0, 0, 0); //Back up further

    wait(.35, sec);

    aBase(1, fwd, 180, 0, 1, 0); //Turn towards the right neutral tower

    wait(.175, sec);

    aBase(0, fwd, 150, 0, 0, 0); //Drive towards the tower

    wait(1.6, sec);

    aBase(0, fwd, 30, 0, 0, 0); //Stop and grab the tower
    aML();
  
    aBase(0, reverse, 225, 0, 0, 0); //Reverse into the home zone

    wait(1.3, sec);

    aBase(1, fwd, 150, 0, 0, 0); //Turn so the tower is out of our way

    wait(.5, sec);

    aBaseStop(); //Drop off the tower
    aML();

    /*---Left Qualifier---*/
  }else if(auton == 2){
    aBase(0, fwd, 75, 0, 0, 0); //Drive up to left alliance tower

    wait(.5, sec);

    aBaseStop();
    aML(); //Drop ring into alliance tower
    aML();

    aBase(0, reverse, 150, 0, 0, 0); //Back away from tower

    wait(.25, sec);

    aBase(1, fwd, 75, 0, 1, 0); //Turn towards the left neutral tower

    wait(.73, sec);

    aBaseStop(); //Let the bot settle

    wait(.1, sec);

    aBase(0, fwd, 200, 0, 0, 0); //Drive towards the tower

    wait(1, sec);

    aBase(0, fwd, 75, 0, 0, 0); //Slow down as to not knock the tower

    wait(.5, sec);

    aBaseStop();

    wait(.1, sec);

    aBase(0, fwd, 30, 0, 0, 0); //Grab the tower
    aML();

    aBase(0, reverse, 200, 0, 0, 0); //Back into home zone

    wait(1.2, sec);

    aBaseStop(); //Drop the tower
    aML();
    
    /*---Right Elimination---*/
  }else if(auton == 3){

    aBase(0, fwd, 400, 0, 0, 0);

    wait(1.15, sec);

    aBaseStop();

    aML();
    aBase(0, reverse, 200, 0, 0, 0);

    wait(1.5, sec);

    aBaseStop();

    wait(6,sec);

    aBase(0, reverse, 400, 0, 0, 0);

    /*---Left Elimination---*/
  }else if(auton == 4){


    /*---Skills---*/
  }else if(auton == 5){
    /*---GPS work for future---*/
    /*GPS.setLocation(1500, -1500, mm, 0, degrees);
    driveToPoint(0, 0, 0);*/

    /*---Current work---*/
    bTLift.spin(fwd, 200, rpm); //Lower the back tower lift

    wait(1, sec);

    aBase(0, reverse, 200, 0, 0, 0); //Begin Speeding towards the other side of the field

    wait(.3, sec);

    bTLift.stop(); //Stop the back tower lift from ramming into the floor

    wait(.2, sec);

    bTLift.spin(reverse, 200, rpm); //Lift the red alliance tower from the AWP line

    wait(1.3, sec);

    bTLift.stop(); //Stop the lift from slamming into the robot

    wait(1, sec);

    aBaseStop(); //

    wait(.2, sec);

    aBase(1, fwd, 20, 0, 0, 0); //

    wait(.5, sec);

    bTLift.spin(fwd, 100, percent); //Begin dropping the red alliance goal
    aBase(1, fwd, 50, 0, 0, 0); //Turn towards the right neutral tower

    wait(.2, sec);

    aBaseStop(); //Stop turning

    wait(.1, sec);

    aBase(0, fwd, 200, 0, 0, 0); //Drive towards the tower

    wait(.9, sec);

    aBase(0, fwd, 100, 0, 0, 0); //Slow down to prevent coasting and hitting the tower
    
    wait(.2, sec);

    bTLift.stop(); //Stop the lift from slamming into the robot

    wait(.8, sec);

    aBaseStop(); //Stop in front of the tower
    mTLift.spin(fwd, 100, percent); // Clamp onto the tower

    wait(.3, sec);

    lift.spin(reverse, 100, percent); //Raise the main lift to prepare to place the goal on the platform
    aBase(1, fwd, 50, 0, 0, 0); //Torn towards the platform
    bTLift.spin(reverse, 100, percent); //Raise the back tower lift to prevent dragging

    wait(.4, sec);

    aBase(0, fwd, 100, 0, 0, 0); //Drive up to the platform
    bTLift.stop(); //Stop the lift

    wait(1.5, sec);

    lift.stop(); //Prevent the lift from attempting to go to high

    wait(.5, sec); //THIS IS WHAT WE CHANGE(og = .325)

    aBase(1, fwd, 50, 0, 1, 0); //Turn towards the platform for better angle

    wait(.6, sec);

    aBase(0, fwd, 100, 0, 0, 0); //Drive up to the platform

    wait(.75, sec);

    lift.spin(fwd, 200, rpm); //Lower the lift to level the platform

    wait(.25, sec);

    aBaseStop(); //Prevent ramming onto the platform and ruining the angle

    wait(.75, sec);

    mTLift.spin(reverse, 100, percent); //Drop the tower

    wait(.3, sec);

    mTLift.stop();
    lift.spin(reverse, 200, rpm); //Lift up over the lip of the platform

    wait(.8, sec);

    aBase(0, reverse, 75, 0, 0, 0); //Back away from the platform
    lift.stop();

    wait(.75, sec);

    aBase(1, fwd, 50, 0, 0, 0); //Turn towards the left wall

    wait(.75, sec);

    aBase(0, fwd, 200, 0, 0, 0); //Drive and slam into the wall

    wait(2, sec);

    aBase(0, fwd, 50, 0, 0, 0); //Prevent bouncing off of the wall

    wait(.2, sec);

    aBase(0, reverse, 50, 0, 0, 0); //Back away from the wall

    wait(1, sec);

    aBase(1, fwd, 50, 0, 0, 0); //Turn towards the goal under the platform

    wait(.6, sec);

    aBase(0, reverse, 100, 0, 0, 0); //Drive to under the platform
    bTLift.spin(fwd, 100, percent); //Lower the back tower lift

    wait(.5, sec);

    bTLift.stop();

    wait(.75, sec);

    bTLift.spin(reverse, 100, percent); //Grab the tower
    lift.spin(fwd, 100, percent); //Lower the main lift
    aBaseStop();

    wait(.3, sec);

    aBase(0, fwd, 100, 0, 0, 0); //Pull out from under the platform

    wait(.75, sec);

    aBase(1, fwd, 100, 0, 0, 0); //Turn towards the left neutral tower

    wait(.025, sec);

    lift.stop();

    wait(.25, sec);

    aBase(0, fwd, 200, 0, 0, 0); //Drive towards the tower

    wait(.15, sec);

    bTLift.stop();

    wait(.25, sec);

    aBase(0, fwd, 100, 0, 0, 0); //Slow down to not knock over the tower

    wait(.9, sec);

    aML(); //Grab the tower

    lift.spin(reverse, 100, percent); //Raise the tower
    aBase(1, fwd, 75, 0, 0, 0); //Turn towards the far platform

    wait(.3, sec);

    aBase(0, fwd, 150, 0, 0, 0); //Drive towards the platform

    wait(1.5, sec);

    lift.stop();

    wait(1, sec);

    aBase(1, fwd, 75, 0, 1, 0); //Turn towards the platform for a better angle

    wait(.5, sec);

    aBaseStop();
    lift.spin(fwd, 100, percent);

    wait(1, sec);

    mTLift.spin(reverse, 100, percent); //Drop the tower

    wait(.3, sec);

    mTLift.stop();
    lift.spin(reverse, 200, rpm); //Lift up over the lip of the platform

    wait(.5, sec);

    lift.stop();
  }
}

void usercontrol(void) {

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
    if(Controller1.ButtonL1.pressing() && liPos > -1700){
      lift.spin(reverse, 150, rpm);
    }else if(Controller1.ButtonL2.pressing() && liPos < 0){
      lift.spin(fwd, 150, rpm);
    }else{
      lift.stop();
    }
    liPos = lift.position(degrees);

    /*---Used to rotate the Main Tower Lift---*/
    if(Controller1.ButtonR2.pressing()){
      mTLift.spin(fwd, 100, percent);
    }else if(Controller1.ButtonR1.pressing()){
      mTLift.spin(reverse, 100, percent);
    }else{
      mTLift.stop();
    }

    /*---Used to control the Front Pnuematic Claw---*/
    /*if(Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing()){
      if(buttonRPressing == 0){
        if(pneumaticFront == 0){
          pF.set(1);
          pneumaticFront = 1;
        }else{
          pF.set(0);
          pneumaticFront = 0;
        }
        buttonRPressing = 1;
      }
    }else{
      buttonRPressing = 0;
    }*/

    /*---Used to rotate the Back Tower Lift---*/
    if(Controller1.ButtonA.pressing()){
      if(buttonAPressing == 0){
        if(upOrDown == 0){
          upOrDown = 1;
        }else{
          upOrDown = 0;
        }
        buttonAPressing = 1;
      }
    }else{
      buttonAPressing = 0;
    }
    if(upOrDown == 0 && bTLift.position(degrees) < 1350){
      bTLift.spin(fwd, 100, percent);
    }else if(upOrDown == 1 && bTLift.position(degrees) > 0){
      bTLift.spin(reverse, 100, percent);
    }else{
      bTLift.stop();
    }

    /*---Puts the battery percent onto the controller---*/
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.clearLine(2);
    Controller1.Screen.print("Battery Percent: ");
    Controller1.Screen.print(Brain.Battery.capacity());
    /*Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.print("mTLift Position: ");
    Controller1.Screen.print(bTLift.position(degrees));
    Controller1.Screen.print(" Degrees");*/

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
