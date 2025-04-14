#pragma once

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
#define KP 1
#define KI 0
#define KD 0
