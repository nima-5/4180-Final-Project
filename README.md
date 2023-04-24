# 4180-Final-Project
This Project holds the code related to the 4180 Final group Project of

Sean Nima (B)

Corey Meyer (B)

Garrett Gularson (B)

Tony Popa (A)

# RC Car 
In this project, you will learn how to make a RC robot using an Mbed microcontroller and a few other parts. This will be fully controllable by your phone!
 

## Parts Required
1. 1x MBED LPC 1768
2. 1x RS232 Bluetooth Serial Adapter
3. 4x Motors
4. 2x HBridge Motor Drivers
5. 1x LED Diode
6. 1x TOF Distance Sensor
7. 2x 9V Barrel Jack Adapters
8. 2x 9V Barrel Battery Packs



## Building the Robot
Once you have accumulated all of the parts above you can begin to build the project together.

1. Setting up the Mbed. In the end, the MBED should look a lot like the block diagram below.

| Pin | Connection |
| :-----: | :--------: |
| VIN | 5V (Barrel Jack 2) |
| GND | GND (Common) |

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/Screenshot%202023-04-24%20at%207.06.54%20PM.png)


2. Setting Up H-bridge 1.  This list follows the pinouts on the H-bridge board from top left side down, then top right of the board down. (Note: Use the image reference to determine which is motor is which)

The H-Bridge motor driver is an essential part to the RC car. This is the device that will communicate with the motors and tell them what needs to be down (whether to rotate clockwise or counter-clockwise). We use 2 of these to control all four motor. Something to note about this device is although the board can be powered using the 3.3 V from the Mbed Vout pin, the power required to spin the motors are a lot higher, so we will use external power sources to power the motors.

| Pin | Connection |
| :-----: | :--------: |
| VM  | 5V (Barrel Jack 1) |
| VCC | VOUT (Mbed) | 
| GND | GND (Common) |
| A01 | + (Motor 1) |
| A02 | - (Motor 1) |
| B01 | + (Motor 2) | 
| B02 | - (Motor 2) |
| GND | GND (Common) |
| PWMA | p24 (Mbed) |
| AI2 | p5 (Mbed) |
| AI1 | p6 (Mbed) |
| STBY | Vout (Mbed) |
| Bl1 | p7 (Mbed) |
| Bl2 | p8 (Mbed) | 
| PWMB | p23 (Mbed) |
| GND | GND (Common) |

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/Screenshot%202023-04-24%20at%207.07.02%20PM.png)

3. Setting Up H-bridge 2 (Refer to notes from H-bridge 1)

| Pin | Connection |
| :-----: | :--------: |
| VM  | 5V (Barrel Jack 1) |
| VCC | VOUT (Mbed) | 
| GND | GND (Common) |
| A01 | + (Motor 3) |
| A02 | - (Motor 3) |
| B01 | + (Motor 4) | 
| B02 | - (Motor 4) |
| GND | GND (Common) |
| PWMA | p22 (Mbed) |
| AI2 | p12 (Mbed) |
| AI1 | p13 (Mbed) |
| STBY | Vout (Mbed) |
| Bl1 | p14 (Mbed) |
| Bl2 | p15 (Mbed) | 
| PWMB | p21 (Mbed) |
| GND | GND (Common) |

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/Screenshot%202023-04-24%20at%207.07.10%20PM.png)


4. Wiring the RS232 Bluetooth Serial Adapter

Now we will move on to setting up the Bluetooth Serial Adapter with the Mbed. This serial adapter will allow us to communicate with motors through the Adafruit Bluetooth BLE App. If you have not yet installed this, please install the App. Note: The RS232 bluetooth adapter we use requires a 5V Power Supply, so remember to use a power supply from the barrel jack when wiring the board up.

| Pin | Connection |
| :-----: | :--------: |
| MOD | NC | 
| CTS | GND | 
| TXO | p10 (Mbed) |
| RXI | p9 (Mbed) |
| Vin | 5V (Barrel Jack 1) |
| RTS | NC |
| GND | GND (Common) |
| OFU | NC | 

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/Screenshot%202023-04-24%20at%207.06.58%20PM.png)


5. Wiring the ToF sensor

This next part, we will be setting up the ToF (Time of Flight) distance sensor. The ToF sensor uses lidar technology to determine how far something is from the sensor.  This sensor is required to ensure that the robot does not run into any walls. When the robot detects that the robot is within X meters of a wall, the robot will be set to reverse for a little bit of distance.



| Pin | Connection |
| :-----: | :--------: |
| VIN | Vout (Mbed) | 
| Gnd | Gnd (Common) |
| SCL | p27 (Mbed) | 
| SDA | p28 (Mbed) | 
| GPIO | NC |
| XSHUT | p20 (Mbed) | 

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/Screenshot%202023-04-24%20at%207.07.06%20PM.png)

6. Wiring the LED Diode

LED Diode that is added on to have a visible light notification for the driver. Allows easy sense of sight to the robot in the dark.
Note: Do not forget to wire the Anode section of the LED through a 330 ohm resistor.

| Pin | Connection |
| :-----: | :--------: |
| Anode | p26 (Mbed) |
| Cathode | GND | 

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/Screenshot%202023-04-24%20at%207.13.20%20PM.png)

## Uploading files to the mbed

At this point, you have everything wired up. All that's left for setup is building and compiling the code onto the online compiler.

In Keil studio, paste in all the files from the src folder in this github to an Mbed OS 2 project. Afterwards, compile the code and save the file to your Mbed while it is plugged in. Voila! You're ready to use your robot!


## Connecting and Controlling the Robot

In this section you will learn how to connect and control the robot. As mentioned in step 4 previously, please be sure to download the Adafruit Bluetooth App as that will be how we control the RC car that we have created.

1. Connect to you're RS 232 using the Adafruit bluetooth connect app

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/IMG_2440.jpg)

2. Once you're connected go to controller and then open control pad

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/IMG_2439.jpg)

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/IMG_2438.jpg)

3. Control the RC car as you see fit using the buttons below!

![alt text](https://github.com/nima-5/4180-Final-Project/blob/main/Images/IMG_2437.jpg)







