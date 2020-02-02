// IR Sensors for 300 rpm motor
int sensor1 = 2;      // Left most sensor
int sensor2 = 3;
int sensor3 = 4;
int sensor4 = 5;      // Right most sensor

// Initial Values of Sensors
int sensor[4] = {0, 0, 0, 0};

// Motor Variables
int ENA = 6;
int motorInput1 = 7;
int motorInput2 = 8;
int motorInput3 = 9;
int motorInput4 = 10;
int ENB = 11;

//Initial Speed of Motor
int initial_motor_speed = 140;

// Output Pins for Led
int ledPin1 = A3;
int ledPin2 = A4;

// PID Constants
float Kp = 25;
float Ki = 0;
float Kd = 15;

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int flag = 0;

int c=0;//node counter
int cx=0;//total nodes in left adn totoal nodes in right
int cy=0;
int X,Y,XY; //target coordinate
int x=2,y=-1; // initial coordinate

int sn,fn; //number of nodes to travel in sides and forward
char s;



void setup()
{

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);

  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);

  Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
  delay(500);
  
  Serial.print("enter X and Y coordinates: ");
  while(Serial.available()== 0){}
  XY=Serial.parseInt();
  X=XY/10;
  Y=XY%10;
  Serial.print("X :  ");
  Serial.print(X);
  Serial.print("\t");
  Serial.print("Y :  ");
  Serial.println(Y);
  delay(2000);
  fn=Y-y;
  sn=X-x;
  Serial.print("number of nodes to travel in FORWARD direction :  ");
  Serial.print(fn);
  Serial.print("\t");
  Serial.print("number of nodes to travel in FLANK direction(- indicates LEFT and + indicates RIGHT) :  ");
  Serial.println(sn);
  delay(2000);
  Serial.println("FOLLOWING begins!!");
  delay(1000);
  
   if (sn>0)  //to decide on the side
    s='R';
  else if (sn<0)
    {
      s='L';
      sn=abs(sn);
    }
  else
    s='N'; 
}

void loop()
{
  read_sensor_values(); // takes in sensor values and calculates error
  Serial.print("errorvalue: ");
  Serial.print(error);  
  
 
  if (error == 100) {               // Make left turn untill it detects straight path
    Serial.print("\t");
    Serial.println("Left");
    do {
      read_sensor_values(); // takes in sensor values and calculates error
      analogWrite(ENA, 110); //Left Motor Speed
      analogWrite(ENB, 90); //Right Motor Speed
      sharpLeftTurn();
    } while (error != 0);
  }
  
  else if (error == 101) {          // Make right turn in case of it detects only right path (it will go into forward direction in case of staright and right "|--")
                                      // untill it detects straight path.
    //Serial.print("\t");
    //Serial.println("Right");
    analogWrite(ENA, 110); //Left Motor Speed
    analogWrite(ENB, 90); //Right Motor Speed
    forward();
    delay(200);
    stop_bot();
    read_sensor_values(); // takes in sensor values and calculates error
    if (error == 102) {
      do {
        analogWrite(ENA, 110); //Left Motor Speed
        analogWrite(ENB, 90); //Right Motor Speed
        sharpRightTurn();
        read_sensor_values(); // takes in sensor values and calculates error
      } while (error != 0);
    }
  } else if (error == 102) {        // Make left turn untill it detects straight path
    //Serial.print("\t");
    //Serial.println("Sharp Left Turn");
    do {
      analogWrite(ENA, 110); //Left Motor Speed
      analogWrite(ENB, 90); //Right Motor Speed
      sharpLeftTurn();
      read_sensor_values(); // takes in sensor values and calculates error
      if (error == 0) { 
        stop_bot();
        delay(200);
      }
    } while (error != 0);
  } else if (error == 103) {        // Make left turn untill it detects straight path or stop if dead end reached.
    if (flag == 0) {
      analogWrite(ENA, 110); //Left Motor Speed
      analogWrite(ENB, 90); //Right Motor Speed
      forward();
      delay(200);
      stop_bot();
      read_sensor_values(); // takes in sensor values and calculates error
      if (error == 103) {     /**** Dead End Reached, Stop! ****/
       stop_bot();
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        flag = 1;
      } else {        /**** Move Left ****/
       analogWrite(ENA, 110); //Left Motor Speed
        analogWrite(ENB, 90); //Right Motor Speed
        sharpLeftTurn();
        delay(200);
        do {
          //Serial.print("\t");
          //Serial.println("Left Here");
          read_sensor_values(); // takes in sensor values and calculates error
          analogWrite(ENA, 110); //Left Motor Speed
          analogWrite(ENB, 90); //Right Motor Speed
          sharpLeftTurn();
        } while (error != 0);
      }
    }
  } else {
    calculate_pid();
    motor_control();
  }
}







void read_sensor_values() // takes in sensor values and calculates error
{
  sensor[0] = !digitalRead(sensor1);
  sensor[1] = !digitalRead(sensor2);
  sensor[2] = !digitalRead(sensor3);
  sensor[3] = !digitalRead(sensor4);
  
    Serial.print("the sensor values from 1 to 4 are: ");
    Serial.print("\t");
    Serial.print("s1:");
    Serial.print(sensor[0]);
    Serial.print("\t");
    Serial.print("s2:");
    Serial.print(sensor[1]);
    Serial.print("\t");
    Serial.print("s3:");
    Serial.print(sensor[2]);
    Serial.print("\t");
    Serial.print("s4:");
    Serial.println(sensor[3]);

  if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0))
    error = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0))
    error = 2;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0))
    error = 1;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0))
    error = 0;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0))
    error = -1;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1))
    error = -2;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1))
    error = -3;

    
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0)) // Turn robot left side till the code is 0110
    error = 100;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)) // Turn robot right side till the code is 0110
    error = 101;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0)) // come reverse till the code is 1111
    error = 102;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)) // node count
    {
      c+=1;
      error = 103;
    }


void calculate_pid()
{
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control()
{
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed - PID_value;
  int right_motor_speed = initial_motor_speed + PID_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

  /*Serial.print(PID_value);
    Serial.print("\t");
    Serial.print(left_motor_speed);
    Serial.print("\t");
    Serial.println(right_motor_speed);*/

  analogWrite(ENA, left_motor_speed); //Left Motor Speed
  analogWrite(ENB, right_motor_speed - 30); //Right Motor Speed

  //following lines of code are to make the bot move forward
  forward();
}






void forward()  //move forward
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}
void reverse() //move backward
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}
void right() //move left with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}
void left() //move right with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}
void sharpRightTurn()  //move right with both the wheels moving in opposite direction
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}
void sharpLeftTurn() //move left with both the wheels moving in opposite direction
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}
void stop_bot() //motors stop running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}
