#include <Arduino.h>

#include "common.h"

#include "led.h"
#include "raw_sensor.h"
#include "calibrated_sensor.h"
#include "discreet_sensor.h"

#include "sensor_manager.h"
#include "symmetric_sensor_reader.h"
#include "discreet_sensor_reader.h"

#include "pid_controller.h"
#include "bang_controller.h"
#include "bang_raw_controller.h"

#include "motor.h"
#include "steering.h"

#define DEMO 0
#if DEMO
#include "demo.h"
#endif /* DEMO */

/* Pin configuration */
#define LED_SIZE 4
#define LED1 8
#define LED2 9
#define LED3 10
#define LED4 11

#define SENSOR_SIZE 4
#define SENSOR1 A0
#define SENSOR2 A1
#define SENSOR3 A2
#define SENSOR4 A3

#define LFORW 4
#define LBACK 7
#define LSPEED 6

#define RFORW 3
#define RBACK 2
#define RSPEED 5

/* Calibration configuration */
#define SECOND 1000L
#define CALIBRATION_SECS 3

/* Calibrated sensor configuration */
#define REVERSED true

/* Discreet sensor configuration */
#define THRESHOLD 0.7

/* Sensor types
 *  1 - Calibrated sensor: normalized, calibrated
 *  2 - Discreet sensor: Composited from 
        the calibrated sensor, 
	but it only outputs discreet 0 or 1000 values.
 * -1 - Raw: raw analog values (not recommended)
 */
#define SENSOR 2

/* Controller types
 * 1 - Raw bang: simple, rudimentary
 * 2 - Bang: might not even work
 * 3 - PID: recommended
 */
#define CONTROLLER 3

/* Reader types
 * 1 - Symmetric reader: gives each sensor 
 *     less weight as we get closer to the center.
 * 2 - Discreet reader: Composited from the 
 *     symmetric reader, but if we're arbitrarily close
 *     to 0 the given value will be 0.
 */
#define READER 2

/* Discreet reader configuration */
#define CUTOFF 300

/* PID controller configuration */
#define TARGET 0
#define KP .005
#define KI 0.0005
#define KD .8

/* TODO: if someone knows some macro tricks 
 * for repeating these I'd much appreciate it. */
Led led1(LED1);
Led led2(LED2);
Led led3(LED3);
Led led4(LED4);

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
Sensor *sensors[SENSOR_SIZE] = { &discreet1, &discreet2, &discreet3, &discreet4 };
#else
Sensor *sensors[SENSOR_SIZE] = { &raw1, &raw2, &raw3, &raw4 };
#endif /* SENSOR */

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
Steering steering(&leftMotor, &rightMotor);

void calibrateSensors() {
	for (uint i = 0; i < SENSOR_SIZE; i++) {
		calibratedSensors[i]->calibrate();
	}
}

/* TODO: sequence API? */
void calibrationSequence() {
	/* Spin in a circle. */
	steering.setTarget(-1000);
	
	/* For a set time keep calibrating the sensors. */
	for(long start = millis(); millis() - start < CALIBRATION_SECS * SECOND;) {
		calibrateSensors();
	}

	/* Stop spinning. */
	steering.stop();
}

void setupLineFollowing() {
	manager.setCallback(&managerCb, nullptr);

	Serial.println("Starting calibration sequence...");
	calibrationSequence();	
	Serial.println("Done calibration.");
}

void setup() {
	Serial.begin(9600);
	
#if !DEMO
	setupLineFollowing();
#endif /* DEMO */
}

void managerCb(uint *values, uint size) {
	int out = 0;

#if CONTROLLER == 1 
	rawController.calculate(values, size, &out);
#else
	reader.calculate(values, size, &out);
	controller.calculate(out, &out);
#endif /* CONTROLLER */
	
	steering.setTarget(out);
}

void loop() {
#if DEMO
	demo(&led1, &led2, &led3, &led4, &leftMotor, &rightMotor, &steering);
	Serial.println("demo mode");
#else
	manager.tick();
#endif /* DEMO */
}
