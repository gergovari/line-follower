#include <Arduino.h>

/* A megértéshez érdemes követni a lenti header és cpp fájlokat,
 * hisz nem akartam redundánsan dokumentálni. 
 * Amit angolul írtam nem olyan fontos. */

#include "common.h"

#include "led.h"
#include "raw_sensor.h"
#include "calibrated_sensor.h"
#include "sensor_manager.h"

/* Hardver konfiguráció leírása */
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
SensorManager sensorManager((Sensor**)&sensors, SENSOR_SIZE);

void startSpinSequence() {

	/* TODO: make robot spin around */
}

void stopSpinSequence() {

	/* TODO: make robot stop spinning */
}

void calibrateSensors(uint *l, uint *h) {
	/* 5 seconds */
	uint time = CALIBRATION_SECS * SECOND; 

	/* Ha megpörgetjük a robotot úgy hogy mindenféle színen 
	 * (értsd vonal és alatta padló) átmegy, 
	 * akkor a lehetséges szenzor értékeket megkaphatjuk. */
	startSpinSequence();
	
	for(long start = millis(); millis() - start < time;) {
		for (int i = 0; i < sizeof(sensors) / sizeof(CalibratedSensor*); i++) {
			sensors[i]->calibrate(l, h);
		}
	}

	stopSpinSequence();
}

void setup()
{
	uint l = 0;
	uint h = 0;

	Serial.begin(9600);
	
	sensorManager.setCallback(&sensorCb);
	
	Serial.println("Starting calibration sequence...");
	calibrateSensors(&l, &h);
	Serial.print("Done calibration sequence: ");
	Serial.print(l);
	Serial.print(", ");
	Serial.print(h);
	Serial.println();
}

/* Ha a DEMO-t 1-re rakjuk akkor nem az alap program fog lefutni 
 * hanem a hardver fog mindent bemutatni amit tud. 
 * Érdemes nem lerakni a földre ilyenkor a robotot. */
#define DEMO 0
#if demo
void demo() {
	test_leds();
}

void test_leds() {
	delay(500);
	led1.set(false);
	delay(2000);

	led2.set(false);
	delay(2000);

	led3.set(false);
	delay(2000);

	led4.set(false);
	delay(2000);

	led1.set(true);
	delay(500);

	led2.set(true);
	delay(500);

	led3.set(true);
	delay(500);

	led4.set(true);
	delay(500);
}
#endif /* DEMO */

/* Itt lehet majd a szenzor értékek alapján a motorok sebességét irányítani. */
void sensorCb(uint *values, uint size) {
	Serial.print(values[0]);
	Serial.print(", ");
	Serial.print(rawSensor1.get());
	Serial.println();
}

void followLine() {
	/* Ezzel indítjuk el a szenzor olvasást. */
	sensorManager.tick();
}

void loop()
{
#if DEMO
	demo();
#else
	followLine();
#endif /* DEMO */
}
