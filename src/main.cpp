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
// lift                 motor_group   11, 17          
// lB                   motor_group   2, 9            
// rB                   motor_group   3, 4            
// mTLift               motor         12              
// pF                   digital_out   D               
// pB                   digital_out   B               
// pP                   digital_out   E               
// GPS                  gps           20              
// bTLift               motor         18              
// bTLSwitch            limit         C               
// conveyor             motor         16              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>

using namespace vex;

competition Competition;


/*---Sets up booleans and variables for the match---*/
bool driveMode = 0;
bool buttonLeftPressing = 0;
bool buttonDownPressing = 0;
bool buttonAPressing = 0;
bool buttonRPressing = 0;
bool buttonYPressing = 0;
bool upOrDown = 0;
bool pneumaticFront = 0;
bool pneumaticBack = 1;
bool direct = 0;
bool aMode = 0;
bool lORr = 0;
bool bTLDown = 0;
bool bTLMax = 0;
bool unclogFunc = 0;
bool buttonUpPressing = 0;
bool needVariance = 0;
bool relX = 0;
bool relY = 0;
bool dtpOnce = 0;
bool dtpS0Fin = 0;
bool dtpS2Fin = 0;
bool ttA = 0;
bool ttAFin = 0;

int n = 0;
int a = 2;
int x = 10;
int y = 30;
int auton = 0;
int xORyReach = 0;
int matchClock = 0;
int matchClock2 = 0;
int convSpin = 0;
int limitDisable = 0;
int relA = 0;
int dtpStage = 0;

