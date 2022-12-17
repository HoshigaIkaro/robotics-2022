#include "vex.h"

// global instances of competition parts
vex::controller Controller = vex::controller(vex::primary);

vex::motor Motor1 = vex::motor(vex::PORT1, vex::ratio18_1, false);
vex::motor Motor2 = vex::motor(vex::PORT2, vex::ratio18_1, true);
vex::motor Motor3 = vex::motor(vex::PORT18, vex::ratio18_1, true);
vex::motor Motor4 = vex::motor(vex::PORT19, vex::ratio18_1, false);
vex::motor_group BaseLeft = vex::motor_group(Motor1, Motor4);
vex::motor_group BaseRight = vex::motor_group(Motor2, Motor3);
vex::drivetrain Base = vex::drivetrain(BaseLeft, BaseRight);

vex::motor Roller = vex::motor(vex::PORT11, vex::ratio36_1, false);

vex::motor LiftLeft = vex::motor(vex::PORT10, vex::ratio36_1, false);
vex::motor LiftRight = vex::motor(vex::PORT20, vex::ratio36_1, true);
vex::motor_group Lift = vex::motor_group(LiftLeft, LiftRight);

vex::motor Intake = vex::motor(vex::PORT13, vex::ratio18_1, false);
