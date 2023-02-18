/********************************/
/*Exploration 2 - Line Following*/
/*     OSU FEH Spring 2023      */
/*        Jacob Capaldi         */
/*    02/17/23  Version 3.0.1   */
/********************************/

/* Include preprocessor directives */
#include <FEHLCD.h>
#include <stdio.h>
#include <FEHUtility.h>
#include <FEHIO.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHRPS.h>

// declare motors
FEHMotor leftMotor(FEHMotor::Motor0,9.0);
FEHMotor rightMotor(FEHMotor::Motor1,9.0);


// declare 3 sensors
AnalogInputPin leftLineF(FEHIO::P2_2);
AnalogInputPin centerLineF(FEHIO::P2_1);
AnalogInputPin rightLineF(FEHIO::P2_0);


int main(void)
{
    // Collect values to display
    float x, y, z;
    char s[30];


    while(!LCD.Touch(&x, &y));
    while(LCD.Touch(&x, &y));


    while (true){
        // Variables that display values for analogue inputs
        x=leftLineF.Value();
        y=centerLineF.Value();
        z=rightLineF.Value();


        // Print these values
        sprintf(s, "%f %f %f", x,y,z);
        LCD.WriteLine(s);


        // Line following algorithm
        // Determine case
        if (x>1 && y<1.3 && z<1.2)
        {
            // Need to go left
            leftMotor.SetPercent(0);
            rightMotor.SetPercent(30);
            Sleep(0.5);
            leftMotor.SetPercent(30);
            rightMotor.SetPercent(30);


        }
        else if (x<1 && y<1.3 && z>2)
        {
            // Need to go Right
            leftMotor.SetPercent(30);
            rightMotor.SetPercent(0);
            Sleep(0.5);
            leftMotor.SetPercent(30);
            rightMotor.SetPercent(30);
        }
        else
        {
            // Need to continue straight
            leftMotor.SetPercent(30);
            rightMotor.SetPercent(30);
        }
    }
}
