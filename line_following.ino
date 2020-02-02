
.//line following program

// sensor arrangement     4     5 node detection
//                         2   3 flank detection
//                           1 center line detection
#define motorInput1 6
#define motorInput2 9
#define motorInput3 10
#define motorInput4 11
#define CS 3 //1
#define RS 7 //2
#define LS 2 //3
#define RRS 4 //4
#define LLS 5 //5
#define led 12
int lv, cv, rv, llv, rrv;
int X = 2, Y = -1, XY = 0;
int cx = 0, cy = 0, p = 0, f = 0, t=0., k = 0,n=0,r=0,z=0,m=0;
int x = 2, y = -1; // initial coordinate
char s; //direction of flank
char q; // stores the current direction of travel
int sn, fn; //number of nodes to travel in sides and forward
char i;
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
  pinMode(led , OUTPUT);
  pinMode(LS , INPUT);
  pinMode(CS , INPUT);
  pinMode(RS , INPUT);
  pinMode(LLS , INPUT);
  pinMode(RRS , INPUT);
  digitalWrite(led, LOW);

//to calculate the coordinates
  //if(Serial.available()>0)
  //XY=Serial.parseInt();
  //Serial.print(XY);
  Serial.print("enter X and Y coordinates: ");
 

  while (Serial.available() == 0) {}
  XY = Serial.parseInt();
  X = XY / 10;
  Y = XY % 10;
  Serial.print("X :  ");
  Serial.print(X);
  Serial.print("\t");
  Serial.print("Y :  ");
  Serial.println(Y);
  delay(2000);
  fn = Y - y;
  sn = X - x;
  Serial.print("number of nodes to travel in FORWARD direction :  ");
  Serial.print(fn);
  Serial.print("\t");
  Serial.print("number of nodes to travel in FLANK direction(- indicates LEFT and + indicates RIGHT) :  ");
  Serial.println(sn);
  delay(2000);
  Serial.println("FOLLOWING begins!!");
  delay(1000);

  //to store the direction of flank travel in a variable
  if (sn > 0)
    s = 'R';
  else if (sn < 0)
  {
    s = 'L';
    sn = abs(sn);
  }
  else
    s = 'N';



}

