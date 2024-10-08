#ifdef ENABLE_TOP_ROBOT

#include <Arduino.h>
#include <constants.h>

#include <drivetrain.h>
// #include <hotspot.h>
#include <network.h>
#include <tape_sensors.h>
#include <motor.h>
#include <stepper.h>
#include <servo.h>
#include <user_interface.h>
#include <top_robot_actions.h>
#include <top_robot_modules.h>

void setup() {
  Serial.begin(9600);
  Serial.println("initializing");

  UserInterface::setupUserInterface();
  Drivetrain::setupDrivetrain();
  // Hotspot::setupWifi();
  Network::setupWifi();
  TapeSensors::setupTapeSensors();
  TopRobotModules::setupTopRobotModules();
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
String waitAndRead() {
  while (Serial.available() == 0) {
    // wait
  }
  String output = Serial.readString();
  Serial.println("Received: " + output);
  return output;
}

// String wifiWaitAndRead();
// String wifiWaitAndRead() {
//   while (!Hotspot::wifiInput()) {
//     // wait
//   }
//   return Hotspot::message;
// }

void loop() {
  // TOP ROBOT COMPETITION ROUTINE
  if (UserInterface::isButtonPressed()) {
    int numBurgers = 4;

    #ifdef ENABLE_HANDSHAKE
    TopRobotModules::movePusher(-1, false);
    UserInterface::displayOLED("Waiting for handshake!");
    Network::waitForHandshake();
    UserInterface::displayOLED("Handshake established");
    delay(200);
    #endif

    UserInterface::displayOLED("INGREDIENTS");
    
    #ifdef ENABLE_HANDSHAKE
    TopRobotModules::movePusher(1, false);
    #endif
    TopRobotActions::startToBuns();
    for (int i = 1; i <= numBurgers; i++) {
      TopRobotActions::bottomBunDriveProcedure();
      // intake one bottom bun
      TopRobotActions::inputBun();
      // drive to cutting
      TopRobotActions::bunsToCutting();
      // serve bun
      TopRobotActions::transferRoutine();
      // handshake for bottom bun initially
      #ifdef ENABLE_HANDSHAKE
      if (i == 1) {
        Network::waitForHandshake();
      }
      #endif

      // go to patty
      TopRobotActions::cuttingToPatties();
      // intake one patty
      TopRobotActions::inputPatty();
      // go to cooktop
      TopRobotActions::pattiesToCooktop();
      // serve patty
      TopRobotActions::transferRoutine();

      // go to buns
      TopRobotActions::cooktopToBuns();
      // intake one top bun
      TopRobotActions::inputBun(false); // spin the top bun the other way to avoid jamming
      // go to cooktop
      TopRobotActions::bunsToCutting();
      delay(1000); // wait one second for the top bun to come around
      // serve bun
      TopRobotActions::transferRoutine();
      // handshake for top bun
      #ifdef ENABLE_HANDSHAKE
      Network::waitForHandshake();
      #endif

      // drive away
      TopRobotActions::cuttingToBuns();
    }

    TopRobotActions::resetToStart();
  }
  
    // String s = waitAndRead();
    // if (s == "tic") {
    //   TopRobotModules::closeInputScraperFast();
    // } else if (s == "ticp") {
    //   TopRobotModules::closeInputScraperPatty();
    // } else if (s == "tio") {
    //   TopRobotModules::openInputScraper();
    // } else if (s == "ti") {
    //   TopRobotModules::setInputScraper(waitAndRead().toDouble());
    // } else if (s == "tor") {
    //   TopRobotModules::raiseOutputScraper();
    // } else if (s == "tol") {
    //   TopRobotModules::lowerOutputScraper();
    // } else if (s == "to") {
    //   TopRobotModules::setOutputScraper(waitAndRead().toDouble());
    // } else if (s == "tcl") {
    //   TopRobotModules::rotateCarouselLeft();
    // } else if (s == "tcr") {
    //   TopRobotModules::rotateCarouselRight();
    // } else if (s == "tc") {
    //   TopRobotModules::rotateCarousel(waitAndRead().toDouble());
    // } else if (s == "tpo") {
    //   TopRobotActions::movePusherOut();
    // } else if (s == "tpi") {
    //   TopRobotActions::movePusherIn();
    // } else if (s == "tp") {
    //   TopRobotModules::movePusher(waitAndRead().toDouble(), false);
    // } else if (s == "tpr") {
    //   TopRobotActions::reloadPusherPatty();
    // }


  // if (Hotspot::wifiInput()) {
  //   String s = Hotspot::message;
  //   UserInterface::displayOLED(s); // echo
  //   if (s == "test") {
  //     Hotspot::wifiPrintln("Hello World!");
  //   // drive testing
  //   } else if (s == "F") {
  //     Drivetrain::driveMecanum(0, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "B") {
  //     Drivetrain::driveMecanum(180, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "L") {
  //     Drivetrain::driveMecanum(90, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "R") {
  //     Drivetrain::driveMecanum(-90, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "time") {
  //     duration = wifiWaitAndRead().toInt();
  //   } else if (s == "power") {
  //     power = wifiWaitAndRead().toDouble();
  //   } else if (s == "FL") {
  //     Drivetrain::driveMotors(power, 0, 0, 0);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "FR") {
  //     Drivetrain::driveMotors(0, power, 0, 0);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "BL") {
  //     Drivetrain::driveMotors(0, 0, power, 0);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "BR") {
  //     Drivetrain::driveMotors(0, 0, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "print") {
  //     Hotspot::wifiPrintln("Duration: " + String(duration) + " Power: " + String(power));
  //     Hotspot::wifiPrintln("Drive time: " + String(driveTime) + " Spin time: " + String(spinTime));
  //     Hotspot::wifiPrintln("Drive power: " + String(power) + " Spin power: " + String(spinPower));
  //     Hotspot::wifiPrintln("Slow time: " + String(slowTime) + " Fast time: " + String(fastTime));
  //     Hotspot::wifiPrintln("Slow power: " + String(slowPower) + " Fast power: " + String(fastPower));
  //     Hotspot::wifiPrintln("Wall delay: " + String(wallTime));
  //   } else if (s == "tape") {
  //     Hotspot::wifiPrintln(TapeSensors::getValuesStr());
  //   } else if (s == "W") {
  //     String s = wifiWaitAndRead();
  //     int num = s.substring(0, 1).toInt();
  //     DriveDirection driveDirection = s.substring(1, 2) == "F" ? DriveDirection::FORWARD : DriveDirection::BACKWARD;
  //     WallLocation wallLocation = s.substring(2, 3) == "R" ? WallLocation::RIGHT : WallLocation::LEFT;
  //     Drivetrain::wallFollow(driveDirection, wallLocation, num, wallTime, true);
  //   } else if (s == "mec") {
  //     double angle = wifiWaitAndRead().toDouble();
  //     Drivetrain::driveMecanum(angle, 0, power);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "spin") {
  //     double spinPower = wifiWaitAndRead().toDouble();
  //     Drivetrain::driveMecanum(0, spinPower, 0);
  //     delay(duration);
  //     Drivetrain::stopAll();
  //   } else if (s == "WW") {
  //     DriveDirection driveDirection = wifiWaitAndRead() == "R" ? DriveDirection::RIGHT : DriveDirection::LEFT;
  //     Drivetrain::wallToWall(driveDirection, slowTime, fastTime, slowPower, fastPower);
  //   } else if (s == "driveT") {
  //     driveTime = wifiWaitAndRead().toInt();
  //   } else if (s == "spinT") {
  //     spinTime = wifiWaitAndRead().toInt();
  //   } else if (s == "slowT") {
  //     slowTime = wifiWaitAndRead().toInt();
  //   } else if (s == "fastT") {
  //     fastTime = wifiWaitAndRead().toInt();
  //   } else if (s == "wallT") {
  //     wallTime = wifiWaitAndRead().toInt();
  //   } else if (s == "slowP") {
  //     slowPower = wifiWaitAndRead().toDouble();
  //   } else if (s == "fastP") {
  //     fastPower = wifiWaitAndRead().toDouble();
  //   } else if (s == "spinP") {
  //     spinPower = wifiWaitAndRead().toDouble();
  //   } else if (s == "WWS") {
  //     DriveDirection driveDirection = wifiWaitAndRead() == "R" ? DriveDirection::RIGHT : DriveDirection::LEFT;
  //     Drivetrain::wallToWallSpin(driveDirection, driveTime, spinTime, power, spinPower);
  //   } else if (s == "WWSS") {
  //     Drivetrain::wallToWallSpinSlow();
  //   // top robot modules
  //   } else if (s == "tic") {
  //     TopRobotModules::closeInputScraper();
  //   } else if (s == "ticp") {
  //     TopRobotModules::closeInputScraperPatty();
  //   } else if (s == "tio") {
  //     TopRobotModules::openInputScraper();
  //   } else if (s == "ti") {
  //     TopRobotModules::setInputScraper(wifiWaitAndRead().toDouble());
  //   } else if (s == "tor") {
  //     TopRobotModules::raiseOutputScraper();
  //   } else if (s == "tol") {
  //     TopRobotModules::lowerOutputScraper();
  //   } else if (s == "to") {
  //     TopRobotModules::setOutputScraper(wifiWaitAndRead().toDouble());
  //   } else if (s == "tcl") {
  //     TopRobotModules::rotateCarouselLeft();
  //   } else if (s == "tcr") {
  //     TopRobotModules::rotateCarouselRight();
  //   } else if (s == "tc") {
  //     TopRobotModules::rotateCarousel(wifiWaitAndRead().toDouble());
  //   } else if (s == "tpo") {
  //     TopRobotActions::movePusherOut();
  //   } else if (s == "tpi") {
  //     TopRobotActions::movePusherIn();
  //   } else if (s == "tp") {
  //     TopRobotModules::movePusher(wifiWaitAndRead().toDouble(), false);
  //   } else if (s == "tpr") {
  //     TopRobotActions::reloadPusherPatty();
  //   // top robot driving
  //   } else if (s == "s2b") {
  //     TopRobotActions::startToBuns();
  //   } else if (s == "bbd") {
  //     TopRobotActions::bottomBunDriveProcedure();
  //   } else if (s == "b2cu") {
  //     TopRobotActions::bunsToCutting();
  //   } else if (s == "c2p") {
  //     TopRobotActions::cuttingToPatties();
  //   } else if (s == "p2c") {
  //     TopRobotActions::pattiesToCooktop();
  //   } else if (s == "c2b") {
  //     TopRobotActions::cooktopToBuns();
  //   } else if (s == "c2p") {
  //     TopRobotActions::cuttingToPatties();
  //   } else if (s == "tir") {
  //     TopRobotActions::inputRoutine();
  //   } else if (s == "tt") {
  //     TopRobotActions::transferRoutine();
  //   }
  // }

  // Hotspot::handleOTA();
  // delay(10);
}

#endif