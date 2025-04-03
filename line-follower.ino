#include <Arduino.h>

#include "common.h"

#include "led.h"
#include "raw_sensor.h"
#include "calibrated_sensor.h"

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

/* Calibration parameters */
#define SECOND 1000L
#define CALIBRATION_SECS 3

/* Controller types
 * 1 - Raw bang (simple, rudimentary)
 * 2 - Bang (might not even work)
 * 3 - PID (final choice) 
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

RawSensor rawSensor1(SENSOR1);
RawSensor rawSensor2(SENSOR2);
RawSensor rawSensor3(SENSOR3);
RawSensor rawSensor4(SENSOR4);

CalibratedSensor sensor1(&rawSensor1, true);
CalibratedSensor sensor2(&rawSensor2, true);
CalibratedSensor sensor3(&rawSensor3, true);
CalibratedSensor sensor4(&rawSensor4, true);
CalibratedSensor *calibratedSensors[SENSOR_SIZE] = { &sensor1, &sensor2, &sensor3, &sensor4 };

SensorManager manager(calibratedSensors, SENSOR_SIZE);

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
