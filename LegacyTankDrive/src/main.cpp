/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\aekstrand7207                                    */
/*    Created:      Thu Sep 19 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::controller Controller;
vex::motor29 leftMotor{Brain.ThreeWirePort.A};
vex::motor29 rightMotor{Brain.ThreeWirePort.B};

void updateMotorLeftVelocity(void);
void updateMotorRightVelocity(void);

int main(void) {
  bool shouldContinue = true;
  void (*p_updateMotorLeftVelocity)(void) = &updateMotorLeftVelocity;
  void (*p_updateMotorRightVelocity)(void) = &updateMotorRightVelocity;
  Controller.Axis3.changed((*p_updateMotorLeftVelocity));
  Controller.Axis2.changed((*p_updateMotorRightVelocity));
  leftMotor.spin(vex::directionType::fwd, 0, vex::percentUnits::pct);
  rightMotor.spin(vex::directionType::fwd, 0, vex::percentUnits::pct);
  while(shouldContinue) {
    if(Controller.ButtonB.pressing()){
        shouldContinue = false;
    }
  }
  leftMotor.stop();
  rightMotor.stop();
}

void updateMotorLeftVelocity(void){
  leftMotor.setVelocity(Controller.Axis3.value(), vex::percentUnits::pct);
  Brain.Screen.print("left: %d", Controller.Axis3.value());
}

void updateMotorRightVelocity(void){
  rightMotor.setVelocity(-Controller.Axis2.value(), vex::percentUnits::pct);
  Brain.Screen.print("right: %d", Controller.Axis2.value());
}