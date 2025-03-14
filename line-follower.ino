#include <Arduino.h>

typedef unsigned int uint;
typedef uint Pin;

class Led {
	private:
		Pin pin;
	public:
		Led(Pin p);
		void set(bool state);
};

Led::Led(Pin p) {
	pin = p;

	pinMode(pin, OUTPUT);
	set(true);
}

void Led::set(bool state) {
	digitalWrite(pin, state);
}


class Sensor {
	private:
		Pin pin;
	public:
		Sensor(Pin p);
		uint get();
};

Sensor::Sensor(Pin p) {
	pin = p;

	pinMode(pin, INPUT);
}

uint Sensor::get() {
	return analogRead(pin);
}

typedef void(*SensorManagerCallback)(uint*, uint) ;

class SensorManager {
	private:
		SensorManagerCallback callback;
		uint size;
		Sensor **sensors;

	public:
		SensorManager(Sensor **se, uint si);

		void setCallback(SensorManagerCallback cb);
		void tick();
};

SensorManager::SensorManager(Sensor **se, uint si) {
	sensors = se;
	size = si;
}

void SensorManager::setCallback(SensorManagerCallback cb) {
	callback = cb;
}

void SensorManager::tick() {
	uint *values = malloc(size * sizeof(uint));
	
	for (int i = 0; i < size; i++) {
		values[i] = sensors[i]->get();
	}

	callback(values, size);
	free(values);
}

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

#define SENSOR_WEIGHT_UNIT 10
#define SENSOR1_WEIGHT -1
#define SENSOR2_WEIGHT -2
#define SENSOR3_WEIGHT 2
#define SENSOR4_WEIGHT 1

Led led1(LED1);
Led led2(LED2);
Led led3(LED3);
Led led4(LED4);

Sensor sensor1(SENSOR1);
Sensor sensor2(SENSOR2);
Sensor sensor3(SENSOR3);
Sensor sensor4(SENSOR4);

Sensor *sensors[SENSOR_SIZE] = { &sensor1, &sensor2, &sensor3, &sensor4 };
SensorManager sensorManager((Sensor**)&sensors, SENSOR_SIZE);

void arraySum(uint *arr, uint size, long *result) {
	for (int i = 0; i < size; i++) {
		(*result) += arr[i];
	}
}

void weightedArraySum(uint *arr, uint* weights, uint size, long *result) {
	for (int i = 0; i < size; i++) {
		(*result) += arr[i] * weights[i];
	}
}

void weightedAverage(uint *values, uint *weights, uint size, long *result) {
	long valueSum = 0; 
	long weightedSum = 0; 
	
	arraySum(values, size, &valueSum);
	weightedArraySum(values, weights, size, &weightedSum);

	(*result) = weightedSum / valueSum;
}

uint sensorWeights[SENSOR_SIZE] = {
	SENSOR1_WEIGHT * SENSOR_WEIGHT_UNIT,
	SENSOR2_WEIGHT * SENSOR_WEIGHT_UNIT,
	SENSOR3_WEIGHT * SENSOR_WEIGHT_UNIT,
	SENSOR4_WEIGHT * SENSOR_WEIGHT_UNIT,
};

void sensorCb(uint *values, uint size) {
	
	long error;

	weightedAverage(values, sensorWeights, size, &error);
	Serial.println(error);
}

void setup()
{
	Serial.begin(9600);
	
	sensorManager.setCallback(&sensorCb);
}

#define DEMO 0
#if demo
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

void loop()
{
#if DEMO
	test_leds();
#else
	sensorManager.tick();
#endif /* DEMO */
}
