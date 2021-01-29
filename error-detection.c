#include<Wire.h>;

// default address of the MPU is 0x68
const int MPU_addr = 0x68;

#define FR_FWD 1 // Front Right Wheel's Motor for Forward direction
#define FR_BWD 2 // Front Right Wheel's Motor for Backward direction
#define FL_FWD 3 // Front Left Wheel's Motor for Forward direction
#define FL_BWD 4 // Front Left Wheel's Motor for Backward direction
#define BR_FWD 5 // Back Right Wheel's Motor for Forward direction
#define BR_BWD 6 // Back Right Wheel's Motor for Backward direction
#define BL_FWD 7 // Back Left Wheel's Motor for Forward direction
#define BL_BWD 8 // Back Left Wheel's Motor for Backward direction

int fr_motor, fl_motor, br_motor, bl_motor;

void setup()
{
    Serial.begin(9600);
    // Serial.println ("Press any key to start");
    // while (Serial.available() == 0);
    Wire.begin();
    Wire.beginTransmission(MPU_addr);

    // Configure the power mode of the sensor
    Wire.write(0x6B);
    Wire.write(0x00);

    // Configure the Gryoscope sensor
    Wire.write(0x1B);
    Wire.write(0x10);

    // Configure the Accelerometer sensor
    Wire.write(0x1C);
    Wire.write(0x00);

    // ending the transmission
    Wire.endTransmission(true);

    fr_motor = fl_motor = br_motor = bl_motor = 230;
}

void loop()
{
    // reading the registers of the Gyroscope (starting with GYRO_XOUT_H)
    Wire.beginTransmission(MPU_addr);

    // address of the first register of X Axis
    Wire.write(0x43);
    Wire.endTransmission(false);

    // reading 2 bytes of the output for a pair of registers of the X axis of the Gyroscope
    Wire.requestFrom(MPU_addr, 2, true);
    int16_t XGyroFull = Wire.read() << 8 | Wire.read();
    //  int16_t YGyroFull = Wire.read() << 8 | Wire.read();
    //  int16_t ZGyroFull = Wire.read() << 8 | Wire.read();

    // converting the read data according to the sensitivity of the Gyroscope
    float XGyroFinal = (float)XGyroFull/32.8;
    //  float YGyroFinal = (float)YGyroFull/32.8;
    //  float ZGyroFinal = (float)ZGyroFull/32.8;

    int fr_increment = fr_motor, fl_increment = fl_motor, br_increment = br_motor, bl_increment = bl_motor;

    //printing the Gyroscope readings
    Serial.print("X Axis = ");
    Serial.print(XGyroFinal);
    Serial.println(" deg/s");
    //  Serial.print("Y Axis = ");
    //  Serial.print(YGyroFinal);
    //  Serial.println(" deg/s");
    //  Serial.print("Z Axis = ");
    //  Serial.print(ZGyroFinal);
    //  Serial.println(" deg/s");

    if (XGyroFinal > 0)     
    {
        fr_increment += XGyroFinal;
        br_increment += XGyroFinal;
        Serial.print("Increased PWM on right side motors to ");
        Serial.println(fr_increment);
    }
    else
    {
        fl_increment += XGyroFinal;
        bl_increment += XGyroFinal;
        Serial.print("Increased PWM on left side motors to ");
        Serial.println(fl_increment);
    }

    analogWrite(FL_FWD, fl_motor);
    analogWrite(FR_FWD, fr_motor);
    analogWrite(BL_FWD, bl_motor);
    analogWrite(BR_FWD, br_motor);

    Serial.print("Front Right motor: ");
    Serial.println(fr_increment);
    Serial.print("Front Left motor: ");
    Serial.println(fl_increment);
    Serial.print("Back Right motor: ");
    Serial.println(br_increment);
    Serial.print("Back Left motor: ");
    Serial.println(bl_increment);

    // Wait for 1 second to ease readability of test outputs
    // delay(1000);
}