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
// mTLift               motor         8               
// pF                   digital_out   A               
// pB                   digital_out   B               
// pP                   digital_out   C               
// GPS                  gps           10              
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
bool buttonAPressing = 0;
bool pneumaticFront = 0;
bool pneumaticBack = 0;
bool direct = 0;
bool aMode = 0;

int uni = 0; //Universal variable
int n = 0;
int a = 2;
int x = 10;
int y = 30;
int auton = 0;

float liPos = 0;
float mTPos = 0;

/*---'Pong' code setup---*/
/*int circleX = 240;

int circleY = 120;

int cSX = (rand() % 450) + 15;

int cSY = (rand() % 210) + 15;

int matchCounter = 0;

int cColor = 0;

bool negX = 0;

bool negY = 0;*/

/*---Auton Selector---*/
void autonSelect(){
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(red);
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(0, 0, 480, 120);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.setPenColor(blue);
  Brain.Screen.drawRectangle(0, 121, 480, 120);
  Brain.Screen.setFillColor(white);
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawRectangle(240, 0, 2, 240);
  Brain.Screen.drawRectangle(0, 120, 480, 2);
  Brain.Screen.setFont(propXL);
  Brain.Screen.setFillColor(red);
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.print("R. Red");
  Brain.Screen.setCursor(2, 15);
  Brain.Screen.print("L. Red");
  Brain.Screen.setFillColor(blue);
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.print("L. Blue");
  Brain.Screen.setCursor(5, 15);
  Brain.Screen.print("R. Blue");
  
  if(aMode == 0){
    if(Brain.Screen.pressing()){
      if((Brain.Screen.xPosition() > 240) && (Brain.Screen.yPosition() > 120)){
        //Right Blue
        Brain.Screen.setPenColor(blue);
        Brain.Screen.setFillColor(blue);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Right Blue");
        auton = 4;
      }else if((Brain.Screen.xPosition() > 240) && (Brain.Screen.yPosition() < 121)){
        //Left Red
        Brain.Screen.setPenColor(red);
        Brain.Screen.setFillColor(red);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Left Red");
        auton = 2;
      }else if((Brain.Screen.xPosition() < 241) && (Brain.Screen.yPosition() > 120)){
        //Left Blue
        Brain.Screen.setPenColor(blue);
        Brain.Screen.setFillColor(blue);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Left Blue");
        auton = 3;
      }else{
        //Right Red
        Brain.Screen.setPenColor(red);
        Brain.Screen.setFillColor(red);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Right Red");
        auton = 1;
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
    mTLift.spin(fwd, 200, rpm);
    direct = 1;
  }else{
    mTLift.spin(reverse, 200, rpm);
    direct = 0;
  }

  wait(.3, sec);

  mTLift.stop();
}

void pre_auton(void) {
  vexcodeInit();
  lift.setStopping(brake);
  mTLift.setStopping(brake);
  mTLift.setStopping(hold);
  autonSelect();
  Brain.Screen.pressed(autonSelect);
}

void autonomous(void) {

  /*---Right Red or Right Blue---*/
  if(auton == 1 || auton == 4){
    aBase(0, fwd, 100, 0, 0, 0); //Drive towards the alliance tower on the AWP line

    wait(.75, sec);

    aBaseStop();
    aML(); //Grab the tower

    aBase(0, reverse, 50, 0, 0, 0); //Back off of the AWP line

    wait(1, sec);

    aBaseStop(); //Stop
    aML(); //Drop the Tower

    aBase(0,reverse, 50, 0, 0, 0); //Back up further

    wait(.35, sec);

    aBase(1, fwd, 120, 0, 1, 0); //Turn towards the right neutral tower

    wait(.175, sec);

    aBase(0, fwd, 100, 0, 0, 0); //Drive towards the tower

    wait(1.6, sec);

    aBaseStop(); //Stop and grab the tower

    aML();
  
    aBase(0, reverse, 150, 0, 0, 0); //Reverse into the home zone

    wait(.9, sec);

    aBase(1, fwd, 100, 0, 0, 0); //Turn so the tower is out of our way

    wait(.5, sec);

    aBaseStop(); //Drop off the tower
    aML();

    /*---Left Red or Left Blue---*/
  }else if(auton == 2 || auton == 3){
    aBase(0, fwd, 50, 0, 0, 0); //Drive up to left alliance tower

    wait(.5, sec);

    aML(); //Drop ring into alliance tower
    aML();

    aBase(0, reverse, 100, 0, 0, 0); //Back away from tower

    wait(.75, sec);

    aBase(1, fwd, 100, 0, 1, 0); //Turn towards the left neutral tower

    wait(.4, sec);

    aBaseStop(); //Let the bot settle

    wait(.1, sec);

    aBase(0, fwd, 200, 0, 0, 0); //Drive towards the tower

    wait(.9, sec);

    aBase(0, fwd, 50, 0, 0, 0); //Slow down as to not knock the tower

    wait(.75, sec);

    aBaseStop();

    wait(.1, sec);

    aBase(0, fwd, 20, 0, 0, 0); //Grab the tower
    aML();

    aBase(0, reverse, 200, 0, 0, 0); //Back into home zone

    wait(.9, sec);

    aBaseStop(); //Drop the tower
    aML();
  }
}

void usercontrol(void) {
  /*---Setting up the 'Pong' code---*/
  /*Brain.Screen.setPenColor(cyan);
  Brain.Screen.setFillColor(cyan);
  Brain.Screen.drawRectangle(1, 1, 479, 239);
  Brain.Screen.setPenColor(vex::black);
  Brain.Screen.setFillColor(black);
  Brain.Screen.drawRectangle(10, 10, 461, 221);
  Brain.Screen.setPenColor(purple);
  Brain.Screen.setFillColor(purple);
  circleX = cSX;
  circleY = cSY;
  Brain.Screen.drawCircle(circleX, circleY, 20);*/

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


    /*---Used to rotate the Main Tower Lift---*/
    if(Controller1.ButtonR2.pressing() && mTPos < 260){
      mTLift.spin(fwd, 75, rpm);
    }else if(Controller1.ButtonR1.pressing() && mTPos > 0){
      mTLift.spin(reverse, 75, rpm);
    }else{
      mTLift.stop();
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


    /*---When pushed, will cause the back tower lift to raise or lower---*/
    if(Controller1.ButtonA.pressing()){
      if(buttonAPressing == 0){
        if(pneumaticBack == 0){
          pB.set(1);
          pneumaticBack = 1;
        }else{
          pB.set(0);
          pneumaticBack = 0;
        }
      }
      buttonAPressing = 1;
    }else{
      buttonAPressing = 0;
    }

    liPos = lift.position(degrees);
    mTPos = mTLift.position(degrees);

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
    /*Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.print("mTLift Position: ");
    Controller1.Screen.print(mTPos);
    Controller1.Screen.print(" Degrees");*/

    wait(20, msec);

    /*---Actual 'Pong' section of the 'Pong' code---*/
    /*matchCounter += 1;
    if(matchCounter >= 2){
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
    }*/
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
