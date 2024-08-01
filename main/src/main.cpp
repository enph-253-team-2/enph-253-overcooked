#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
#include <network.h>
#include <tape_sensors.h>
#include <bottom_robot_modules.h>
#include <motor.h>
#include <stepper.h>
#include <servo.h>
#include <actions.h>
#include <user_interface.h>
#include <top_robot_modules.h>


void setup() {
  Serial.begin(9600);
  Serial.println("initializing");

  Drivetrain::setupDrivetrain();
  Network::setupWifi();
  TapeSensors::setupTapeSensors();
  BottomRobotModules::setupBottomRobotModules();
  // TopRobotModules::setupTopRobotModules();
  UserInterface::setupUserInterface();
  // Navigator::setupNavigator();
}

int duration = 1000;
double power = 0.4; 
int driveTime = 377;
int spinTime = 765;
int slowTime = 135;
int fastTime = 440;
double slowPower = 0.25;
double fastPower = 0.5;
double spinPower = 0.5;
int wallTime = 500;

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
  if (Network::wifiInput()) {
    String s = Network::message;
    UserInterface::displayOLED(s); // echo
    if (s == "test") {
      Network::wifiPrintln("Hello World!");
    // drive testing
    } else if (s == "F") {
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
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "time") {
      duration = wifiWaitAndRead().toInt();
    } else if (s == "power") {
      power = wifiWaitAndRead().toDouble();
    } else if (s == "FL") {
      Drivetrain::driveMotors(power, 0, 0, 0);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "FR") {
      Drivetrain::driveMotors(0, power, 0, 0);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "BL") {
      Drivetrain::driveMotors(0, 0, power, 0);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "BR") {
      Drivetrain::driveMotors(0, 0, 0, power);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "print") {
      Network::wifiPrintln("Duration: " + String(duration) + " Power: " + String(power));
      Network::wifiPrintln("Drive time: " + String(driveTime) + " Spin time: " + String(spinTime));
      Network::wifiPrintln("Drive power: " + String(power) + " Spin power: " + String(spinPower));
      Network::wifiPrintln("Slow time: " + String(slowTime) + " Fast time: " + String(fastTime));
      Network::wifiPrintln("Slow power: " + String(slowPower) + " Fast power: " + String(fastPower));
      Network::wifiPrintln("Wall delay: " + String(wallTime));
    } else if (s == "tape") {
      Network::wifiPrintln(TapeSensors::getValuesStr());
    } else if (s == "W") {
      String s = wifiWaitAndRead();
      int num = s.substring(0, 1).toInt();
      DriveDirection driveDirection = s.substring(1, 2) == "F" ? DriveDirection::FORWARD : DriveDirection::BACKWARD;
      WallLocation wallLocation = s.substring(2, 3) == "R" ? WallLocation::RIGHT : WallLocation::LEFT;
      Drivetrain::wallFollow(driveDirection, wallLocation, num, wallTime);
    } else if (s == "mec") {
      double angle = wifiWaitAndRead().toDouble();
      Drivetrain::driveMecanum(angle, 0, power);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "spin") {
      double spinPower = wifiWaitAndRead().toDouble();
      Drivetrain::driveMecanum(0, spinPower, 0);
      delay(duration);
      Drivetrain::stopAll();
    } else if (s == "WW") {
      DriveDirection driveDirection = wifiWaitAndRead() == "R" ? DriveDirection::RIGHT : DriveDirection::LEFT;
      Drivetrain::wallToWall(driveDirection, slowTime, fastTime, slowPower, fastPower);
    } else if (s == "driveT") {
      driveTime = wifiWaitAndRead().toInt();
    } else if (s == "spinT") {
      spinTime = wifiWaitAndRead().toInt();
    } else if (s == "slowT") {
      slowTime = wifiWaitAndRead().toInt();
    } else if (s == "fastT") {
      fastTime = wifiWaitAndRead().toInt();
    } else if (s == "wallT") {
      wallTime = wifiWaitAndRead().toInt();
    } else if (s == "slowP") {
      slowPower = wifiWaitAndRead().toDouble();
    } else if (s == "fastP") {
      fastPower = wifiWaitAndRead().toDouble();
    } else if (s == "spinP") {
      spinPower = wifiWaitAndRead().toDouble();
    } else if (s == "WWS") {
      DriveDirection driveDirection = wifiWaitAndRead() == "R" ? DriveDirection::RIGHT : DriveDirection::LEFT;
      Drivetrain::wallToWallSpin(driveDirection, driveTime, spinTime, power, spinPower);
    } else if (s == "WWSS") {
      Actions::wallToWallSpinSlow();
    // bottom robot modules
    } else if (s == "bic") {
      BottomRobotModules::closeInputScraper();
    } else if (s == "bio") {
      BottomRobotModules::openInputScraper();
    } else if (s == "btc") {
      BottomRobotModules::closeTrapdoor();
    } else if (s == "bto") {
      BottomRobotModules::openTrapdoor();
    } else if (s == "boc") {
      BottomRobotModules::closeOutputScraper();
    } else if (s == "boo") {
      BottomRobotModules::openOutputScraper();
    } else if (s == "bpo") {
      BottomRobotModules::openPlatePincher();
    } else if (s == "bpc") {
      BottomRobotModules::closePlatePincher();
    } else if (s == "bcl") {
      BottomRobotModules::rotateCarouselLeft();
    } else if (s == "bcr") {
      BottomRobotModules::rotateCarouselRight();
    } else if (s == "be") {
      double distanceMM = wifiWaitAndRead().toDouble();
      BottomRobotModules::moveElevator(distanceMM);
    } else if (s == "serve") {
      Actions::servingRoutine();
    } else if (s == "burger") {
      // drive to cutting area, intake bottom bun
      BottomRobotModules::moveElevator(30);
      Actions::startToCutting();
      Actions::inputSingle();
      // drive to tomato area, intake tomato
      BottomRobotModules::moveElevator(-10);
      Actions::cuttingToTomato();
      Actions::inputSingle();
      // drive to cheese area, intake cheese
      BottomRobotModules::moveElevator(-5);
      Actions::tomatoToCheese();
      Actions::inputSingle();
      // drive to cooktop, intake patty
      BottomRobotModules::moveElevator(-10);
      Actions::cheeseToCooktop();
      Actions::inputSingle();
      // drive to lettuce area, intake lettuce
      BottomRobotModules::moveElevator(-5);
      Actions::cooktopToLettuce();
      Actions::inputSingle();
      // drive to cooktop, intake top bun
      Actions::lettuceToCooktop();
      Actions::inputSingle();
      // drive to plates, get plate
      Actions::cooktopGrabPlate();
      // drive to serving area, serve burger
      Actions::plateToServing();
      Actions::servingRoutine();
      // drive back to cooktop
      Actions::servingToCooktop();
    } else if (s == "start") {
      Actions::startToCutting();
    } else if (s == "c2t") {
      Actions::cuttingToTomato();
    } else if (s == "t2c") {
      Actions::tomatoToCheese();
    } else if (s == "c2c") {
      Actions::cheeseToCooktop();
    } else if (s == "c2l") {
      Actions::cooktopToLettuce();
    } else if (s == "l2c") {
      Actions::lettuceToCooktop();
    } else if (s == "c2p") {
      Actions::cooktopGrabPlate();
    } else if (s == "p2s") {
      Actions::plateToServing();
    } else if (s == "s2c") {
      Actions::servingToCooktop();
    } else if (s == "input") {
      Actions::inputSingle();
    // top robot modules
    } else if (s == "tic") {
      TopRobotModules::closeInputScraper();
    } else if (s == "tio") {
      TopRobotModules::openInputScraper();
    } else if (s == "ti") {
      TopRobotModules::setInputScraper(wifiWaitAndRead().toDouble());
    } else if (s == "tor") {
      TopRobotModules::raiseOutputScraper();
    } else if (s == "tol") {
      TopRobotModules::lowerOutputScraper();
    } else if (s == "to") {
      TopRobotModules::setOutputScraper(wifiWaitAndRead().toDouble());
    } else if (s == "tcl") {
      TopRobotModules::rotateCarouselLeft();
    } else if (s == "tcr") {
      TopRobotModules::rotateCarouselRight();
    } else if (s == "tc") {
      TopRobotModules::rotateCarousel(wifiWaitAndRead().toDouble());
    } else if (s == "tpo") {
      TopRobotModules::movePusherOut();
    } else if (s == "tpi") {
      TopRobotModules::movePusherIn();
    }
  }

  Network::handleOTA();
  delay(10);
}