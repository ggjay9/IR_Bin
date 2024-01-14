#include <TimerFreeTone.h>     // TimerFreeTone library to create note without conflicts with servo library
#include <IRremote.h>          // IRremote library to receive codes from the remote control
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <Servo.h>             // Servo library to use the motor

// Pin definition
int trig_pin = 5;    
int echo_pin = 6;   
int servo_pin = 9;
int recv_pin = 11;
int alarm_pin = 12;
// Other variables 
Servo servo;         
IRrecv irrecv(recv_pin);
decode_results results;        
int distance, full;
int melody[] = {262, 196, 196, 220, 196, 0, 247, 262};
int dur[] = {250, 125, 125, 250, 250, 250, 250, 250};
long duration;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);  
  pinMode(echo_pin, INPUT);  
  servo.attach(servo_pin);        // Defines the pin with which you can communicate with the motor
  irrecv.enableIRIn();            // Start the receiver
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
     Serial.println(results.value, HEX);    // Here you can see the code association in hexadecimal
     irrecv.resume();                       // Receive the next value

     if (results.value == 0xFF30CF) {       // Push 1 to open the bin, the code association could change between different remote control
        servo.attach(servo_pin);
        delay(1);
        servo.write(150);                   // The motor turns 150° so the bin is open
        full = 1;                           // The ultrasonic sensor can check if the bin is full
        Serial.print("Servo 150° -> "); Serial.println(full);
        delay(1000);
     }
     if (results.value == 0xFF6897) {        // Push 0 to close the bin, the code association could change between different remote control
        servo.write(0);                      // The motor turns 0° so the bin is closed
        Serial.println("Servo 0°");
        delay(1000);
        servo.detach();
     }
  }
  delay(100);
  
  if (full == 1) {
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    duration = pulseIn(echo_pin, HIGH);                      // Measures the time (µs) between the transmitted wave and the reflected one
    distance = duration*0.034/2;                             // v=s*2t  speed of sound 0.034 cm/µs, the time is double because
                                                             // the wave goes back and forth
    Serial.print("The bin isn't full, distance: "); Serial.print(distance); Serial.println(" cm"); 
    if(distance < 3) {                                       // If the distance between the back of the bin and the trash is less than 3 cm
                                                             // the alarm will start
      Serial.print("The bin is full, distance: "); Serial.print(distance); Serial.println(" cm"); 
      for (int i=0; i<8; i++) { 
          TimerFreeTone(alarm_pin, melody[i], dur[i]);       // Play melody[i] note for duration[i] time
          delay(50);                                         // Short delay between notes.
      } 
    }
    full = 0;                                                // The bin isn't full
  }
}