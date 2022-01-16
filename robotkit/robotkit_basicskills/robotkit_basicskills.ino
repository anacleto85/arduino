
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


// function starting right wheel moving forward
void start_right_wheel_forward() {

  digitalWrite(ENB, HIGH);  // enable right motor
  
  // start moving right wheel farward (0,1)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Start moving right wheel forward");
}

// function starting left wheel moving forward
void start_left_wheel_forward() {

  digitalWrite(ENA, HIGH);  // enable left motor

  // start moving left wheel forward (1,0)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  Serial.println("Start moving left wheel forward");
}

// function starting left wheel moving backward
void start_left_wheel_backward() {

  digitalWrite(ENA, HIGH);  // enable left motor

  // start moving left wheel backward (0,1)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  Serial.println("Start moving left wheel backward");
}

// function starting right wheel moving backward
void start_right_wheel_backward() {

  digitalWrite(ENB, HIGH);  // enable right motor

  // start moving right wheel backward (1,0)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Start moving right wheel backward");
}

// function stopping right wheel moving
void stop_right_wheel() {

  digitalWrite(ENB, HIGH);  // enable right motor

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Stop moving right wheel");
}

// function stopping left wheel moving
void stop_left_wheel() {

  digitalWrite(ENA, HIGH);  // enable left motor

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.println("Stop moving left wheel");
}

// test contrl of right wheel
void test_right_wheel() {

  // start moving right wheel forward
  start_right_wheel_forward();
  // wait a bit (1 second)
  delay(1000);

  // sto moving 
  stop_right_wheel();
  // wait a bit (0.5 seconds)
  delay(500);

  // start moving right wheel backward
  start_right_wheel_backward();
  delay(1000);
  
  // stop moving
  stop_right_wheel();
  delay(500);
}

// test contrl of left wheel
void test_left_wheel() {


  // start moving rleft wheel forward
  start_left_wheel_forward();
  // wait a bit (1 second)
  delay(1000);

  // sto moving 
  stop_left_wheel();
  // wait a bit (0.5 seconds)
  delay(500);

  // start moving left wheel backward
  start_left_wheel_backward();
  delay(1000);
  
  // stop moving
  stop_left_wheel();
  delay(500);
}


// function starting moving the robot forward
void go_forward() {

  start_left_wheel_forward();
  start_right_wheel_forward();
  Serial.println("Start moving forward");
}

// function starting moving the robot backward
void go_backward() {

  start_left_wheel_backward();
  start_right_wheel_backward();
  Serial.println("Start moving backward");
}

// function turning the robot left
void turn_left() {

  start_left_wheel_backward();
  start_right_wheel_forward();
  Serial.println("Start turning left");
}

// function turning the robot right
void turn_right() {

  start_left_wheel_forward();
  start_right_wheel_backward();
  Serial.println("Start turning right");
}

// function stopping wheel from moving
void halt() {

  stop_left_wheel();
  stop_right_wheel();
  Serial.println("Stop moving wheels");
}


// function for increasing robot speed to the max
void increase_speed() {

  Serial.println("Accelerate speed");
  for (int i = 0; i <= 255; i++) {

    analogWrite(ENA, i);
    analogWrite(ENB, i);
    delay(20);
  }
  
}

// function for decreasing robot speed to stop
void decrease_speed() {

  Serial.println("Decrease speed");
  for (int i = 255; i >= 0; i--) {

    analogWrite(ENA, i);
    analogWrite(ENB, i);
    delay(20);    
  }
  
}

// setup code goes here
void setup() {
  
  // set IO pin mode for right wheel
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // set IO pin mode for left wheel
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  
}

// main loop
void loop() {

  go_forward();

  decrease_speed();

  delay(1000);

  go_backward();

  increase_speed();

  delay(1000);

  halt();

  delay(500);


  turn_left();

  delay(1000);

  turn_right();

  delay(1000);


  halt();


  delay(500);

}