float liPos = 0;
float mTPos = 0;
float pheta = 0;
float convChange = 0;
float convLast = 0;
float tgtA = 0;
float startX= 0;
float startY = 0;
float upperVariance = 0;
float lowerVariance = 0;

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
  Brain.Screen.drawRectangle(160, 0, 2, 120);
  Brain.Screen.drawRectangle(319, 0, 2, 120);
  Brain.Screen.drawRectangle(240, 121, 2, 120);
  Brain.Screen.drawRectangle(0, 120, 480, 2);
  Brain.Screen.setFont(propXL);
  Brain.Screen.setFillColor(purple);
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.print("L. Qual.");
  Brain.Screen.setCursor(2, 18);
  Brain.Screen.print("R. Qual.");
  Brain.Screen.setCursor(2, 11);
  Brain.Screen.print("S. WP");
  Brain.Screen.setFillColor(green);
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.print("L. Elim.");
  Brain.Screen.setCursor(5, 15);
  Brain.Screen.print("R. Elim");
  Brain.Screen.setFillColor(white);
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFont(propM);
  Brain.Screen.drawRectangle(201, 91, 80, 60);
  Brain.Screen.setCursor(6, 23);
  Brain.Screen.print("Skills");
  
  if(aMode == 0){
    if(Brain.Screen.pressing()){
      if((Brain.Screen.xPosition() > 240 && Brain.Screen.yPosition() > 150) || (Brain.Screen.xPosition() > 280 && Brain.Screen.yPosition() > 120)){
        //Right Elimination
        Brain.Screen.setPenColor(green);
        Brain.Screen.setFillColor(green);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Right Elim.");
        auton = 3;
      }else if(Brain.Screen.xPosition() > 320 && Brain.Screen.yPosition() < 121){
        //Right Qualifier
        Brain.Screen.setPenColor(purple);
        Brain.Screen.setFillColor(purple);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Right Qual.");
        auton = 1;
      }else if((Brain.Screen.xPosition() < 241 && Brain.Screen.yPosition() > 150) || (Brain.Screen.xPosition() < 201 && Brain.Screen.yPosition() > 120)){
        //Left Elimination
        Brain.Screen.setPenColor(green);
        Brain.Screen.setFillColor(green);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Left Elim.");
        auton = 4;
      }else if(Brain.Screen.xPosition() < 161 && Brain.Screen.yPosition() < 121){
        //Left Qualifier
        Brain.Screen.setPenColor(purple);
        Brain.Screen.setFillColor(purple);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Left Qual.");
        auton = 2;
      }else if((Brain.Screen.xPosition() < 201 && Brain.Screen.yPosition() < 120) || (Brain.Screen.xPosition() > 280 && Brain.Screen.yPosition() < 120) || (Brain.Screen.xPosition() > 200 && Brain.Screen.yPosition() < 90)){
        //Solo Win Point
        Brain.Screen.setPenColor(purple);
        Brain.Screen.setFillColor(purple);
        Brain.Screen.drawRectangle(0, 0, 480, 240);
        Brain.Screen.setPenColor(white);
        Brain.Screen.setFont(propXXL);
        Brain.Screen.setCursor(2, 5);
        Brain.Screen.print("Solo W.P.");
        auton = 6;
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
      rB.spin(dir, num - offset, rpm);
    }else{
      lB.spin(dir, num - offset, rpm);
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
void aPB(){
  if(pneumaticBack == 0){
    pB.set(1);
    pneumaticBack = 1;
  }else{
    pB.set(0);
    pneumaticBack = 0;
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


/*---Fix the angles compared to the GPS code strip---*/
/*void gpsStripVariance(float initX, float initY, float initA){
  if(GPS.heading() > 75 && GPS.heading() < 115){
    relX = 0;
    relY = 1;
    relA = 90;
  }else if(GPS.heading() > 165 && GPS.heading() < 195){
    relX = 1;
    relY = 1;
    relA = 180;
  }else if(GPS.heading() > 255 && GPS.heading() < 285){
    relX = 1;
    relX = 0;
    relA = 270;
  }else{
    relX = 0;
    relY = 0;
    relA = 0;
  }
}*/


/*---Drive to a certain point and position and face a certain direction---*/
void driveToPoint(float xTgt, float yTgt, float endA, int amnt){
  for(int d = 0; d < amnt; d++){
  GPS.calibrate();
  dtpOnce = 0;
  dtpStage = 0;
  dtpS0Fin = 0;
  dtpS2Fin = 0;
  while(dtpStage != 3){
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearScreen();
    Controller1.Screen.print(GPS.xPosition(mm));
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print(GPS.yPosition(mm));
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(GPS.heading());
    Controller1.Screen.setCursor(3, 17);
    Controller1.Screen.print(lORr);
    Controller1.Screen.setCursor(3, 20);
    Controller1.Screen.print(dtpStage);
    Controller1.Screen.setCursor(3, 10);
    Controller1.Screen.print(tgtA);
    if(dtpStage == 0){
    /*---The Turn---*/
    if(dtpOnce == 0){
      pheta = atan((GPS.yPosition(mm)-yTgt)/(GPS.xPosition(mm)-xTgt))*180/M_PI;
      dtpOnce = 1;
    }
    if(((GPS.xPosition(mm) - xTgt) < 0 || (GPS.xPosition(mm) < 0 && xTgt > 0)) && !(GPS.xPosition(mm) > 0 && xTgt < 0)){
      if(pheta < 0){
        tgtA = std::abs(pheta) + 90;
      }else{
        tgtA = 90 - pheta;
      }
    }else{
      if(pheta < 0){
        tgtA = std::abs(pheta) + 270;
      }else{
        tgtA = 270 - pheta;
      }
    }
    if((tgtA + 2) > 360){
      upperVariance = tgtA - 358;
    }else{
      upperVariance = tgtA + 2;
    }
    if((tgtA - 2) < 0){
      lowerVariance = tgtA + 358;
    }else{
      lowerVariance = tgtA - 2;
    }
    if(GPS.heading() > upperVariance){
      while(GPS.heading() > upperVariance){
        aBase(1, fwd, 25, 0, 1, 0);
      }
    }else if(GPS.heading() < lowerVariance){
      while(GPS.heading() < lowerVariance){
        aBase(1, fwd, 25, 0, 0, 0);
      }
    }
    if(GPS.heading() > lowerVariance && GPS.heading() < upperVariance){
      aBaseStop();
      dtpStage = 1;
      dtpOnce = 0;
    }else{
      aBaseStop();
      dtpOnce = 0;
    }
    }else if(dtpStage == 1){

    /*---The Drive---*/
    aBase(0, fwd, 200, 0, 0, 0);
    if(dtpOnce == 0){
      startX = GPS.xPosition(mm);
      startY = GPS.yPosition(mm);
      dtpOnce = 1;
    }
    if(xTgt <= startX){
      if(yTgt <= startY){
        while((((startX - xTgt) * 1/2) + xTgt) < GPS.xPosition(mm) && (((startY - yTgt) * 1/2) + yTgt) < GPS.yPosition(mm)){
          wait(1, msec);
        }
        aBase(0, fwd, 100, 0, 0, 0);
        while((((startX - xTgt) * 1/6) + xTgt) < GPS.xPosition(mm) && (((startY - yTgt) * 1/6) + yTgt) < GPS.yPosition(mm)){
          wait(1, msec);
        }
        aBase(0, fwd, 50, 0, 0, 0);
        while(((xTgt + 5) < GPS.xPosition(mm) || (xTgt - 5) < GPS.xPosition(mm)) && ((yTgt + 5) < GPS.yPosition(mm) || (yTgt - 5) < GPS.yPosition(mm))){
          wait(1, msec);
        }
      }else{
        while((((startX - xTgt) * 1/2) + xTgt) < GPS.xPosition(mm) && (((yTgt - startY) * 1/2) + startY) > GPS.yPosition(mm)){
          wait(1, msec);
        }
        aBase(0, fwd, 100, 0, 0, 0);
        while((((startX - xTgt) * 1/6) + xTgt) < GPS.xPosition(mm) && (((yTgt - startY) * 1/6) + startY) > GPS.yPosition(mm)){
          wait(1, msec);
        }
        aBase(0, fwd, 50, 0, 0, 0);
        while(((xTgt + 5) < GPS.xPosition(mm) || (xTgt - 5) < GPS.xPosition(mm)) && ((yTgt + 5) > GPS.yPosition(mm) || (yTgt - 5) > GPS.yPosition(mm))){
          wait(1, msec);
        }
      }
    }else{
      if(yTgt <= startY){
        while((((xTgt - startX) * 1/2) + startX) > GPS.xPosition(mm) && (((startY - yTgt) * 1/2) + yTgt) < GPS.yPosition(mm)){
          wait(1, msec);
        }
        aBase(0, fwd, 100, 0, 0, 0);
        while((((xTgt - startX) * 1/6) + startX) > GPS.xPosition(mm) && (((startY - yTgt) * 1/6) + yTgt) < GPS.yPosition(mm)){
          wait(1, msec);
        }
        aBase(0, fwd, 50, 0, 0, 0);
        while(((xTgt + 5) > GPS.xPosition(mm) || (xTgt - 5) > GPS.xPosition(mm)) && ((yTgt + 5) < GPS.yPosition(mm) || (yTgt - 5) < GPS.yPosition(mm))){
          wait(1, msec);
        }
      }else{
        while((((xTgt - startX) * 1/2) + startX) > GPS.xPosition(mm) && (((yTgt - startY) * 1/2) + startY) > GPS.yPosition(mm)){
          wait(1, msec);
        }
        aBase(0, fwd, 100, 0, 0, 0);
        while((((xTgt - startX) * 1/6) + startX) > GPS.xPosition(mm) && (((yTgt - startY) * 1/6) + startY) > GPS.yPosition(mm)){
          wait(1, msec);
        }
        aBase(0, fwd, 50, 0, 0, 0);
        while(((xTgt + 5) > GPS.xPosition(mm) || (xTgt - 5) > GPS.xPosition(mm)) && ((yTgt + 5) > GPS.yPosition(mm) || (yTgt - 5) > GPS.yPosition(mm))){
          wait(1, msec);
        }
      }
    }
    aBaseStop();
    //if((((xTgt - 5) < GPS.xPosition(mm) && (xTgt + 5) > GPS.xPosition(mm)) || ((xTgt - 5) > GPS.xPosition(mm) && (xTgt + 5) < GPS.xPosition(mm))) && (((yTgt - 5) < GPS.yPosition(mm) && (yTgt + 5) > GPS.yPosition(mm)) || ((yTgt - 5) > GPS.yPosition(mm) && (yTgt + 5) < GPS.yPosition(mm)))){
      dtpStage = 2;
    /*}else{
      dtpStage = 0;
    }*/
    dtpOnce = 0;
    }else if(dtpStage == 2){
  
  /*---The Final Turn---*/
  if(180 <= std::abs(GPS.heading() - endA) && std::abs(GPS.heading() - endA) <= 360){
      lORr = 0;
    }else{
      lORr = 1;
    }
    if((endA + 2) > 360){
      upperVariance = endA - 358;
    }else{
      upperVariance = endA + 2;
    }
    if((endA - 2) < 0){
      lowerVariance = endA + 358;
    }else{
      lowerVariance = endA - 2;
    }
    if(lORr == 1){
      if(GPS.heading() > upperVariance){
        while(GPS.heading() > upperVariance){
          aBase(1, fwd, 25, 0, 1, 0);
          //dtpS2Fin = 1;
        }
      }else{
        aBase(1, fwd, 50, 0, 0, 0);
      }
      if(/*tpS2Fin == 1*/ GPS.heading() < lowerVariance){
        aBaseStop();
        dtpStage = 3;
      }
    }else{
      if(GPS.heading() < lowerVariance){
        while(GPS.heading() < lowerVariance){
          aBase(1, fwd, 25, 0, 0, 0);
          //dtpS2Fin = 1;
        }
      }else{
        aBase(1, fwd, 50, 0, 1, 0);
      }
      if(/*dtpS2Fin == 1*/ GPS.heading() > upperVariance){
        aBaseStop();
        dtpStage = 3;
      }
    }
  dtpOnce = 0;
  }
  }
  }
}

void turnToAngle(float endA){
  ttA = 0;
  ttAFin = 0;
  while(ttA < 1){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(GPS.heading());
    Controller1.Screen.setCursor(3, 17);
    Controller1.Screen.print(lORr);
    Controller1.Screen.setCursor(3, 20);
    Controller1.Screen.print(ttAFin);
  
    if(180 <= std::abs(GPS.heading() - endA) && std::abs(GPS.heading() - endA) <= 360){
      lORr = 0;
    }else{
      lORr = 1;
    }
    if((endA + 2) > 360){
      upperVariance = endA - 359.5;
    }else{
      upperVariance = endA + .5;
    }
    if((endA - 2) < 0){
      lowerVariance = endA + 359.5;
    }else{
      lowerVariance = endA - .5;
    }
    if(lORr == 1){
      if(GPS.heading() > upperVariance){
        while(GPS.heading() > upperVariance){
          aBase(1, fwd, 25, 0, 1, 0);
        }
      }else{
        aBase(1, fwd, 25, 0, 0, 0);
      }
      if(GPS.heading() < lowerVariance){
        aBaseStop();
        ttA = 1;
      }
    }else{
      if(GPS.heading() < lowerVariance){
        while(GPS.heading() < lowerVariance){
          aBase(1, fwd, 25, 0, 0, 0);
        }
      }else{
        aBase(1, fwd, 25, 0, 1, 0);
      }
      if(GPS.heading() > upperVariance){
        aBaseStop();
        ttA = 1;
      }
    }
  }
  
}

void pre_auton(void) {
  vexcodeInit();
  lift.setStopping(hold);
  mTLift.setStopping(hold);
  bTLift.setStopping(brake);
  autonSelect();
  Brain.Screen.pressed(autonSelect);
  pF.set(1);
  pB.set(1);
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

    wait(.215, sec);

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

    aBase(0, reverse, 150, 0, 0, 0); //Back away from tower

    wait(.25, sec);

    aBaseStop();
    aML();

    aBase(0, reverse, 100, 0, 0, 0);

    wait(.5, sec);

    aBase(1, fwd, 75, 0, 1, 0); //Turn towards the left neutral tower

    wait(.7, sec);

    aBaseStop(); //Let the bot settle

    wait(.1, sec);

    aBase(0, fwd, 200, 0, 0, 0); //Drive towards the tower

    wait(1.1, sec);

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

    mTLift.spin(fwd, 100, percent);

    wait(.5, sec);
    
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
    pF.set(1); //Turn off the ratchet for the front claw
    pB.set(0); //Open the back tower lift
    aBase(0, reverse, 100, 0, 0, 0); //Back up into the right side red allaince tower

    wait(1, sec);

    aBaseStop();
    conveyor.spin(fwd, 100, percent); //Turn on the conveyor
    pB.set(1); //Grab the tower

    wait(.1, sec);

    aBase(0, fwd, 100, 1, 0, 82); //Arc towards the right neutral tower

    wait(2.75, sec);

    aBase(0, fwd, 100, 0, 0, 0); //Drive towards the right neutral tower

    wait(1.2, sec);

    aBaseStop();
    mTLift.spin(fwd, 100, percent); //Grab the right neutral tower
    lift.spin(reverse, 100, percent); //Raise up the lift so it can get onto the platform

    wait(1.75, sec);

    lift.stop();
    driveToPoint(900, -150, 100, 1); //Drive up next to and point towards the blue platform

    aBase(0, fwd, 100, 0, 0, 0); //Get the tower overtop the platform

    wait(.5, sec);

    aBaseStop();
    lift.spin(fwd, 100, percent); //Level the platform and prevent the tower from tipping when dropped

    wait(1, sec);

    lift.stop();
    mTLift.spin(reverse, 100, percent); //Drop the tower

    wait(.3, sec);

    mTLift.stop();
    lift.spin(reverse, 100, percent); //Lift over the lip of the platform

    wait(.5, sec);

    aBase(0, reverse, 100, 0, 0, 0); //Back away from the platform

    wait(.5, sec);

    aBaseStop();
    lift.stop();

    //aBase(1, fwd, 75, 0, 0, 0); //Turn towards the left wall

    //wait(.75, sec);

    /*turnToAngle(180); //Turn towards the left wall

    aBase(0, fwd, 200, 0, 0, 0); //Drive and slam into the wall

    wait(2.5, sec);

    aBase(0, reverse, 75, 0, 0, 0); //Back away from the wall

    wait(.75, sec);

    //aBase(1, fwd, 50, 0, 1, 0);

    //wait(1.13, sec);

    turnToAngle(90); //Turn towards the back wall

    aBase(0, fwd, 200, 0, 0, 0); //Slam into the wall to guarentee the position (pre GPS)

    wait(1.6, sec);

    aBase(0, reverse, 50, 0, 0, 0); //Back away from the wall

    wait(1.2, sec);

    aBase(1, fwd, 25, 0, 1, 0); //Turn towards the left neutral tower

    wait(3.7, sec);

    lift.spin(fwd, 100, percent);

    wait(.5, sec);

    aBase(0, fwd, 200, 0, 0, 0); //Drive to tower

    wait(1.5, sec);

    lift.stop();*/

    lift.spin(fwd, 100, percent); //Lower the lift

    wait(1.5, sec);

    lift.stop();
    driveToPoint(600, -900, 270, 1); //Drive up to and point towards the left neutral tower

    aBase(0, fwd, 50, 0, 0, 0); //Approach on the tower

    wait(1, sec);

    mTLift.spin(fwd, 100, percent); //Grab the tower
    /*aBase(1, fwd, 50, 0, 0, 0);

    wait(.55, sec);

    aBaseStop();
    lift.spin(reverse, 100, percent);

    wait(1.7, sec);

    aBase(0, fwd, 200, 0, 0, 0);
    lift.stop();

    wait(.9, sec);*/

    lift.spin(reverse, 100, percent); //Raise the lift

    wait(1.5, sec);

    lift.stop();
    driveToPoint(-900, -100, 280, 1); //Drive up next to and point towards the red platform

    aBase(0, fwd, 50, 0, 0, 0); //Approach on the platform

    wait(.5, sec);

    aBaseStop();
    lift.spin(fwd, 100, percent); //Lower the lift to level the platform and prevent the tower from tipping

    wait(.5, sec);

    mTLift.spin(reverse, 100, percent); //Drop the tower
    lift.spin(reverse, 100, percent); //Raise the lift

    wait(.5, sec);

    aBase(0, reverse, 100, 0, 0, 0); //Back away from the platform
    lift.stop();

    wait(.6, sec);

    aBaseStop();
    lift.spin(fwd, 100, percent); //Lower the lift

    wait(1.5, sec);

    lift.stop();
    turnToAngle(270); //Turn to a predictible angle

    pB.set(0); //Drop the red tower that's been getting hauled around
    aBase(0, fwd, 100, 0, 0, 0); //Pull away from the tower

    wait(.5, sec);

    aBaseStop();
    lift.stop();
    turnToAngle(90); //Turn towards the dropped tower

    aBase(0, fwd, 100, 0, 0, 0); //Drive up to the tower

    wait(.75, sec);

    mTLift.spin(fwd, 100, percent); //Grab the tower
    aBaseStop();

    wait(.3, sec);

    lift.spin(reverse, 100, percent); //Raise the lift

    wait(1.25, sec);

    lift.stop();
    turnToAngle(285); //Turn to the platform

    aBase(0, fwd, 100, 0, 0, 0); //Drive up to the platform

    wait(.75, sec);

    aBaseStop();
    lift.spin(fwd, 100, percent); //Lower the lift

    wait(.5, sec);

    lift.stop();
    mTLift.spin(reverse, 100, percent);

    wait(.3, sec);

    mTLift.stop();
    aBase(0, reverse, 25, 0, 0, 0);

    wait(.1, sec);

    lift.spin(reverse, 100, percent);

    wait(.5, sec);

    lift.stop();
    aBaseStop();
    /*aBase(1, fwd, 50, 0, 1, 0);

    wait(1.25, sec);

    lift.spin(fwd, 100, percent);

    wait(.25, sec);

    aBase(0, fwd, 150, 0, 0, 0);

    wait(1, sec);

    lift.stop();
    
    wait(.5, sec);

    mTLift.spin(fwd, 100, percent);

    wait(.3, sec);

    aBase(0, reverse, 50, 0, 0, 0);

    wait(1, sec);

    aBase(1, fwd, 50, 0, 1, 0);
    lift.spin(reverse, 100, percent);

    wait(1.465, sec);

    aBase(0, fwd, 200, 0, 0, 0);

    wait(.5, sec);

    lift.stop();

    wait(1.5, sec);

    aBaseStop();
    lift.spin(fwd, 100, percent);

    wait(.75, sec);
    
    lift.stop();

    wait(.2, sec);
    mTLift.spin(reverse, 100,percent);

    wait(.2, sec);

    aBase(0, reverse, 50, 0, 0, 0);
    mTLift.stop();

    wait(1, sec);

    aBaseStop();*/
  }
}

void usercontrol(void) {

  /*---Sets up driver information---*/
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Arcade");

  while (1) {

    /*---Used to switch between 'Tank' and 'Arcade' controls---*/
    /*if(Controller1.ButtonLeft.pressing()){
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
    }*/


    /*---Drive---*/
    if(driveMode == 0){

      /*---'Arcade'---*/
      lB.spin(fwd, 2*Controller1.Axis3.position(percent) + 1.5*Controller1.Axis1.position(percent), rpm);
      rB.spin(fwd, 2*Controller1.Axis3.position(percent) - 1.5*Controller1.Axis1.position(percent), rpm);
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
    /*if(Controller1.ButtonR2.pressing()){
      mTLift.spin(fwd, 100, percent);
    }else if(Controller1.ButtonR1.pressing() && mTLift.position(degrees) > 0){
      mTLift.spin(reverse, 100, percent);
    }else{
      mTLift.stop();
    }*/

    /*---Used to actuate the Front Pneumatic Claw---*/
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

    /*---Ratchet Claw---*/
    if(Controller1.ButtonR1.pressing() && mTLift.position(degrees) > 10){
      mTLift.spin(reverse, 100, percent);
      pF.set(1);
    }else if(Controller1.ButtonR2.pressing()){
      mTLift.spin(fwd, 100, percent);
      pF.set(0);
    }else{
      mTLift.stop();
    }
    if(Controller1.ButtonY.pressing()){
      if(buttonYPressing == 0){
        if(pneumaticFront == 0){
          pneumaticFront = 1;
        }else{
          pneumaticFront = 0;
        }
        buttonYPressing = 1;
      }
    }else{
      buttonYPressing = 0;
    }
    if(pneumaticFront == 1){
      pF.set(1);
    }

    /*---Used to toggle the Conveyor---*/
    if(Controller1.ButtonDown.pressing()){
      if(buttonDownPressing == 0){
        if(convSpin == 1){
          conveyor.stop();
          convSpin = 0;
          matchClock = 0;
        }else{
          conveyor.spin(fwd, 100, percent);
          convSpin = 1;
        }
        buttonDownPressing = 1;
      }
    }else if(Controller1.ButtonUp.pressing()){
      if(buttonUpPressing == 0){
        if(convSpin == 2){
          conveyor.stop();
          convSpin = 0;
          matchClock = 0;
        }else{
          conveyor.spin(reverse, 100, percent);
          convSpin = 2;
          matchClock = 0;
        }
        buttonUpPressing = 1;
      }
    }else{
      buttonDownPressing = 0;
      buttonUpPressing = 0;
    }
    convChange = conveyor.position(degrees) - convLast;
    if(convSpin == 1){
      matchClock += 1;
      if(matchClock >= 2 && convChange <= 50 && unclogFunc == 0){
        unclogFunc = 1;
        matchClock = 0;
      }
    }
    if(unclogFunc == 1){
      if(matchClock <= 1){
        conveyor.spin(reverse, 100, percent);
      }else{
        unclogFunc = 0;
        matchClock = 0;
        conveyor.spin(fwd, 100, percent);
      }
    }
    convLast = conveyor.position(degrees);

    /*---Used to control the Back Pnuematic Claw---*/
    if(Controller1.ButtonA.pressing()){
      if(buttonAPressing == 0){
        if(pneumaticBack == 0){
          pB.set(1);
          pneumaticBack = 1;
        }else{
          pB.set(0);
          pneumaticBack = 0;
        }
        buttonAPressing = 1;
      }
    }else{
      buttonAPressing = 0;
    }


    /*---Used to rotate the Back Tower Lift---*/
    /*if(Controller1.ButtonA.pressing()){
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
    if(upOrDown == 0 && bTLift.position(degrees) < -600){
      bTLift.spin(fwd, 100, percent);
    }else if(upOrDown == 1 && bTLift.position(degrees) > -2500){
      bTLift.spin(reverse, 100, percent);
    }else{
      bTLift.stop();
    }*/

    /*---Puts the battery percent onto the controller---*/
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.clearLine(2);
    Controller1.Screen.print("Battery Percent: ");
    Controller1.Screen.print(Brain.Battery.capacity());
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.clearLine(3);
    Controller1.Screen.print(GPS.xPosition(mm));
    Controller1.Screen.setCursor(3, 10);
    Controller1.Screen.print(GPS.yPosition(mm));

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
