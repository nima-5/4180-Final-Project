# 4180-Final-Project
This Project holds the code related to the 4180 Final group Project of
Sean Nima (B)
Corey Meyer (B)
Garrett Gularson (B)
Tony Popa (A)

# Twisted-Tea Robot
In this project, you will learn how to make a twisted tea RC robot. The aesthetic for this robot is completely up to you, but in our case we will be using twiswted tea as our box design
 

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

1. Setting up the Mbed.

| Pin | Connection |
| :-----: | :--------: |
| VIN | 5V (Barrel Jack 2) |
| GND | GND (Common) |


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

6. Wiring the LED Diode
LED Diode that is added on to have a visible light notification for the driver. Allows easy sense of sight to the robot in the dark.
Note: Do not forget to wire the Anode section of the LED through a 330 ohm resistor.

| Pin | Connection |
| :-----: | :--------: |
| Anode | p26 (Mbed) |
| Cathode | GND | 










