#include "mbed.h"
#include "MMA7660.h"
#include "C12832.h"

MMA7660 MMA(p28, p27);
C12832 lcd(p5, p7, p6, p8, p11);

// Define the PWM pins for controlling the LED colors
PwmOut redLed(p23);
PwmOut greenLed(p24);
PwmOut blueLed(p25);

// Function to map the accelerometer values to the LED brightness range
float map(float value, float in_min, float in_max, float out_min, float out_max) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main() {
    if (MMA.testConnection())

    lcd.cls();
    lcd.locate(0,0);
    lcd.printf("MMA7660 Test\n");

    // Set the PWM period to 20ms
    redLed.period(0.02);
    greenLed.period(0.02);
    blueLed.period(0.02);

    while(1) {
        // Read the accelerometer values
        float x = MMA.x();
        float y = MMA.y();
        float z = MMA.z();

        // Map the accelerometer values to the LED brightness range (0.0 to 1.0)
        float redBrightness = map(fabs(x), 0.0, 1.0, 0.0, 1.0);
        float greenBrightness = map(fabs(y), 0.0, 1.0, 0.0, 1.0);
        float blueBrightness = map(fabs(z), 0.0, 1.0, 0.0, 1.0);

        // Set the LED brightness
        redLed.write(redBrightness);
        greenLed.write(greenBrightness);
        blueLed.write(blueBrightness);

        // Print the LED brightness values on the LCD
        lcd.cls();
        lcd.locate(0,0);
        lcd.printf("Red: %5.2f, Green: %5.2f, Blue: %5.2f", redBrightness, greenBrightness, blueBrightness);

        // Wait for 100ms before updating the values
        wait(0.1);
    }
}
