#pragma once

#include "led.h"
#include "motor.h"
#include "steering.h"

#include <Arduino.h>

void test_leds(Led *led1, Led *led2, Led *led3, Led *led4) {
	delay(500);
	led1->set(false);
	delay(1000);
	led2->set(false);
	delay(1000);
	led3->set(false);
	delay(1000);
	led4->set(false);
	delay(1000);
	led1->set(true);
	delay(500);
	led2->set(true);
	delay(500);
	led3->set(true);
	delay(500);
	led4->set(true);
	delay(500);
}

void test_motors(Motor *left, Motor *right) {
	left->setSpeed(1000);
	right->setSpeed(1000);
	delay(1000);
	left->setSpeed(-1);
	right->setSpeed(-1);
	delay(2000);
	left->setSpeed(1000);
	right->setSpeed(1000);
	delay(1000);
	left->setSpeed(-1);
	right->setSpeed(-1);
	delay(2000);
	left->setSpeed(0);
	right->setSpeed(0);
	delay(1000);
}

void test_steering(Steering *steering) {
	steering->setTarget(0);
	delay(2000);
	steering->setTarget(-500);
	delay(2000);
	steering->setTarget(500);
	delay(2000);
	steering->setTarget(-1000);
	delay(2000);
	steering->setTarget(1000);
	delay(2000);
	steering->stop();
	delay(1000);
}

void demo(LineFollower *follower) 
{
	auto left = follower->motors->left;
	auto right = follower->motors->right;
	auto steering = follower->steering;

	//test_leds(led1, led2, led3, led4);
	test_motors(left, right);
	test_steering(steering);
}
