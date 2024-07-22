#include <Arduino.h>
#include <constants.h>

// #include <drivetrain.h>
#include <network.h>
#include <tape_sensors.h>
// #include <navigator.h>
#include <bottom_robot_modules.h>
#include <motor.h>
#include <stepper.h>
#include <servo.h>


void setup() {
  Serial.begin(9600);

  Drivetrain::setupDrivetrain();
  Network::setupWifi();
  // TapeSensors::setupTapeSensors();
  // Navigator::setupNavigator();
  // BottomRobotModules::setupBottomRobotModules();
}

int duration = 1000;
double power = 0.5; 

// Stepper outputStepper = Stepper(27, 14, 1);
// Servo inputServo = Servo(32, 8);
// Servo outputServo = Servo(33, 9);
// Stepper carouselStepper = Stepper(25, 26, 1);

String waitAndRead();
String wifiWaitAndRead();

String waitAndRead() {
  while (Serial.available() == 0) {
    // wait
  }
  String output = Serial.readString();
  Serial.println("Received: " + output);
  return output;
}

String wifiWaitAndRead() {
  while (!Network::wifiInput()) {
    // wait
  }
  return Network::message;
}

void loop() {
  // mecanum drive testing
  String s = wifiWaitAndRead();
  if (s == "F") {
    Drivetrain::driveMecanum(0, 0, power);
    delay(duration);
    Drivetrain::stopAll();
  } else if (s == "B") {
    Drivetrain::driveMecanum(180, 0, power);
    delay(duration);
    Drivetrain::stopAll();
  } else if (s == "L") {
    Drivetrain::driveMecanum(90, 0, power);
    delay(duration);
    Drivetrain::stopAll();
  } else if (s == "R") {
    Drivetrain::driveMecanum(-90, 0, power);
  } else if (s == "time") {
    duration = wifiWaitAndRead().toInt();
  } else if (s == "power") {
    power = wifiWaitAndRead().toDouble();
  }

  // top robot modules testing
  /*
  String s = waitAndRead();
  if (s == "input") {
    int angle = waitAndRead().toInt();
    inputServo.setAngle(angle);
  } else if (s == "output") {
    int angle = waitAndRead().toInt();
    outputServo.setAngle(angle);
  } else if (s == "linear") {
    double revs = waitAndRead().toDouble();
    outputStepper.step((int)(revs * 200));
  } else if (s == "carousel") {
    double revs = waitAndRead().toDouble();
    carouselStepper.step((int)(revs * 200));
  } else if (s == "ic") {
    inputServo.setAngle(107);
  } else if (s == "io") {
    inputServo.setAngle(180);
  } else if (s == "ou") {
    outputServo.setAngle(180);
  } else if (s == "od") {
    outputServo.setAngle(117);
  } else if (s == "lo") {
    outputStepper.stepRevs(2.5);
  } else if (s == "li") {
    outputStepper.stepRevs(-2.5);
  } else if (s == "ci") {
    carouselStepper.stepRevs(0.33);
  } else if (s == "co") {
    carouselStepper.stepRevs(-0.33);
  } */


  // while (Serial.available() == 0) {
  // }
  // String s = Serial.readStringUntil('\n');
  // s.trim();
  // BottomRobotModules::run(s);

  // if (Network::message == "R") {
  //   Network::wifiPrintln("Turning right until tape");
  //   Drivetrain::turnUntilTape(TurnDirection::RIGHT);
  // } else if (Network::message == "L") {
  //   Network::wifiPrintln("Turning left until tape");
  //   Drivetrain::turnUntilTape(TurnDirection::LEFT);
  // } else if (Network::message == "F"){
  //   while (!Network::wifiInput()) {
  //     // wait
  //   }
  //   Network::wifiPrintln("Starting tape following");
  //   Drivetrain::tapeFollow(Network::message.toDouble());
  // } else if (Network::message == "B") {
  //   Drivetrain::backUpToTape();
  // }

  // String reading = Network::message;
  // if (reading == "pa") {
  //   Navigator::navigateToStation(PATTIES);
  // } else if (reading == "bu") {
  //   Navigator::navigateToStation(BUNS);
  // } else if (reading == "po") {
  //   Navigator::navigateToStation(POTATOES);
  // } else if (reading == "to") {
  //   Navigator::navigateToStation(TOMATOES);
  // } else if (reading == "cu") {
  //   Navigator::navigateToStation(CUTTING);
  // } else if (reading == "co") {
  //   Navigator::navigateToStation(COOKING);
  // } else if (reading == "pl") {
  //   Navigator::navigateToStation(PLATES);
  // } else if (reading == "ch") {
  //   Navigator::navigateToStation(CHEESE);
  // } else if (reading == "se") {
  //   Navigator::navigateToStation(SERVING);
  // } else if (reading == "le") {
  //   Navigator::navigateToStation(LETTUCE);
  // } else if (reading == "R") {
  //   Drivetrain::turnUntilTape(TurnDirection::RIGHT);
  // } else if (reading == "L") {
  //   Drivetrain::turnUntilTape(TurnDirection::LEFT);
  // } else if (reading == "Tape") {
  //   Network::wifiPrintln(TapeSensors::getValuesStr());
  // } else if (reading == "F") {
  //   while (!Network::wifiInput()) {
  //     // wait
  //   }
  //   Drivetrain::tapeFollow(Network::message.toDouble());
  // } else if (reading == "Table") {
  //   Drivetrain::driveUpToTable();
  // } else if (reading == "Back") {
  //   Drivetrain::backUpToTape();
  // } else if (reading == "ic") {
  //   BottomRobotModules::closeInputScraper();
  // } else if (reading == "io") {
  //   BottomRobotModules::openInputScraper();
  // } else if (reading == "tc") {
  //   BottomRobotModules::closeTrapdoor();
  // } else if (reading == "to") {
  //   BottomRobotModules::openTrapdoor();
  // } else if (reading == "cr") {
  //   BottomRobotModules::rotateCarouselRight();
  // } else if (reading == "cb") {
  //   BottomRobotModules::rotateCarouselLeft();
  // } else if (reading == "straight") {
  //   Drivetrain::run();
  // }
}