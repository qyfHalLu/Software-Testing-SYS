#include "mbed.h"
#include "physcom.h"
 using namespace physcom;
 Serial pc(USBTX, USBRX); // tx, rx
// SIG goes to pin 11 of the mbed board
// GND goes to pin GND of the mbed board
// 5V goes to pin 5V from Pololu robot
M3pi robot; //create an object of type  M3pi

Ping Pinger(p11);
int range;

// int main() {
//    int range;
//
//    while(1) {
//        Pinger.Send();
//        wait_ms(300);
//        range = Pinger.Read_cm();
//        pc.printf("range: %d\r\n", range);
//     }
// }


// bottom sensors
int main() {
    pc.printf("Start calibration!\r\n");
    robot.sensor_auto_calibrate();   //robot executes calibration
    pc.printf("Finished calibration!\r\n");
    while (1) {
        int sensors[5];
        robot.calibrated_sensors(sensors);  //5 values are read in a 
vector
        pc.printf("sensor values: %d; %d; %d; %d; %d;\r\n", sensors[0], 
sensors[1],sensors[2], sensors[3], sensors[4]);

        //if((sensors[2]>800)){ //straight
//           robot.activate_motor (0,0.2) ; 
//           robot.activate_motor (1,0.2) ; 
//       }
        if( sensors[1]>150 ){ // turn left
            robot.activate_motor (0,0) ; 
            robot.activate_motor (1,0.3) ; 
            }
        else if (sensors[0]>150 && sensors[0]<600) {
            // sharp left
            robot.activate_motor (0,-0.05) ; 
            robot.activate_motor (1,0.3) ; 
            } 
        else if((sensors[3]>150) ){ // turn right
            robot.activate_motor (0,0.3) ; 
            robot.activate_motor (1,0) ; 
        }
        else if (sensors[4]>150 && sensors[4]<600) { 
        // sharp right
            robot.activate_motor (0,0.3) ; 
            robot.activate_motor (1,-0.05) ; 
            }
            
            
        Pinger.Send();
        wait_ms(15);
        range = Pinger.Read_cm();
        pc.printf("range: %d\r\n", range);

        if((sensors[0]<500 && sensors[1]<500 && sensors[2]<500 && 
sensors[3]<500 && sensors[4]<500)){
            robot.activate_motor (0,0) ; // drive left motor 1/10 max 
speed forward
            robot.activate_motor (1,0) ; // drive right motor 0/10 max 
speed forward
        }
        //wait_ms(1000);
    }
}