void read_sensor_values1();
void read_sensor_values2();
void read_sensor_values3();
void read_sensor_values4();
void forward();
void forwardS();
void stop_bot();
void sharpRightTurnT();
void sharpLeftTurnT();
void sharpRightTurn();
void sharpLeftTurn();
void right();
void left();
void loop() {

  //calculate error value
  //forward motion
  if (cy != fn && n==0)
  {
    read_sensor_values1();
    read_sensor_values2();
    /*Serial.print("\t");
    Serial.print("errorvalue1: ");
    Serial.println(error1);
    Serial.print("\t");
    Serial.print("errorvalue2: ");
    Serial.println(error2);
    Serial.print("\t");*/
    Serial.print("  Y-counter: ");
    Serial.print(cy);
  }

  //flank motion
  else if (cx != sn )
  {
    read_sensor_values3();
    read_sensor_values4();
   /* Serial.print("\t");
    Serial.print("errorvalue3: ");
    Serial.println(error3);
    Serial.print("\t");
    Serial.print("errorvalue4: ");
    Serial.println(error4);
    Serial.print("\t");*/
    Serial.print(" X-counter: ");
    Serial.print(cx);
  }

 if (cy != fn) // to move in Y direction untill it reaches the Y target node
  {
    if (error1 == 1 && error2 != 11)
      forward();
    else if (error1 == 2 && error2 != 11)
    {
      //speed control
      sharpRightTurnT();
    }
    else if (error1 == 3 && error2 != 11)
    {
      //speed control
      sharpLeftTurnT();
    }
    else if (error1 == 4 && error2 != 11)
    {
      //speed reduction
      forwardS();
    }
    else if (error1 == 5 && error2 != 11)
    { //speed reduction
      right() ;
    }
    else if (error1 == 6 && error2 != 11)
    { //speed reduction
      left();
    }
    else if (error1 == 7 && error2 != 11)
    {
    //  if (q == 'f')
      //  reverse();
      if (q == 'r' || q== 'f')
        left();
      else if (q == 'l' || q== 'f')
        right();
      
    }


    if (error2 == 11)
    { error2 = 0;
      read_sensor_values1();
      if (error1 == 1)
        forward();
      else if (error1 == 2)
      {
        //speed control
        sharpRightTurnT();
      }
      else if (error1 == 3)
      {
        //speed control
        sharpLeftTurnT();
      }
      else if (error1 == 4)
      {
        //speed reduction
        forward();
      }
      else if (error1 == 5)
      {
        //speed reduction
        right() ;
      }
      else if (error1 == 6)
      {
        //speed reduction
        left();
      }
      else if (error1 == 7)
      { //speed reduction
       // if (q == 'f')
         //  reverse();
        if (q == 'r' || q== 'f')
          left();
        else if (q == 'l' || q== 'f')
          right();
      }

      delay(800);// to wait for the bots to cross the node
    }

  }


  if (cy == fn && cx != sn && f == 0) // to turn the bot at 90 degree at Y target node to follow the X target node
  {
    if (s == 'R')
    {
      
        sharpRightTurn() ;
        delay(800);
    }

    if (s == 'L')
    {
      
        sharpLeftTurn() ;
        delay(800);
      
    }
   read_sensor_values1();
      if (error1 == 1)
        forward();
      else if (error1 == 2)
      {
        //speed control
        sharpRightTurnT();
      }
      else if (error1 == 3)
      {
        //speed control
        sharpLeftTurnT();
      }
      else if (error1 == 4)
      {
        //speed reduction
        forward();
      }
      else if (error1 == 5)
      {
        //speed reduction
        right() ;
      }
      else if (error1 == 6)
      {
        //speed reduction
        left();
      }
      else if (error1 == 7)
      { //speed reduction
        //if (q == 'f')
         // reverse();
        if (q == 'r' || q=='f')
          left();
       else if (q == 'l'|| q=='f')
          right();
      
      }  
   delay(500);
    error2=0;
    p = 0;//node turning count
    n = 1;//to change the reading statements to that of flank
    f = 1;//to  confirm 90 degree turn
  }

  if (cy == fn && cx != sn) //movement of bot in X direction
  {
    read_sensor_values3();

    if (error3 == 1 && error4 != 11)
      forward();
    else if (error3 == 2 && error4 != 11)
    {
      //speed control
      sharpRightTurnT();
    }
    else if (error3 == 3 && error4 != 11)
    {
      //speed control
      sharpLeftTurnT();
    }
    else if (error3 == 4 && error4 != 11)
    {
      //speed reduction
      forwardS();
    }
    else if (error3 == 5 && error4 != 11)
    { //speed reduction
      right() ;
    }
    else if (error3 == 6 && error4 != 11)
    { //speed reduction
      left();
    }
    else if (error3 == 7 && error4 != 11)
    {
      
      if (q == 'r' || q== 'f')
        left();
      else if (q == 'l' || q== 'f')
        right();
    }


    if (error4 == 11)
    { error4 = 0;
      read_sensor_values3();
      if (error1 == 1)
        forward();
      else if (error1 == 2)
      {
        //speed control
        sharpRightTurnT();
      }
      else if (error1 == 3)
      {
        //speed control
        sharpLeftTurnT();
      }
      else if (error1 == 4)
      {
        //speed reduction
        forward();
      }
      else if (error1 == 5)
      {
        //speed reduction
        right() ;
      }
      else if (error1 == 6)
      {
        //speed reduction
        left();
      }
      else if (error1 == 7)
      { //speed reduction
        
      
        if (q == 'r' || q== 'f')
          left();
        else if (q == 'l' || q== 'f')
          right();
      
      }     
          

      }

      delay(500);
    }

if (cy == fn && cx == sn) //reached the target node so rotate 180 degrees
  {
    stop_bot();
    digitalWrite(led, HIGH);
    delay(4000);
    digitalWrite(led, LOW);
   
  }

if (x==2 && y== -1) //reached the initial node so rotate 180 degrees
  {
    sharpLeftTurn() ;
    delay(1900);
    stop_bot();
    Serial.println(" *FOLLOWING ENDS!!!* ");
    m=1;

  }
if(m==1)
 {
  stop_bot(); 
 }
}

