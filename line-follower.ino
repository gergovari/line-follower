#include <Arduino.h>

#include "common.h"

#include "raw_sensor.h"
#include "calibrated_sensor.h"
#include "discreet_sensor.h"
#include "sensor.h"

#include "calibrated_sensor_array.h"
#include "sensor_manager.h"

#include "symmetric_sensor_reader.h"
#include "discreet_sensor_reader.h"

#include "bang_raw_controller.h"
#include "bang_controller.h"
#include "pid_controller.h"

#include "motor.h"
#include "steering.h"

#include "line_follower.h"

#include "configuration.h"

#include "display.h"
#include "input.h"

#include "demo.h"


#include "pin_conf.h"
#include "conf.h"

RawSensor raw1(SENSOR1);
RawSensor raw2(SENSOR2);
RawSensor raw3(SENSOR3);
RawSensor raw4(SENSOR4);

#if SENSOR == 1 || SENSOR == 2
CalibratedSensor calibrated1(&raw1, REVERSED);
CalibratedSensor calibrated2(&raw2, REVERSED);
CalibratedSensor calibrated3(&raw3, REVERSED);
CalibratedSensor calibrated4(&raw4, REVERSED);
CalibratedSensor *calibratedSensors[SENSOR_SIZE] = 
	{ &calibrated1, &calibrated2, &calibrated3, &calibrated4 };
#endif /* SENSOR */

#if SENSOR == 2
DiscreetSensor discreet1(&calibrated1, THRESHOLD);
DiscreetSensor discreet2(&calibrated2, THRESHOLD);
DiscreetSensor discreet3(&calibrated3, THRESHOLD);
DiscreetSensor discreet4(&calibrated4, THRESHOLD);
#endif /* SENSOR */

#if SENSOR == 1
Sensor *sensors[SENSOR_SIZE] = { &calibrated1, &calibrated2, &calibrated3, &calibrated4 };
#elif SENSOR == 2
//Sensor *sensors[SENSOR_SIZE] = { &discreet1, &discreet2, &discreet3, &discreet4 };
Sensor *sensors[SENSOR_SIZE] = { &discreet1, &discreet2, &discreet3, &discreet4 };
#else
Sensor *sensors[SENSOR_SIZE] = { &raw1, &raw2, &raw3, &raw4 };
#endif /* SENSOR */
CalibratedSensorArray sensorArray((Sensor*)sensors, SENSOR_SIZE);

SensorManager manager(sensors, SENSOR_SIZE);

#if READER == 1
SymmetricSensorReader reader;
#else
DiscreetSensorReader reader(CUTOFF);
#endif /* READER */

#if CONTROLLER == 1
BangRawController rawController(false);
#elif CONTROLLER == 2
BangController controller;
#else
PIDParameters parameters(TARGET, KP, KI, KD);
PIDController controller(parameters);
#endif /* CONTROLLER */

Motor leftMotor(LFORW, LBACK, LSPEED);
Motor rightMotor(RFORW, RBACK, RSPEED);
MotorPair motors(&leftMotor, &rightMotor);

Steering steering(&leftMotor, &rightMotor);

LineFollower follower(&controller, &sensorArray, &reader, &manager, &motors, &steering);


enum States {
	STANDBY,
	DEMO,
	LINE_FOLLOWING,
	CALIBRATION
};
States state = STANDBY;

ScreenManager screenManager;
Display disp;

#if CONTROLLER == 3
Configuration config(TARGET, KP, KI, KD);

void pInSet(double in) {
	config.p = in;
	config.save();
	config.apply(&controller);
}
DoubleInput pInput("Proportional", pInSet, KP);

void iInSet(double in) {
	config.i = in;
	config.save();
	config.apply(&controller);
}
DoubleInput iInput("Integrate", iInSet, KI);

void dInSet(double in) {
	config.d = in;
	config.save();
	config.apply(&controller);
}
DoubleInput dInput("Derivate", dInSet, KD);

void pidP() {
	screenManager.push(&pInput);
	disp.show(screenManager.current);
}
void pidI() {
	screenManager.push(&iInput);
	disp.show(screenManager.current);
}
void pidD() {
	screenManager.push(&dInput);
	disp.show(screenManager.current);
}

char *pidNames[3] = {
	"P",
	"I",
	"D"
};
void (*pidFuncs[3])() = {
	pidP,
	pidI,
	pidD
};
Menu pid(pidNames, pidFuncs, 3);

