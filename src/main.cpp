#include "Mutex.h"
#include "Thread.h"
#include "mbed.h"
// #include "mbed2/313/drivers/PwmOut.h"
#include "rtos.h"
#include "SDFileSystem.h"
#include "wave_player.h"
#include "uLCD_4DGL.h"
#include "Motor/Motor.h"
#include "XNucleo53L0A1.h"
#include "Servo.h"

#define MAX_DISTANCE 90
#define MIN_DISTANCE 30
#define VL53L0_I2C_SDA   p28
#define VL53L0_I2C_SCL   p27
DigitalOut shdn(p20);
PwmOut servo(p26);



static XNucleo53L0A1 *board=NULL;


#define MAX_SPEED 1

Serial  blue(p9,p10);
BusOut myled(LED1,LED2,LED3,LED4);
volatile int driveable = 1;

Serial pc(USBTX, USBRX);

Motor frontLeft(p24, p5,p6);
Motor frontRight(p23, p7, p8);
Motor backRight(p22, p12, p13);
Motor backLeft(p21, p14, p15);

void driveStop()
{
    frontLeft.speed(0);
    frontRight.speed(0);
    backLeft.speed(0);
    backRight.speed(0);
}

void driveForward()
{
    frontLeft.speed(MAX_SPEED);
    frontRight.speed(MAX_SPEED);
    backLeft.speed(-MAX_SPEED);
    backRight.speed(-MAX_SPEED);
}

void driveBackward()
{
    frontLeft.speed(-MAX_SPEED);
    frontRight.speed(-MAX_SPEED);
    backLeft.speed(MAX_SPEED);
    backRight.speed(MAX_SPEED);
}

void driveLeft()
{
    frontLeft.speed(MAX_SPEED);
    frontRight.speed(-MAX_SPEED);
    backLeft.speed(MAX_SPEED);
    backRight.speed(-MAX_SPEED);
}

void driveRight()
{
    frontLeft.speed(-MAX_SPEED);
    frontRight.speed(MAX_SPEED);
    backLeft.speed(-MAX_SPEED);
    backRight.speed(MAX_SPEED);
}
void driveCar(void const *args)
{
    char bnum;
    char bhit;
    float servoPos = 0.5;
    servo = servoPos;

    while(1)
    {
        Thread::wait(50);
        if (!driveable)
        {
            if (blue.readable() && blue.getc()=='!') 
            {
                if (blue.readable() && blue.getc()=='B') 
                { //button data packet
                    bnum = blue.getc(); //button number
                    bhit = blue.getc(); //1=hit, 0=release
                    if (blue.readable() && blue.getc()==char(~('!' + 'B' + bnum + bhit))) 
                    { //checksum OK?
                        switch (bnum) 
                        {
                            case '6': //button 6 down arrow Move Backwards
                                if (bhit=='1') {
                                    //add hit code here
                                    driveBackward();
                                    pc.printf("Not driveable Backward\n\r");
                                } else {
                                    //add release code here
                                    driveStop();
                                    myled = 0;
                                }
                                break;
                                case '1': //number button 1
                            if (bhit=='1') {
                                //add hit code here
                                if (servoPos < 1)
                                {
                                    servoPos += 0.1;
                                    servo = servoPos;
                                }
                                pc.printf("increase Servo %f\n\r", servoPos);

                            } else {
                                //add release code here
                            }
                            break;
                        case '2': //number button 2
                            if (bhit=='1') {
                                //add hit code here
                                if (servoPos >= 0.1)
                                {
                                    servoPos -= 0.1;
                                    servo = servoPos;
                                }
                                pc.printf("decrease servo %f\n\r", servoPos);
                            } else {
                                //add release code here
                            }
                            break;
                            default:
                            driveStop();
                        }
                    }
                }
            }
            myled = 15;
            continue;
        } else
        {
            myled = 0;
        }
        // pc.printf("try read\n");
        if (blue.readable() && blue.getc()=='!') {
                bnum = blue.getc();
            if (bnum =='B') { //button data packet
                bnum = blue.getc(); //button number
                bhit = blue.getc(); //1=hit, 0=release
                if (blue.getc()==char(~('!' + 'B' + bnum + bhit))) { //checksum OK?
                    myled = bnum - '0'; //current button number will appear on LEDs
                    switch (bnum) {
                        case '1': //number button 1
                            if (bhit=='1') {
                                //add hit code here
                                if (servoPos < 1)
                                {
                                    servoPos += 0.1;
                                    servo = servoPos;
                                }
                                pc.printf("increase Servo %f\n\r", servoPos);
                            } else {
                                //add release code here
                            }
                            break;
                        case '2': //number button 2
                            if (bhit=='1') {
                                //add hit code here
                                if (servoPos > 0)
                                {
                                    servoPos -= 0.1;
                                    servo = servoPos;
                                }
                                pc.printf("decrease servo %f\n\r", servoPos);
                            } else {
                                //add release code here
                            }
                            break;
                        // case '3': //number button 3
                        //     if (bhit=='1') {
                        //         //add hit code here
                        //     } else {
                        //         //add release code here
                        //     }
                        //     break;
                        // case '4': //number button 4
                        //     if (bhit=='1') {
                        //         //add hit code here
                        //     } else {
                        //         //add release code here
                        //     }
                        //     break;
                        case '5': //button 5 up arrow Move Forward
                            if (bhit=='1') {
                                //add hit code here
                                pc.printf("forward\n\r");
                                driveForward();
                                
                            } else {
                                //add release code here
                                driveStop();
                                myled = 0;
                            }
                            break;
                        case '6': //button 6 down arrow Move Backwards
                            if (bhit=='1') {
                                //add hit code here
                                pc.printf("backward\n\r");
                                driveBackward();
                            } else {
                                //add release code here
                                driveStop();
                                myled = 0;
                            }
                            break;
                        case '7': //button 7 left arrow Move Left
                            if (bhit=='1') {
                                //add hit code here
                                pc.printf("left\n\r");
                                driveLeft();
                            } else {
                                //add release code here
                                driveStop();
                                myled = 0;
                            }
                            break;
                        case '8': //button 8 right arrow
                            if (bhit=='1') {
                                //add hit code here
                                pc.printf("right\n\r");
                                driveRight();
                            } else {
                                //add release code here
                                driveStop();
                                myled = 0;
                            }
                            break;
                        default:
                        Thread::wait(50);
                    }
                }
            }
        }
    }
}

int main()
{
    servo = 0.5;
    int status;
    uint32_t distance;
    DevI2C *device_i2c = new DevI2C(VL53L0_I2C_SDA, VL53L0_I2C_SCL);
    /* creates the 53L0A1 expansion board singleton obj */
    board = XNucleo53L0A1::instance(device_i2c, A2, D8, D2);
    shdn = 0; //must reset sensor for an mbed reset to work
    wait(0.1);
    shdn = 1;
    wait(0.1);
    /* init the 53L0A1 board with default values */
    status = board->init_board();
    while (status) {
        pc.printf("Failed to init board! \r\n");
        status = board->init_board();
    }
    pc.printf("hey");
    Thread thread(driveCar);

    //loop taking and printing distance
    while (1) {
        status = board->sensor_centre->get_distance(&distance);
        if (status == VL53L0X_ERROR_NONE) {
            pc.printf("D=%ld mm\r\n", distance);
            if (distance < MAX_DISTANCE && distance > MIN_DISTANCE)
        {
            driveable = 0;
        } else
        {
            driveable = 1;
        }
        }
        Thread::wait(500);
        // Thread::yield();
    }
    // Thread thread(multicolorBeacon); //Start LED effect thread

}