//END OF LOOP

//BEGINING OF UDF

int node_turning_count() //to count nodes while rotating at intersections
{
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
 /* Serial.print("the sensor values from 1 to 3 are:\t\t  ");
  Serial.print("s1:");
  Serial.print(sensor[0]);
  Serial.print("\t");
  Serial.print("s2:");
  Serial.print(sensor[1]);
  Serial.print("\t");
  Serial.print("s3:");
  Serial.print(sensor[2]);
  Serial.print("\t");*/

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
  /*Serial.print("the sensor values from 4 to 5 are:\t\t  ");
  Serial.print("s4:");
  Serial.print(sensor[3]);
  Serial.print("\t");
  Serial.print("s5:");
  Serial.print(sensor[4]);
  Serial.print("\t");*/
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
  /*Serial.print("the sensor values from 1 to 3 are:\t\t  ");
  Serial.print("s1:");
  Serial.print(sensor[0]);
  Serial.print("\t");
  Serial.print("s2:");
  Serial.print(sensor[1]);
  Serial.print("\t");
  Serial.print("s3:");
  Serial.print(sensor[2]);
  Serial.print("\t");*/

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
  /*Serial.print("the sensor values from 4 to 5 are:\t\t  ");
  Serial.print("s4:");
  Serial.print(sensor[3]);
  Serial.print("\t");
  Serial.print("s5:");
  Serial.print(sensor[4]);
  Serial.print("\t");*/
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
 // Serial.println("forward");
  q = 'f';
}
void forwardS()  //move forward SLOW
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 158);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 158);
  analogWrite(motorInput4, 0);
  //Serial.println("forward");
  q = 'f';
}
void reverse() //move backward
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 0);
  analogWrite(motorInput2, 158);
  analogWrite(motorInput3, 0);
  analogWrite(motorInput4, 158);
  //Serial.println("reverse");

}
void right() //move left with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 0);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 90);
  analogWrite(motorInput4, 0);
 // Serial.println("right");

}
void left() //move right with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 900);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 0);
  analogWrite(motorInput4, 0);
 // Serial.println("left");
  
}
void sharpRightTurn()  //move right with both the wheels moving in opposite direction with EQUAL SPEED
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, 0);
  digitalWrite(motorInput2, 1);
  digitalWrite(motorInput3, 1);
  digitalWrite(motorInput4, 0);
 // Serial.println("right");
 
}
void sharpRightTurnT()  //move right with both the wheels moving in opposite direction with UNEQUAL SPEED
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 0);
  analogWrite(motorInput2, 90);
  analogWrite(motorInput3, 90);
  analogWrite(motorInput4, 0);
  //Serial.println("right");
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
  
}
void sharpLeftTurnT() //move left with both the wheels moving in opposite direction with UNEQUAL SPEEDS
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 90);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 0);
  analogWrite(motorInput4, 90);
  //Serial.println("left");
  q = 'l';
}
void leftR() //move left with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 0);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 0);
  analogWrite(motorInput4, 90);
  //Serial.println("right");
  q = 'l';// ut this value opposite to that of the actual
}
void rightR() //move left with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 0);
  analogWrite(motorInput2, 90);
  analogWrite(motorInput3, 0);
  analogWrite(motorInput4, 0);
  //Serial.println("left");
  q = 'r';
}
void stop_bot() //motors stop running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(motorInput1, 0);
  digitalWrite(motorInput2, 0);
  digitalWrite(motorInput3, 0);
  digitalWrite(motorInput4, 0);
 // Serial.println("stop");

}
void rightS() //move left with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 0);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 100);
  analogWrite(motorInput4, 0);
  delay(250);
 // Serial.println("right");

}
void leftS() //move right with one motor stopped and other running
{
  /*The pin numbers and high, low values might be different depending on your connections */
  analogWrite(motorInput1, 100);
  analogWrite(motorInput2, 0);
  analogWrite(motorInput3, 0);
  analogWrite(motorInput4, 0);
  delay(250);
 // Serial.println("left");
  
}