void setPID() {
	screenManager.push(&pid);
	disp.show(screenManager.current);
}
char *setNames[1] = {
	"PID",
};
void (*setFuncs[1])() = {
	setPID
};
Menu settings(setNames, setFuncs, 1);
#else
char *setNames[0] = {};
void (*setFuncs[0])() = {};
Menu settings(setNames, setFuncs, 0);
#endif

void followPauseResume() {
	state = state == STANDBY ? LINE_FOLLOWING : STANDBY;
}
void followStop() {
	state = STANDBY;
	screenManager.back();
	disp.show(screenManager.current);
}
char *followNames[2] = {
	"PAUSE/RESUME",
	"STOP"
};
void (*followFuncs[2])() = {
	followPauseResume,
	followStop
};
Menu follow(followNames, followFuncs, 2);

void manualStart() {
	state = CALIBRATION;
}
void manualStop() {
	state = STANDBY;
}

char *manualNames[2] = {
	"START",
	"STOP"
};
void (*manualFuncs[2])() = {
	manualStart,
	manualStop
};
Menu manual(manualNames, manualFuncs, 2);

void calibrationAutomatic() {
	disp.clear();
	disp.write(0, 0, "Calibration");
	disp.write(0, 1, "started...");
	disp.blink();
	
	// TODO
	//calibrationSequence();

	disp.show(screenManager.current);
}
void calibrationManual() {
	screenManager.push(&manual);
	disp.show(screenManager.current);
}

char *calibrationNames[2] = {
	"AUTOMATIC",
	"MANUAL"
};
void (*calibrationFuncs[2])() = {
	calibrationAutomatic,
	calibrationManual
};
Menu calibration(calibrationNames, calibrationFuncs, 2);

Popup demoPopup("Demo mode on...");

void startCalibration() {
	screenManager.push(&calibration);
	disp.show(screenManager.current);
}
void startSettings() {
	screenManager.push(&settings);
	disp.show(screenManager.current);
}
void startDemo() {
	state = DEMO;
	screenManager.push(&demoPopup);
	disp.show(screenManager.current);
}
void startLineFollowing() {
	state = LINE_FOLLOWING;
	screenManager.push(&follow);
	disp.show(screenManager.current);
}

char *startNames[4] = {
	"CALIBR",
	"CONFIG",
	"DEMO",
	"FOLLOW"
};
void (*startFuncs[4])() = {
	startCalibration,
	startSettings,
	startDemo,
	startLineFollowing
};
Menu start(startNames, startFuncs, 4);

void leftClick() {
	screenManager.left();
	disp.show(screenManager.current);
}
void rightClick() {
	screenManager.right();
	disp.show(screenManager.current);
}
void okClick() {
	screenManager.ok();
	disp.show(screenManager.current);
}
void okHold() {
	screenManager.back();
	disp.show(screenManager.current);
}
void doubleLeftClick() {
	screenManager.doubleLeft();
	disp.show(screenManager.current);
}
void doubleRightClick() {
	screenManager.doubleRight();
	disp.show(screenManager.current);
}

ButtonConfig left(8, leftClick, nullptr, doubleLeftClick);
ButtonConfig right(9, rightClick, nullptr, doubleRightClick);
ButtonConfig ok(10, okClick, okHold);
ButtonConfig *btns[3] = { &left, &right, &ok };

Input input(btns, 3);

void setup() {
	Serial.begin(9600);
	disp.begin();
	
	screenManager.current = &start;
	disp.show(screenManager.current);
}

void runState() {
	switch (state) {
		case STANDBY:
			follower.state = LineFollowerStates::STANDBY;
			follower.tick();
			break;
		case DEMO:
			follower.run(demo);
			state = STANDBY;
			break;
		case LINE_FOLLOWING:
			follower.state = LineFollowerStates::FOLLOW;
			break;
		case CALIBRATION:
			follower.run([](auto *follower) {
				long time = CALIBRATION_SECS * SECOND;
				auto *steering = follower->steering;
				auto *sensors = follower->sensors;

				if (sensors->calibrated) {
					steering->setTarget(-1000);
					for(long start = millis(); millis() - start < time;) {
						((CalibratedSensorArray*)(sensors))->calibrate();
					}
					steering->stop();
				}
			});
			break;
	}
}

void loop() {
	input.tick();
	runState();
	follower.tick();
}
