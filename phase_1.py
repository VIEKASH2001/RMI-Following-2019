import serial
import time
a="COM12"
ard=serial.Serial(a,9600)
while(True):
    print("enter X and Y coordinate")
    C=input();
    print(C);
    ard.write(str.encode(str(C)))
    ard.flush();

    
 
