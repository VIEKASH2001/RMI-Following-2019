import serial
import time
a="COM10"
ard=serial.Serial(a,9600)
while True:
    X=b'1'
    ard.write(str.encode(str(X)))
    ard.flush();
    
    
    
 

   
