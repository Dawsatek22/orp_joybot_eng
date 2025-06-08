
// this is a code to test the dc motors with a L9110S motor driver

#include <iostream> // standard input output header.
#include <wiringPi.h> // for more info on wiringPi(the gpio library)
//link is here : https://github.com/WiringPi/WiringPi
// english documentation link is here: https://github.com/WiringPi/WiringPi/blob/master/documentation/english/functions.md
// if you have problems accessing gpio during launch this might help: https://www.reddit.com/r/raspberry_pi/comments/194qhwc/gpionext_error_no_access_todevmem/

//This are the output pins for the hbridge below.
int ia2 = 14;
int ib2 = 15;
int ia1 = 18;
int ib1 = 23;




using namespace std; // to make the code a little bit shorter.

// below are the functions for the motor directions.

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
int main() {

wiringPiSetupGpio(); // gpio pins are setup in the bcm numbering.

// the pins are set into output pins.
pinMode(ia1,OUTPUT);
pinMode(ia2,OUTPUT);
pinMode(ib1,OUTPUT);
pinMode(ib2,OUTPUT);

// now  the directions are tested below.

   forward();

   delay(500);
   stop();
   delay(2000);
   backward();

   delay(500);
   stop();
   delay(2000);


   left();

   delay(500);
   stop();
   delay(2000);


   right();

   delay(500);
   stop();
   delay(2000);

}


