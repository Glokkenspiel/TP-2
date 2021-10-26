#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor liftMotorA = motor(PORT5, ratio18_1, true);
motor liftMotorB = motor(PORT9, ratio18_1, false);
motor_group lift = motor_group(liftMotorA, liftMotorB);
motor lBMotorA = motor(PORT1, ratio18_1, false);
motor lBMotorB = motor(PORT2, ratio18_1, false);
motor_group lB = motor_group(lBMotorA, lBMotorB);
motor rBMotorA = motor(PORT3, ratio18_1, true);
motor rBMotorB = motor(PORT4, ratio18_1, true);
motor_group rB = motor_group(rBMotorA, rBMotorB);
motor mTLift = motor(PORT7, ratio18_1, false);
digital_out pF = digital_out(Brain.ThreeWirePort.A);
digital_out pB = digital_out(Brain.ThreeWirePort.B);
digital_out pP = digital_out(Brain.ThreeWirePort.C);

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