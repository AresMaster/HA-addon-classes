#include <wiringPi.h>
//#include <iostream>
//#include <stdio.h>
//#include <sys/time.h>
//#include <time.h>
#include <stdlib.h>
//#include <sched.h>
//#include <sstream>
//#include <fstream>

#define PIN 0		//pin do wysylania
#define ZCN 810 	// "ZERO" CZAS NISKI - czas stanu niskiego bitu "0"
#define ZCW 240		// "ZERO" CZAS WYSOKI - czas stanu wysokiego bituu "0"
#define JCN 280		// "JEDEN" CZAS NISKI - czas stanu niskiego bitu "1"
#define JCW	770		// "JEDEN" CZAS WYSOKI - czas stanu wysokiego bitu "1"
#define PAUZA 6		// czas pauzy w milisekundach

using namespace std;

void zero(){
	digitalWrite(PIN, LOW);		delayMicroseconds(ZCN);		// przelacz na niski i odczekaj (ZCN)
	digitalWrite(PIN, HIGH); 	delayMicroseconds(ZCW);		// przelacz na wysoki i czekaj (ZCW)
}

void jeden(){
	digitalWrite(PIN, LOW);		delayMicroseconds(JCN);	     // przelacz na niski i odczekaj (JCN)
	digitalWrite(PIN, HIGH);	delayMicroseconds(JCW);      // przelacz na wysoki i czekaj (JCW)
}

void pauza(){
	digitalWrite(PIN, LOW);		delay(PAUZA);				//przelacz na niski i czekaj
}

int main(int argc, char *argv[]) {
	
  if(wiringPiSetup() == -1)
       return 0;
   
   int komenda=0;
   int adres[19]={1,0,1,0,1,0,1,1,1,1,1,1,0,0,0,1,0,0,0};	//adres lub inna stala czesc nadawana zawsze na poczatku transmisji, pozamieniac na 0 i 1
   
   komenda=atoi(argv[1]);		//ATOI zamienia zmienna CHAR na INT,
   
   for(int razy=0;razy<10;razy=razy+1){
	   
	   for(int i=0;i<19;i=i+1){
			if(adres[i]==0) zero();
			if(adres[i]==1) jeden();
			if(adres[i]==2) pauza();
	   }
		if(komenda==11){
		     zero(); jeden(); zero(); zero(); zero(); zero();   // pozamieniac na "zero();" i "jeden();"
		}
		if(komenda==10){
			zero(); jeden(); zero(); jeden(); zero(); zero();	// pozamieniac na "zero();" i "jeden();"
			}
		if(komenda==12){
			zero(); jeden(); jeden(); zero(); zero(); zero();	// pozamieniac na "zero();" i "jeden();"
		}
		pauza();
   }
   
  return 0;
}