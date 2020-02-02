#define motorInput1 6
#define motorInput2 9
#define motorInput3 10
#define motorInput4 11
#define CS 3 //1
#define RS 7 //2
#define LS 2 //3
#define RRS 4 //4
#define LLS 5 //5
#define led 13
int lv, cv, rv, llv, rrv;
int X = 2, Y = -1, XY = 0;
int cx = 0, cy = 0, p = 0, f = 0, t, k = 0,n=0;
int x = 2, y = -1; // initial coordinate
char s; //direction of flank
char q; // stores the current direction of travel
int sn, fn; //number of nodes to travel in sides and forward

int sensor[5] = {0, 0, 0, 0, 0};

int error1 = 1;
int error2 = 0;
int error3 = 1;
int error4 = 0;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode(motorInput1 , OUTPUT);
  pinMode(motorInput2 , OUTPUT);
  pinMode(motorInput3 , OUTPUT);
  pinMode(motorInput4 , OUTPUT);
  pinMode(led , INPUT);
  pinMode(LS , INPUT);
  pinMode(CS , INPUT);
  pinMode(RS , INPUT);
  pinMode(LLS , INPUT);
  pinMode(RRS , INPUT);
  digitalWrite(led, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
forward();  
read_sensor_values2();
if( error2==11)
{ 
        sharpLeftTurn() ;
    delay(2500);
    error2=0;
    stop_bot();
    delay(2000);
} 

}

int node_turning_count() //to count nodes while rotating at intersections
{
  if(p==1)
  {
    Serial.print(" uooooooooooooooooo" );
    delay(1000);
    p+=1;
  }
  read_sensor_values2();
  if ((sensor[3] == 1) && (sensor[4] == 1)) //reached the perpendicular node
  {
    p += 1;
  }
  return p;
}



// for FORWARD motion


void read_sensor_values1()
{ //read the values from the sensor
  lv = digitalRead(LS);
  rv = digitalRead(RS);
  cv = digitalRead(CS);
  sensor[0] = cv;
  sensor[1] = rv;
  sensor[2] = lv;
  Serial.print("the sensor values from 1 to 3 are:\t\t  ");
  Serial.print("s1:");
  Serial.print(sensor[0]);
  Serial.print("\t");
  Serial.print("s2:");
  Serial.print(sensor[1]);
  Serial.print("\t");
  Serial.print("s3:");
  Serial.print(sensor[2]);
  Serial.print("\t");

  if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0)) // forward
    error1 = 1;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0)) // turn right
    error1 = 2;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 1)) // turn left
    error1 = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1)) // slow forward
    error1 = 4;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0)) // turn right
    error1 = 5;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1)) // turn left
    error1 = 6;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0)) //
    error1 = 7;
  /*else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1)) //
      error = 8;*/
}

void read_sensor_values2()
{ //read the values from the sensor
  rrv = digitalRead(RRS);
  llv = digitalRead(LLS);
  sensor[3] = rrv;
  sensor[4] = llv;
  Serial.print("the sensor values from 4 to 5 are:\t\t  ");
  Serial.print("s4:");
  Serial.print(sensor[3]);
  Serial.print("\t");
  Serial.print("s5:");
  Serial.print(sensor[4]);
  Serial.print("\t");
  if ((sensor[3] == 1) && (sensor[4] == 1)) //  perfect node
  {
    cy += 1;
    error2 = 11;
  }
  /*  else if ((sensor[3] == 0) && (sensor[4] == 1))
      error = 22;
    else if ((sensor[3] == 0) && (sensor[4] == 0))
      error = 33;
    else if ((sensor[3] == 1) && (sensor[4] == 0))
      error = 44;*/
}

//for FLANK motion

void read_sensor_values3()
{ //read the values from the sensor
  lv = digitalRead(LS);
  rv = digitalRead(RS);
  cv = digitalRead(CS);
  sensor[0] = cv;
  sensor[1] = rv;
  sensor[2] = lv;
  Serial.print("the sensor values from 1 to 3 are:\t\t  ");
  Serial.print("s1:");
  Serial.print(sensor[0]);
  Serial.print("\t");
  Serial.print("s2:");
  Serial.print(sensor[1]);
  Serial.print("\t");
  Serial.print("s3:");
  Serial.print(sensor[2]);
  Serial.print("\t");

  if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0)) // forward
    error3 = 1;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0)) // turn right
    error3 = 2;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 1)) // turn left
    error3 = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1)) // slow forward
    error3 = 4;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0)) // turn right
    error3 = 5;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1)) // turn left
    error3 = 6;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0)) //
    error3 = 7;
  /*else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1)) //
      error = 8;
  */
}

void read_sensor_values4()
{ //read the values from the sensor
  rrv = digitalRead(RRS);
  llv = digitalRead(LLS);
  sensor[3] = rrv;
  sensor[4] = llv;
  Serial.print("the sensor values from 4 to 5 are:\t\t  ");
  Serial.print("s4:");
  Serial.print(sensor[3]);
  Serial.print("\t");
  Serial.print("s5:");
  Serial.print(sensor[4]);
  Serial.print("\t");
  if ((sensor[3] == 1) && (sensor[4] == 1)) //  perfect node
  {
    cx += 1;
    error4 = 11;
  }
  /*  else if ((sensor[3] == 0) && (sensor[4] == 1))
      error = 22;
    else if ((sensor[3] == 0) && (sensor[4] == 0))
      error = 33;
    else if ((sensor[3] == 1) && (sensor[4] == 0))
      error = 44;*/
}





void forward()  //move forward
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 158);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 158);
  analogWrite(motorInput4, 0);
  Serial.println("forward");
  q = 'f';
}
void forwardS()  //move forward SLOW
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 158);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 158);
  analogWrite(motorInput4, 0);
  Serial.println("forward");
  q = 'f';
}
void reverse() //move backward
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 0);
  analogWrite(motorInput2, 158);
  analogWrite(motorInput3, 0);
  analogWrite(motorInput4, 158);
  Serial.println("reverse");

}
void right() //move left with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 0);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 90);
  analogWrite(motorInput4, 0);
  Serial.println("right");
  q = 'r';
}
void left() //move right with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 90);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 0);
  analogWrite(motorInput4, 0);
  Serial.println("left");
  q = 'l';
}
void sharpRightTurn()  //move right with both the wheels moving in opposite direction with EQUAL SPEED
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, 0);
  digitalWrite(motorInput2, 1);
  digitalWrite(motorInput3, 1);
  digitalWrite(motorInput4, 0);
  Serial.println("right");
  q = 'r';
}
void sharpRightTurnT()  //move right with both the wheels moving in opposite direction with UNEQUAL SPEED
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 0);
  analogWrite(motorInput2, 90);
  analogWrite(motorInput3, 90);
  analogWrite(motorInput4, 0);
  Serial.println("right");
  q = 'r';
}
void sharpLeftTurn() //move left with both the wheels moving in opposite direction with EQUAL SPEED
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, 1);
  digitalWrite(motorInput2, 0);
  digitalWrite(motorInput3, 0);
  digitalWrite(motorInput4, 1);
  Serial.println("left");
  q = 'l';
}
void sharpLeftTurnT() //move left with both the wheels moving in opposite direction with UNEQUAL SPEEDS
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 90);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 0);
  analogWrite(motorInput4, 90);
  Serial.println("left");
  q = 'l';
}
void stop_bot() //motors stop running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, 0);
  digitalWrite(motorInput2, 0);
  digitalWrite(motorInput3, 0);
  digitalWrite(motorInput4, 0);
  Serial.println("stop");

}
