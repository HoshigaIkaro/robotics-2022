//===----------------------------------------------------------------------===//
///
/// @file main.cpp
/// @author tonyc
/// @date Thursday, September 15, 2022
///
/// Vex V5 Project
///
//===----------------------------------------------------------------------===//

#include "config.h"
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

/// @brief Scale the base's velocity by this amount.
/// @details Scale of the base's velocity. The value is from 0.0 to 1.0
const float BASE_SCALE = 1.0;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

/// @brief Set up robot before competition starts.
/// @details Sets up the robot pre-competition. This is called once after V5 is
/// powered on.
/// @return void must be returned for the other tasks to start
void pre_auton(void) {
  Lift.setVelocity(100.0, percent);
  Lift.setMaxTorque(100.0, percent);

  Intake.setVelocity(100.0, percent);
  Intake.setMaxTorque(100.0, percent);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Roller.setBrake(vex::brakeType::brake);
}

/*---------------------------------------------------------------------------*/
/*                                 Functions                                 */
/*---------------------------------------------------------------------------*/

/// @brief Rolls the base forward
/// @param scale a float percentage from -100.0 to 100.0
void moveForward(float scale) {
  BaseLeft.spin(forward, scale, percent);
  BaseRight.spin(forward, scale, percent);
}

/// @brief Rolls the base backward
/// @param scale a float percentage from -100.0 to 100.0
void moveBackward(float scale) {
  BaseLeft.spin(reverse, scale, percent);
  BaseRight.spin(reverse, scale, percent);
}

/// @brief Rolls the roller if button X is active
void rollRoller(void) {
  if (Controller.ButtonR1.pressing()) {
    Roller.spin(forward, 100.0, percent);
  } else {
    Roller.stop();
  }
}

void rollLift(void) {
  if (Controller.ButtonL2.pressing()) {
    Lift.spin(forward, 100.0, percent);
  } else {
    Lift.stop();
  }
}

void rollIntake(void) {
  if (Controller.ButtonR1.pressing()) {
    Intake.spin(forward, 100.0, percent);
  } else if (Controller.ButtonR2.pressing()) {
    Intake.spin(reverse, 100.0, percent);
  } else {
    Intake.stop();
  }
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/

/// @brief Runs the autonomous phase
/// @details This function is used during the autonomous task.
/// The robot will drop two preloaded rings into the goal field when called, and
/// move back to the start.
void autonomous(void) {
  // Moves into the goal field
  moveBackward(100.0);
  wait(2, seconds);
  // moves back to start position
  moveForward(100.0);
  wait(2, seconds);
  BaseLeft.stop();
  BaseRight.stop();
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

/// @brief Controls the robot during the User Control phase
/// @details This function controls the robot during the user control task.
void usercontrol(void) {
  while (1) {
    BaseLeft.spin(forward, Controller.Axis3.position(percent) * BASE_SCALE,
                  percent);
    BaseRight.spin(forward, Controller.Axis2.position(percent) * BASE_SCALE,
                   percent);

    rollRoller();
    rollLift();
    rollIntake();

    wait(20, msec); // prevent wasted resources.
  }
}

/// @brief Set up the competition functions and callbacks.
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
