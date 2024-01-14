# IR_Bin
Smart Waste Bin Project: An Arduino-based smart bin with remote lid control, ultrasonic fill level monitoring, and fullness alerts via a buzzer. Code and schematics included for easy replication.

Creating a smart waste bin with features like automatic lid control using a remote control and an infrared sensor. It also includes an ultrasonic sensor to monitor the bin's fill level and a buzzer for notifications when the bin is full. Here's a summary:

Main Components:
1. Arduino Uno: The control board.
2. KY-022 Infrared Module: For remote control and servo motor.
3. SG90 Servo Motor: Controls the lid.
4. HC-SR04 Ultrasonic Sensor: Measures fill level.
5. Buzzer: Provides notifications.

Arduino Code:
The code uses three libraries for various functions. In setup, pins and variables are initialized. The ultrasonic sensor checks fill levels, and the servo motor is controlled by infrared signals. If the bin opens and is full, the buzzer alerts the user.
