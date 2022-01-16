
#include <Servo.h>
Servo srv;              // servo object to control servo motor controlling the ultrasonic sensor

int Echo = A4;
int Trig = A5;

// robot speed
#define SPEED 150

// variable to store detected distance on motion directions
int right_distance = 0, left_distance = 0, frontal_distance = 0;



// The direction of the car's movement
// ENA  ENB   IN1   IN2   IN3   IN4     Description
// HIGH HIGH  HIGH  LOW   LOW   HIGH    Car is runing forward
// HIGH HIGH  LOW   HIGH  HIGH  LOW     Car is runing back
// HIGH HIGH  LOW   HIGH  LOW   HIGH    Car is turning left
// HIGH HIGH  HIGH  LOW   HIGH  LOW     Car is turning right
// HIGH HIGH  LOW   LOW   LOW   LOW     Car is stoped
// HIGH HIGH  HIGH  HIGH  HIGH  HIGH    Car is stopped
// LOW  LOW   N/A   N/A   N/A   N/A     Car is stopped (motors are disabled)

// CONNECTION BOARD - MAP MOTOR BOARD L298N TO ARDUINO IO PINs

#define ENA 5     // enable left-side motor and velocity control
#define ENB 6     // enable right-side motor and velocity control

// conrol of left-side motor BREAK = <(0,0), (1,1)>, FORWARD = (1,0), BACKWARD = (0,1)
#define IN1 7      
#define IN2 8

// control of right-side motor BREAK = <(0,0), (1,1), FORWARD = (0,1), BACKWARD = (1,0)
#define IN3 9
#define IN4 11


// function to move the robot forward at constant speed
void forward() {

  // enable motor with with specified speed
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  // move forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward at constant speed");
}

// function to move the robot backward at constant speed
void backward() {

  // enable motor with with specified speed
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  // move forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Backward at constant speed");
}

// function to turn the robot left at constant speed
void turn_left() {

  // enable motor with with specified speed
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  // move forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Turn left at constant speed");
  
}

// function to turn the robot right at constant speed
void turn_right() {

  // enable motor with with specified speed
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  // move forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Turn right at constant speed");
  
}

// function to stop the robot by turning off motors
void halt() {

  // disable the motors
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop the robot");
}


// function to check robot distance from any obstacle
int check_distance() {

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  //delayMicroseconds(20);
  delay(65);
  digitalWrite(Trig, LOW);
  float fdistance = pulseIn(Echo, HIGH);
  
  // compute distance in cm
  fdistance = fdistance / 58;
  return (int) fdistance;
}

// setup code
void setup() {

  // attache servo on pin 3 to Servo Object
  srv.attach(3);
  Serial.begin(9600);

  // enable pin mode
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  halt();
}


// main code
void loop() {

  srv.write(90);    // set servo position  according to scaled value (forward)
  delay(1000);

  // continuously get distance
  int distance = check_distance();
  // check distance from obstacles
  if (distance <= 20) {

    // stop robot
    halt();
    delay(1000);

    // check distance on the right side of the robot
    srv.write(5);
    delay(1000);
    right_distance = check_distance();
    delay(500);

    // check distance on the left side of the robot
    srv.write(180);
    delay(1000);
    left_distance = check_distance();
    delay(500);

    // turn the "head" front 
    srv.write(90);
    delay(1000);
    // check again frontal distance
    frontal_distance = check_distance();
    delay(500);

    // check possible motion directions
    if (frontal_distance > 20) {

      // go forward
      forward();
      
    } else if(right_distance > 20 && right_distance > left_distance) {

      // turn right
      turn_right();
      delay(360);
      
    }  else if (left_distance > 20 && left_distance > right_distance) {

      // turn left
      turn_left();
      delay(360);
      
    } else {

      // go backward and turn a bit
      backward(); 
      delay(1000);

      turn_right();
      delay(500);
    }

    
  } else {

    // go forward till possible
    forward();
  }
  
  
}
