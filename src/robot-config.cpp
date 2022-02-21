#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor liftMotorA = motor(PORT5, ratio18_1, false);
motor liftMotorB = motor(PORT17, ratio18_1, true);
motor_group lift = motor_group(liftMotorA, liftMotorB);
motor lBMotorA = motor(PORT2, ratio18_1, true);
motor lBMotorB = motor(PORT9, ratio18_1, true);
motor_group lB = motor_group(lBMotorA, lBMotorB);
motor rBMotorA = motor(PORT3, ratio18_1, false);
motor rBMotorB = motor(PORT4, ratio18_1, false);
motor_group rB = motor_group(rBMotorA, rBMotorB);
motor mTLift = motor(PORT12, ratio18_1, false);
digital_out pF = digital_out(Brain.ThreeWirePort.D);
digital_out pB = digital_out(Brain.ThreeWirePort.B);
digital_out pP = digital_out(Brain.ThreeWirePort.E);
gps GPS = gps(PORT20, -113.00, -120.00, mm, 270);
motor bTLift = motor(PORT18, ratio18_1, false);
limit bTLSwitch = limit(Brain.ThreeWirePort.C);
motor conveyor = motor(PORT16, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}