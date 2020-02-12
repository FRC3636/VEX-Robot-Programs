/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\aekstrand7207                                    */
/*    Created:      Wed Sep 18 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::controller Controller;

vex::motor leftMotor{vex::PORT1};
vex::motor rightMotor{vex::PORT2};
vex::motor29 armMotor{Brain.ThreeWirePort.A};
vex::motor29 clawMotor{Brain.ThreeWirePort.B};

void updateMotorLeftVelocity(void);
void updateMotorRightVelocity(void);
void openClaw();
void closeClaw();

int main(void) {
  bool shouldContinue = true;
  void (*p_updateMotorLeftVelocity)(void) = &updateMotorLeftVelocity;
  void (*p_updateMotorRightVelocity)(void) = &updateMotorRightVelocity;
  void (*p_openClaw)(void) = &openClaw;
  void (*p_closeClaw)(void) = &closeClaw;
  Controller.Axis3.changed((*p_updateMotorLeftVelocity));
  Controller.Axis2.changed((*p_updateMotorRightVelocity));
  Controller.ButtonR2.pressed((*p_openClaw));
  Controller.ButtonR2.released((*p_closeClaw));
  leftMotor.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  rightMotor.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
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
  }
  armMotor.stop();
  clawMotor.stop();
  leftMotor.stop();
  rightMotor.stop();
}

void updateMotorLeftVelocity(void){
  leftMotor.setVelocity(-Controller.Axis3.position(), vex::velocityUnits::pct);
  Brain.Screen.print("left: %d", Controller.Axis3.position());
}

void updateMotorRightVelocity(void){
  rightMotor.setVelocity(Controller.Axis2.position(), vex::velocityUnits::pct);
  Brain.Screen.print("right: %d", Controller.Axis2.position());
}

void openClaw(){
  clawMotor.spin(vex::directionType::fwd);
  vex::task::sleep(1500);
  clawMotor.stop();
}

void closeClaw(){
  clawMotor.spin(vex::directionType::rev);
  vex::task::sleep(500);
  clawMotor.stop();
}
