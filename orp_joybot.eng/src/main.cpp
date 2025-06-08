// this is the main code to run the robot with a  joystick(The xbox series x joystick is used for this)over bluetooth.
// here is a link on how to learn to connect the raspberry pi to the joystick in bluetooth : https://pimylifeup.com/raspberry-pi-bluetooth/
// part of the code is based of this source code : https://gist.github.com/jasonwhite/c5b2048c15993d285130

// this are the standard header files for the main file below.
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include <linux/joystick.h> // this header is for the joystick control.
#include <wiringPi.h> // for more info on wiringPi(the gpio library) link is here : https://github.com/WiringPi/WiringPi
// english documentation link is here: https://github.com/WiringPi/WiringPi/blob/master/documentation/english/functions.md

using namespace std; // to make the code a little bit shorter.
int ia2 = 14;
int ib2 = 15;
int ia1 = 18;
int ib1 = 23;



// this are the main functions to to control the motor directions.

void right(){

    digitalWrite(ia1,LOW);
    digitalWrite(ia2,LOW);
    digitalWrite(ib1,LOW);
    digitalWrite(ib2,HIGH);
    cout << "Robot moves rightwards"<< '\n';
}


void left(){

    digitalWrite(ia1,HIGH);
    digitalWrite(ia2,LOW);
    digitalWrite(ib1,LOW);
    digitalWrite(ib2,LOW);
    cout << "Robot moves leftwards"<< '\n';
}

void backward(){

    digitalWrite(ia1,HIGH);
    digitalWrite(ia2,LOW);
    digitalWrite(ib1,LOW);
    digitalWrite(ib2,HIGH);
    cout << "Robot moves backwards"<< '\n';
}

void forward(){

    digitalWrite(ia1,LOW);
    digitalWrite(ia2,HIGH);
    digitalWrite(ib1,HIGH);
    digitalWrite(ib2,LOW);
    cout << "Robot moves forward"<< '\n';
}


void stop(){

    digitalWrite(ia1,LOW);
    digitalWrite(ia2,LOW);
    digitalWrite(ib1,LOW);
    digitalWrite(ib2,LOW);
    cout << "Robot stops"<< '\n';
}

void stopped(){

    digitalWrite(ia1,LOW);
    digitalWrite(ia2,LOW);
    digitalWrite(ib1,LOW);
    digitalWrite(ib2,LOW);
    cout << "Robot is stopped"<< '\n';
}
int read_event(int fd, struct js_event *event) {


    long int bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    /* Error, could not read full event. */
    return -1;
}

unsigned long get_axis_count(int fd) {
 unsigned long axes;
if (ioctl(fd, JSIOCGAXES, &axes) == -1)
return 0;

return axes;

}


unsigned long get_button_count(int fd) {

 unsigned char buttons;
 if (ioctl(fd,JSIOCGBUTTONS, &buttons)== -1)
 return 0;

 return buttons;

}



struct axis_state {
int x,y;

};

unsigned long get_axis_state(struct js_event *event, struct axis_state axes [3])
{
unsigned long  axis = event->number /2;

if (axis < 3) {


    if (event->number % 2 )
    axes[axis].x = event-> value;
    else
    axes[axis].y = event-> value;
}

return axis;

}


int main(int argc, char * argv[]) {


    wiringPiSetupGpio();

    pinMode(ia1,OUTPUT);
    pinMode(ia2,OUTPUT);
    pinMode(ib1,OUTPUT);
    pinMode(ib2,OUTPUT);
    
    const char *device;
    int js;
    struct js_event event;
    struct axis_state axes[3] = {0};
    size_t axis;

    if (argc > 1)
        device = argv[1];
    else
        device = "/dev/input/js0";

    js = open(device, O_RDONLY);

    if (js == -1)
        perror("Could not open joystick");

    /* This loop will exit if the controller is unplugged. */
    while (read_event(js, &event) == 0)
    {
        switch (event.type)
        {
            case JS_EVENT_BUTTON:
                printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
                break;
            case JS_EVENT_AXIS:
                axis = get_axis_state(&event, axes);
                if (axis < 3)
                    printf("Axis %zu at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
                break;
            default:
                /* Ignore init events. */
                break;
        
        
        
       
            stopped();
        }

        // the robot is controlled by this joystick buttons.
          if (event.number == 3) { // x button
            forward(); 
            delay(50);
            stop();
          }
        if (event.number == 4) { // y button 
            backward();
             delay(50);
             stop();
        }
        if (event.number == 1) { // b button
            left(); 
            delay(50);
            stop();

        }
        
   
        if (event.number == 11) { // select button.
            right(); 
            delay(50);
            stop();
       
        
       }
         fflush(stdout);
    
    }
        close(js);

        return 0;

        }