using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group lift;
extern motor_group lB;
extern motor_group rB;
extern motor mTLift;
extern digital_out pF;
extern digital_out pB;
extern digital_out pP;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );