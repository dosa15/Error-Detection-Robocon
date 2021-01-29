# Error-Detection-Robocon
Error detection for the Throwing Robot and Defensive Robot to keep them in balance even in case of uneven terrains and PWM fluctuation in a motor.

Sensor used for the Gyroscope is MPU6050 for TR and DR

MPU6050 is a 6 dimension motion tracking sensor that includes a gyroscope, accelerometer and a thermometer. It is a Micro Electro-Mechanical system (MEMS) that can capture motion in X, Y, Z axes on both the gyroscope and accelerometer. It also has a Digital Motion Processor (DMP), which has property to solve complex calculations.

Operating voltage: 3V to 5V
Acceleration Range: ±2g, ±4g, ±8g, ±16g
Gyroscope range: ±250°/s, ±500°/s, ±1000°/s, ±2000°/s

MPU6050 has a 16-bit analog to digital converter hardware that uses I2C module to interface with Arduino.

Logic:

While interfacing with NodeMCU, we use the value outputted by the sensor along the X-axis of the bots to compute the required PWM for each motor with regard to the changes in weight of the bot as it moves around the arena.
If we place the sensor at the center of the bot, a change in weight towards the left or right side of the bot will trigger a change in the Roll (X-axis) value of the sensor.
If the Roll value is positive (clockwise rotation on the axis), it means the weight has shifted to the right side of the bot, hence we increase the PWM of the right hand side motors.
If the Roll value is negative (anti-clockwise rotation on the axis), it means the weight has shifted to the left side of the bot, hence we increase the PWM of the left hand side motors.
