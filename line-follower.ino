#include <Arduino.h>

#include "common.h"

#include "raw_sensor.h"
#include "calibrated_sensor.h"
#include "discreet_sensor.h"
#include "sensor.h"

#include "calibrated_sensor_array.h"
#include "sensor_manager.h"

#include "discreet_sensor_reader.h"
#include "memory_sensor_reader.h"

#include "bang_raw_controller.h"
#include "bang_controller.h"
#include "pid_controller.h"

#include "motor.h"
#include "steering.h"

#include "line_follower.h"
#include "demo.h"

#include "configuration.h"

#include "display.h"
#include "input.h"

#include "pin_conf.h"
#include "conf.h"

RawSensor raw1(SENSOR1);
RawSensor raw2(SENSOR2);
RawSensor raw3(SENSOR3);
RawSensor raw4(SENSOR4);

CalibratedSensor calibrated1(&raw1, REVERSED);
CalibratedSensor calibrated2(&raw2, REVERSED);
CalibratedSensor calibrated3(&raw3, REVERSED);
CalibratedSensor calibrated4(&raw4, REVERSED);
CalibratedSensor *calibratedSensors[SENSOR_SIZE] = 
	{ &calibrated1, &calibrated2, &calibrated3, &calibrated4 };
CalibratedSensorArray calibratedSensorArray(calibratedSensors, SENSOR_SIZE);

DiscreetSensor discreet1(&calibrated1, THRESHOLD);
DiscreetSensor discreet2(&calibrated2, THRESHOLD);
DiscreetSensor discreet3(&calibrated3, THRESHOLD);
DiscreetSensor discreet4(&calibrated4, THRESHOLD);

Sensor *sensors[SENSOR_SIZE] = { &discreet1, &discreet2, &discreet3, &discreet4 };
SensorArray sensorArray(sensors, SENSOR_SIZE);

SensorManager manager(sensors, SENSOR_SIZE);

DiscreetSensorReader discreetReader(CUTOFF);
MemorySensorReader reader(&discreetReader);

PIDParameters parameters(TARGET, KP, KI, KD);
PIDController controller(parameters);

Motor leftMotor(LFORW, LBACK, LSPEED);
Motor rightMotor(RFORW, RBACK, RSPEED);
MotorPair motors(&leftMotor, &rightMotor);

Steering steering(&motors);

LineFollower follower(&controller, 
		&sensorArray, 
		&reader, 
		&manager, 
		&steering,
		&calibratedSensorArray);


enum States {
	STANDBY,
	DEMO,
	LINE_FOLLOWING,
	CALIBRATION
};
States state = STANDBY;

Display disp;
ScreenManager screenManager(&disp);

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
}
void pidI() {
	screenManager.push(&iInput);
}
void pidD() {
	screenManager.push(&dInput);
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
}
char *setNames[1] = {
	"PID",
};
void (*setFuncs[1])() = {
	setPID
};
Menu settings(setNames, setFuncs, 1);

void followPauseResume() {
	state = state == STANDBY ? LINE_FOLLOWING : STANDBY;
}
void followStop() {
	state = STANDBY;
	screenManager.back();
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
	screenManager.back();
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
	
	follower.run([](auto *follower) {
		long time = CALIBRATION_SECS * SECOND;
		auto *steering = follower->steering;
		auto *sensors = follower->calibratedSensors;
		
		if (sensors) {
			steering->setTarget(-1000);
			for(long start = millis(); millis() - start < time;) {
				sensors->calibrate();
			}
			steering->stop();
		} else {
			disp.clear();
			disp.write(0, 0, "Failed");
			disp.write(0, 1, "calibration...");
			disp.blink();
			delay(2000);
		}
	});
}
void calibrationManual() {
	screenManager.push(&manual);
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
}
void startSettings() {
	screenManager.push(&settings);
}
void startDemo() {
	state = DEMO;
	screenManager.push(&demoPopup);
}
void startLineFollowing() {
	state = LINE_FOLLOWING;
	screenManager.push(&follow);
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
}
void rightClick() {
	screenManager.right();
}
void okClick() {
	screenManager.ok();
}
void okHold() {
	screenManager.back();
}
void doubleLeftClick() {
	screenManager.doubleLeft();
}
void doubleRightClick() {
	screenManager.doubleRight();
}

ButtonConfig left(LEFT, leftClick, nullptr, doubleLeftClick);
ButtonConfig right(RIGHT, rightClick, nullptr, doubleRightClick);
ButtonConfig ok(OK, okClick, okHold);
ButtonConfig *btns[3] = { &left, &right, &ok };

Input input(btns, 3);

void setup() {
	Serial.begin(9600);
	disp.begin();
	
	/* We don't do this in an initalizer 
	 * as we need to begin the display here... */
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
			auto *sensors = follower.calibratedSensors;
			if (sensors) {
				sensors->calibrate();
			}
			break;
	}
}

void loop() {
	input.tick();
	runState();
	follower.tick();
}
