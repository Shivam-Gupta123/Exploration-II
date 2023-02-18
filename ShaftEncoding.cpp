/********************************/
/*Exploration 2 - Shaft Encoding*/
/*     OSU FEH Spring 2023      */
/*        Zachary Smith         */
/*    02/17/23  Version 3.0.1   */
/********************************/

/* Include preprocessor directives */
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>


// Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);


// moves forward and stops by reading the counts on the left and right encoders
void move_forward(int percent, int counts) 
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();


    // Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent-3);


    // While the average of the left and right encoder is less than counts,
    // keep running motors
    while(((left_encoder.Counts() + right_encoder.Counts()) / 2) < counts);


    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}


// right turn function using the left and right encoders
void turn_right(int percent, int counts)
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();


    // Set both motors to desired percent
    // hint: set right motor backwards, left motor forwards
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);


    // While the average of the left and right encoder is less than counts,
    // keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);


    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}


// Left turn function using left and right encoders
void turn_left(int percent, int counts) 
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();


    // Set both motors to desired percent
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent);


    // While the average of the left and right encoder is less than counts,
    // keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);


    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}


int main(void)
{
    int motor_percent = 40; // Input power level here
    int expected_counts = 567; // Input theoretical counts here


    float x, y; // for touch screen


    // Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);


    LCD.WriteLine("Shaft Encoder Exploration Test");
    LCD.WriteLine("Touch the screen");
    while(!LCD.Touch(&x,&y)); // Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); // Wait for screen to be unpressed


    // drive 14"
    move_forward(motor_percent, expected_counts); // see function
    Sleep(2.0); // Wait for counts to stabilize


    // turn left 90 deg.
    int turn_percent = 40;
    int turn_count = 220;
    turn_left(turn_percent,turn_count);
    Sleep(2.0);


    // drive 10"
    expected_counts = 405;
    move_forward(motor_percent, expected_counts);
    Sleep(2.0);


    // turn right 90
    turn_right(turn_percent,turn_count);
    Sleep(2.0);


    // drive 4"
    expected_counts = 162;
    move_forward(motor_percent, expected_counts);
    Sleep(2.0);

}
