#include <wiringPi.h>
//#include <iostream>
//#include <stdio.h>
//#include <sys/time.h>
//#include <time.h>
#include <stdlib.h>
//#include <sched.h>
//#include <sstream>
//#include <fstream>

#define PIN 0

using namespace std;

void dwa(){
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);
	digitalWrite(PIN, LOW); 	delayMicroseconds(190);	
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);	
	digitalWrite(PIN, LOW);
	delayMicroseconds(1180);
}

void jeden(){
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);	
	digitalWrite(PIN, LOW);
	delayMicroseconds(1180);
}

void trzy(){
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);
	digitalWrite(PIN, LOW); 	delayMicroseconds(190);	
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);	
	digitalWrite(PIN, LOW); 	delayMicroseconds(190);	
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);	
	digitalWrite(PIN, LOW);
	delayMicroseconds(1180);
}

int main(int argc, char *argv[]) {
	
  if(wiringPiSetup() == -1)
       return 0;
   
   int komenda=0;
   int adres[27]={2,2,2,2,2,1,2,2,2,2,2,3,2,2,1,2,2,2,2,2,2,2,2,2,2,3,2};
   
   komenda=atoi(argv[1]);		//ATOI zamienia zmienna CHAR na INT,
   
   for(int razy=0;razy<10;razy=razy+1){
	   jeden();
	   delayMicroseconds(1380);
	   for(int i=0;i<27;i=i+1){
			if(adres[i]==2) dwa();
			if(adres[i]==1) jeden();
			if(adres[i]==3) trzy();
	   }
		if(komenda==11){
			jeden(); dwa(); dwa(); dwa(); dwa(); dwa();
		}
		if(komenda==10){
			dwa(); jeden(); dwa(); dwa(); dwa(); dwa();
		}
		delay(8);																			
		digitalWrite(PIN, HIGH);	delayMicroseconds(190);		digitalWrite(PIN, LOW);		delayMicroseconds(2500);	// pik pomiedzy powtorzeniami
   }
   
  return 0;
}