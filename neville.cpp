#include "mbed.h"
#include "physcom.h"
 using namespace physcom;
 Serial pc(USBTX, USBRX); // tx, rx
// SIG goes to pin 11 of the mbed board
// GND goes to pin GND of the mbed board
// 5V goes to pin 5V from Pololu robot
M3pi robot; //create an object of type  M3pi
DigitalOut redled(p18);
DigitalOut greenled(p19);
//DigitalOut greenled(p
Ping Pinger(p11);
int range;
float light_value;
AnalogIn passive_light(p20);


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
    pc.printf("Start!\r\n");
    pc.printf("battery: %f\r\n", robot.battery()); //battery status

    
    pc.printf("Start calibration!\r\n");
    robot.sensor_auto_calibrate();   //robot executes calibration
    pc.printf("Finished calibration!\r\n");

    while (1) {
        int sensors[5];
        robot.calibrated_sensors(sensors);  //5 values are read in a vector
        pc.printf("sensor values: %d; %d; %d; %d; %d;\r\n", sensors[0], sensors[1],sensors[2], sensors[3], sensors[4]);

        light_value = passive_light.read();
        pc.printf("value: %f\r\n", light_value);
//        pc.printf("range: %d\r\n", range);
//        if((sensors[2]>800)){ //straight
//           robot.activate_motor (0,0.2) ; 
//           robot.activate_motor (1,0.2) ; 
//       }
        
//        wait(0.5);

    
         if( sensors[1]>150 ){ // turn left
            robot.activate_motor (0,0) ; 
            robot.activate_motor (1,0.3) ; 
                    if (light_value > 0.2){
            redled = 0;
            greenled = 0;
        } 
        else if (light_value <0.2){
            redled = 1;
            greenled = 1;
        }
            }
        else if (sensors[0]>150 && sensors[0]<600) {
            // sharp left
            robot.activate_motor (0,-0.15) ; 
            robot.activate_motor (1,-0.15) ;
            wait_ms(200);
            robot.activate_motor (0,-0.05) ; 
            robot.activate_motor (1,0.3) ; 
                    if (light_value > 0.2){
            redled = 0;
            greenled = 0;
        } 
        else if (light_value <0.2){
            redled = 1;
            greenled = 1;
        }
            } 
        else if((sensors[3]>150) ){ // turn right
            robot.activate_motor (0,0.3) ; 
            robot.activate_motor (1,0) ; 
                    if (light_value > 0.2){
            redled = 0;
            greenled = 0;
        } 
        else if (light_value <0.2){
            redled = 1;
            greenled = 1;
        }
        }
        else if (sensors[4]>150 && sensors[4]<600) { 
        // sharp right
            robot.activate_motor (0,-0.15) ; 
            robot.activate_motor (1,-0.15) ;
            wait_ms(200);
            robot.activate_motor (0,0.3) ; 
            robot.activate_motor (1,-0.05) ; 
                    if (light_value > 0.2){
            redled = 0;
            greenled = 0;
        } 
        else if (light_value <0.2){
            redled = 1;
            greenled = 1;
        }
            }
            
            
        Pinger.Send();
        wait_ms(0);
        range = Pinger.Read_cm();
        pc.printf("range: %d\r\n", range);

        if( (sensors[0]==0 && sensors[1]==0 && sensors[2]==0 && sensors[3]==0 && sensors[4]==0) || range < 40){
            robot.activate_motor (0,0) ; // stop
            robot.activate_motor (1,0) ; // stop
        }
        //wait_ms(1000);
    }
}
