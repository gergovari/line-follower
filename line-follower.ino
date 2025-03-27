#include <Arduino.h>

/* A megértéshez érdemes követni a lenti header és cpp fájlokat,
 * hisz nem akartam redundánsan dokumentálni. 
 * Amit angolul írtam nem olyan fontos. */

#include "common.h"

#include "led.h"
#include "raw_sensor.h"
#include "calibrated_sensor.h"
#include "sensor_manager.h"
#include "weighted_sensor_manager.h"
#include "motor.h"
#include "steering.h"

/* Ha a DEMO-t 1-re rakjuk akkor nem az alap program fog lefutni 
 * hanem a hardver fog mindent bemutatni amit tud. 
 * Érdemes nem lerakni a földre ilyenkor a robotot. */
#define DEMO 0
#if DEMO
#include "demo.h"
#endif /* DEMO */

/* Hardver konfiguráció leírása */
/* A dokumentációhoz képest angolul lettek a pinek elnevezve. */
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

/* Kalibrációs paraméterek */
#define SECOND 1000L
#define CALIBRATION_SECS 5

/* TODO: if someone knows some macro tricks 
 * for repeating these I'd much appreciate it. */
Led led1(LED1);
Led led2(LED2);
Led led3(LED3);
Led led4(LED4);

RawSensor rawSensor1(SENSOR1);
CalibratedSensor sensor1(&rawSensor1);

RawSensor rawSensor2(SENSOR2);
CalibratedSensor sensor2(&rawSensor2);

RawSensor rawSensor3(SENSOR3);
CalibratedSensor sensor3(&rawSensor3);

RawSensor rawSensor4(SENSOR4);
CalibratedSensor sensor4(&rawSensor4);

CalibratedSensor *sensors[SENSOR_SIZE] = { &sensor1, &sensor2, &sensor3, &sensor4 };
double weights[SENSOR_SIZE] = { -1, 0, .5, 1 };

SensorManager sensorManager(sensors, SENSOR_SIZE);
WeightedSensorManager weightedManager(&sensorManager, 1, weights);

Motor leftMotor(LFORW, LBACK, LSPEED);
Motor rightMotor(RFORW, RBACK, RSPEED);
Steering steering(&leftMotor, &rightMotor);

/* TODO: sequence API? */
void startSpinSequence() {
	steering.setTarget(-1000);
}
void stopSpinSequence() {
	steering.stop();
}
void calibrateSensors() {
	uint time = CALIBRATION_SECS * SECOND; 

	/* Ha megpörgetjük a robotot úgy hogy mindenféle színen 
	 * (értsd vonal és alatta padló) átmegy, 
	 * akkor a lehetséges szenzor értékeket megkaphatjuk. */
	startSpinSequence();
	
	for(long start = millis(); millis() - start < time;) {
		sensorManager.calibrate();
	}

	stopSpinSequence();
}

void setup() {
	Serial.begin(9600);
	
#if !DEMO
	weightedManager.setCallback(&wCb);

	Serial.println("Starting calibration sequence...");
	calibrateSensors();	
	Serial.println("Done calibration.");
#endif /* DEMO */
}

void wCb(int value) {
	Serial.println(value);
}

void followLine() {
	/* Ezzel indítjuk el a szenzor olvasást. */
	weightedManager.tick();
}

void loop() {
#if DEMO
	demo(&led1, &led2, &led3, &led4, &leftMotor, &rightMotor, &steering);
	Serial.println("demo mode");
#else
	followLine();
#endif /* DEMO */
}
