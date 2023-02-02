#include <wiringPi.h>
#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <sched.h>
#include <sstream>
#include <fstream>

#define PIN 0

using namespace std;

void dwa(){
	//std::cout <<"2";
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);
	digitalWrite(PIN, LOW); 	delayMicroseconds(190);	
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);	
	digitalWrite(PIN, LOW);
	delayMicroseconds(1180);
}

void jeden(){
	//std::cout <<"1";
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);	
	digitalWrite(PIN, LOW);
	delayMicroseconds(1180);
}

void trzy(){
	//std::cout <<"3";
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);
	digitalWrite(PIN, LOW); 	delayMicroseconds(190);	
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);	
	digitalWrite(PIN, LOW); 	delayMicroseconds(190);	
	digitalWrite(PIN, HIGH);	delayMicroseconds(190);	
	digitalWrite(PIN, LOW);
	delayMicroseconds(1180);
}

int main(int argc, char *argv[]) {
	
  if(wiringPiSetup() == -1) {
	return 0; 
  }
   
   int komenda=0;
   int adres[28]={1,2,1,2,3,1,3,1,2,3,
                  1,3,1,3,2,2,1,2,3,1,
				  2,2,2,3,2,1,3,2};
		
   komenda=atoi(argv[1]);		//ATOI zamienia zmienna CHAR na INT,
   
   for(int razy=0;razy<10;razy=razy+1){  // ilość wysłanych transmisji 
	   jeden();
	   delayMicroseconds(1380);           
	   for(int i=1;i<28;i=i+1){          // dodatkowa 1 z przodu
			if(adres[i]==2) dwa();
			if(adres[i]==1) jeden();
			if(adres[i]==3) trzy();
	   }
		if(komenda==11){
			jeden(); dwa(); dwa(); dwa(); dwa(); dwa(); //on,
		}
		if(komenda==10){
			dwa(); jeden(); dwa(); dwa(); dwa(); dwa(); //off,
		}
		if(komenda==12){
			trzy(); dwa(); dwa(); dwa(); trzy(); dwa(); dwa(); dwa(); jeden(); //25%,
		}
		if(komenda==13){
			trzy(); dwa(); dwa(); dwa(); trzy(); dwa(); jeden(); trzy(); jeden(); //33%,
		}
		if(komenda==14){
			trzy(); dwa(); dwa(); dwa(); trzy(); jeden(); trzy(); dwa(); jeden(); //48%,
		}
		if(komenda==15){
			trzy(); dwa(); dwa(); dwa(); trzy(); jeden(); dwa(); trzy(); jeden(); //62%,
		}
		if(komenda==16){
			trzy(); dwa(); dwa(); dwa(); dwa(); trzy(); dwa(); dwa(); jeden(); //76%,
		}
		if(komenda==17){
			trzy(); dwa(); dwa(); dwa(); dwa(); trzy(); jeden(); trzy(); jeden(); //86%,
		}
		if(komenda==18){
			trzy(); dwa(); dwa(); dwa(); dwa(); trzy(); jeden(); dwa(); dwa(); //90%,
		}
		if(komenda==19){
			trzy(); dwa(); dwa(); dwa(); dwa(); dwa(); trzy(); jeden(); dwa(); //96%,
		}
		if(komenda==20){
			trzy(); dwa(); dwa(); dwa(); dwa(); dwa(); dwa(); dwa(); dwa();  //100%,
		}
		delay(11);																			
		digitalWrite(PIN, HIGH);	delayMicroseconds(190);		digitalWrite(PIN, LOW);		delayMicroseconds(2500);	// pik pomiedzy powtorzeniami
   }
   
  return 0;
}