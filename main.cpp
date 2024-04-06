#include "mbed.h"
#include "LSM6DSLSensor.h"

#define PI 3.141592654

static DevI2C devI2c(PB_11, PB_10);
static LSM6DSLSensor acc_gyro(&devI2c, 0xD4, D4, D5); // high address

// Function to compute the angle in degrees
float computeAngle(int x, int y, int z) {
    return atan(static_cast<float>(x) / sqrt(y * y + z * z)) * 180.0 / PI;
}

int main() {
    uint8_t id;
    int32_t axes[3];
    float angle;

    // Initialize accelerometer
    acc_gyro.init(NULL);
    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while (1) {
        // Read accelerometer data
        acc_gyro.get_x_axes(axes);
        
        // Compute angle
        angle = computeAngle(axes[0], axes[1], axes[2]);
        
        // Print accelerometer data and angle
        printf("LSM6DSL: %6ld, %6ld, %6ld, %3.2f degrees\r\n", axes[0], axes[1], axes[2], angle);

        // Wait for 2 seconds
        ThisThread::sleep_for(2000ms);
    }
}