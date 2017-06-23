#include <CVDSensor.h>

/*
 * CVDSense Library Demo Sketch
 * Admar Schoonen 2016
 * Connect 4 electrodes (piece of metal sheet / foil) to analog pins A0 - A3
 */

/* 
 * Number of capacitive sensors. Needs a minimum of 2. When using only one
 * sensor, set N_SENSORS to 2 and use an unused analog input pin for the second
 * sensor. For 2 or more sensors you don't need to add an unused analog input.
 */
#define N_SENSORS			4

/* 
 * Number of measurements per sensor to take in one cycle. More measurements
 * means more noise reduction / spreading, but is also slower.
 */
#define N_MEASUREMENTS_PER_SENSOR	16

/* cvdSensors is the actual object that contains all the sensors */
CvdSensors<N_SENSORS, N_MEASUREMENTS_PER_SENSOR> cvdSensors;

void setup()
{
	int n;

	/* Delay to make sure serial monitor receives first message */
	delay(500);
	Serial.begin(9600);
	Serial.println();
	Serial.println();
	Serial.println("Switching baudrate to 115200. Make sure to adjust "
		"baudrate in serial monitor as well!");
	Serial.println();
	Serial.println();
	Serial.end();

	/*
	 * Switch baudrate to highest baudrate available. With higher baudrate,
	 * CPU has more time left to do capacitive sensing and thus get better
	 * signal quality.
	 */
	Serial.begin(115200);
	Serial.println();
	Serial.println();

	/* Change approached threshold for each sensor */
	for (n = 0; n < N_SENSORS; n++) {
		/*
		 * Set state transition times to 0 to get more direct feedback
		 * while tuning the threshold levels.
		 */
		cvdSensors.data[n].releasedToApproachedTime = 0;
		cvdSensors.data[n].approachedToReleasedTime = 0;
		cvdSensors.data[n].approachedToPressedTime = 0;
		cvdSensors.data[n].pressedToApproachedTime = 0;

		/* 
		 * approachedToPressedThreshold is set to 150 by default. Set to
		 * lower value to make sensor more sensitive. Do not make it
		 * smaller than releasedToApproachedThreshold.
		 */
		cvdSensors.data[n].approachedToPressedThreshold = 75;

		/*
		 * pressedToApproachedThreshold is set to 120 by default. It
		 * should usually be a little lower than
		 * approachedToPressedThreshold to prevent button instability.
		 */
		cvdSensors.data[n].pressedToApproachedThreshold = 60;
	}
}

void loop()
{
	int n;

	/* 
	 * Call cvdSensors.sample() take do a new measurement cycle for all
	 * sensors 
	 */
	cvdSensors.sample();

	/*
	 * For each button, print current value and if button is pressed or not
         */
	for (n = 0; n < N_SENSORS; n++) {
		Serial.print("button[");
		Serial.print(n);
		Serial.print("]: current value: ");
		Serial.print(cvdSensors.data[n].delta);
		Serial.print(", pressed: ");
		Serial.print(cvdSensors.data[n].buttonIsPressed);
		if (n < N_SENSORS - 1) {	
			Serial.print("\t ");
		} else {
			Serial.println("");
		}
	}
}