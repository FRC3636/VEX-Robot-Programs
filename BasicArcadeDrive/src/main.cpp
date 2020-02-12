/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\aekstrand7207                                    */
/*    Created:      Thu Sep 19 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::controller Controller;

vex::motor leftMotor{vex::PORT1};
vex::motor rightMotor{vex::PORT2};
vex::motor29 armMotor{Brain.ThreeWirePort.A};
vex::motor29 clawMotor{Brain.ThreeWirePort.B};
vex::drivetrain DriveTrain{leftMotor, rightMotor};

void updateMotorVelocity(void);

int main() {
  leftMotor.setVelocity(0, vex::velocityUnits::pct);
  rightMotor.setVelocity(0, vex::velocityUnits::pct);
  bool shouldContinue = true;
  void (*p_updateMotorVelocity)(void) = &updateMotorVelocity;
  Controller.Axis3.changed((*p_updateMotorVelocity));
  Controller.Axis1.changed((*p_updateMotorVelocity));
  leftMotor.spin(vex::directionType::fwd);
  rightMotor.spin(vex::directionType::rev);
  while(shouldContinue) {
    if(Controller.ButtonB.pressing()){
        shouldContinue = false;
    }
    if(Controller.ButtonL2.pressing()){
      armMotor.spin(vex::directionType::rev);
    }
    else if (Controller.ButtonL1.pressing()) {
      armMotor.spin(vex::directionType::fwd);
    }
    else{
      armMotor.stop();
    }
    if(Controller.ButtonR2.pressing()) {
      clawMotor.spin(vex::directionType::fwd);
    } else if(Controller.ButtonR1.pressing()) {
      clawMotor.spin(vex::directionType::rev);
    } else {
      clawMotor.stop();
    }
  }
  clawMotor.stop();
  armMotor.stop();
  leftMotor.stop();
  rightMotor.stop();
}

void updateMotorVelocity(void){
  float yValue = Controller.Axis1.position() * -1;
  float xValue = Controller.Axis3.position() * -1;
  leftMotor.setVelocity(yValue + xValue, vex::velocityUnits::pct);
  rightMotor.setVelocity(yValue - xValue, vex::velocityUnits::pct);
}