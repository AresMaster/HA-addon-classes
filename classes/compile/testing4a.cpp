/*
Poprawka 3 - temp_binary
Sprawdza dodatkowe 3 jedynki przy synchronizacji
Poprawka 4 - temp_sig
Jesli nie znajdzie kombinacji 11111000111 pomija zapis - Ln:151
Poprawka 5 - nadpisuje plik, zamiast dodawać linię - Ln:35
Poprawka 6 - jeszcze 000 do synchronizacji (111111000111000) - Ln:152
signal_check - sprawdza tylko 11111
*/
#include <wiringPi.h>
#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <sched.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <cmath>



using namespace std;

//store data into array 
#define MAX_CHANGE_TO_KEEP 266
static int durations[MAX_CHANGE_TO_KEEP];
static float temper, lastTemp[3],	roznica;	//temperatura obliczona, ostatnia wartość temperatury
static int binary[266];		//tyle bitow z transmisji zapisujemy
static int licznik=-1;		//zaznacza miejsce gdzie zaczyna sie transmisja
static int temper2[10];		//10 bitow temperatury	
static string plik="test2.txt";		//tu zapisuje  temperature z czujnika X
static string odebrane;		//tu zapisuje bity odebrane z radia 
static string tab[3];	//tu zapisuje bity synchronizacji z plików
static bool firstrun[3]={true,true,true};	//zaznacza czy to pierwsze uruchomienie
 
void log(string a){
  cout << a ;
}

// zapisuje do pliku temperatury, przyjmuje wartosc do wpisania i nazwe pliku
void zapisz(string cal,string nazwa){
	ofstream outfile;
	outfile.open(nazwa.c_str());
	outfile << cal; 
}

// odczytuje z podanego pliku bity synchronizacji
void odczyt(string wejscie,int numer){
	ifstream input(wejscie.c_str());
		input >> tab[numer-1];
	cout << "Czujnik "<< numer << ": " << tab[numer-1] << endl;
}

//zamienia zmienna 'double' na 'string' aby latwo zapisac
string temper2String(double wynik){
    stringstream mystream;
    mystream << wynik;
    return mystream.str();
}

string intToString(int myint){
    string mystring;
    stringstream mystream;
    mystream << myint;
    return mystream.str();
}


void handleInterrupt() {
 
  static unsigned int duration;
  static unsigned int changeCount;
  static unsigned long lastTime;

  static int lockPassed;
  static int lockChange;

  long time = micros();
  duration = time - lastTime;

  //wait for lock
  if (lockChange == 0 && duration > 2040 && duration < 2600 && lockPassed == 0) { 
    changeCount = 0;

    //store duration
    durations[changeCount++] = duration;
    lockChange = 1;
  } else if (lockChange == 1 && duration > 1830 && duration < 2000 && lockPassed == 0) {

    durations[changeCount++] = duration;
    lockChange = 2;
  } else if (lockChange == 2 && duration > 3500 && duration < 4000 && lockPassed == 0) {

    durations[changeCount++] = duration;
    lockChange = 3;
    lockPassed = 1;	//lock is finished
  }


  else if (lockPassed != 0) { // REST OF DATA


    if (changeCount > MAX_CHANGE_TO_KEEP) { // store 100 change Max
      //ended
      lockPassed = 0;
      changeCount = 0;
      lockChange = 0;
//      log("===============================");
      //start after the lock
      for (int i=3; i < MAX_CHANGE_TO_KEEP; i=i+2) {
	
        if (durations[i] > 1800 && durations[i] < 1970 &&
            durations[i+1] > 1900 && durations[i+1] < 2200  ) {
			continue;
		
        } else if (durations[i] > 1800 && durations[i] < 1970 &&
            durations[i+1] > 3500 && durations[i+1] < 4100  ) {
			continue;
			
        } else if (	(	(durations[i] > 10)	 && 
						(durations[i] < 1000)	) 	|| 	
					(	(durations[i+1] > 10) 	&&	 
						(durations[i+1] < 1000)	)	)	{
			continue;
			
		} else {

          changeCount = 0;
          lockChange = 0;
          lockPassed = 0;
          break;
        }

      }
		cout << endl;
		
	  	for (int i=2; i< MAX_CHANGE_TO_KEEP; i=i+2) {
		if (durations[i] < 4080 && durations[i] > 3000) {
		binary[i/2]=1;
		}
		else binary[i/2]=0;
		cout << binary[i/2];
		}

		
		for (int i=0;i<45;i=i+1){
			if(	binary[i  ]==1 && 
				binary[i+1]==0 && 
				binary[i+2]==1 && 
				binary[i+3]==1 && 
				binary[i+4]==1 && 
				binary[i+5]==1 && 
				binary[i+6]==1 ) 
				{
				licznik=i;
				break;
			}
			else continue;
		}
		 if(licznik!=-1)
		{
			odebrane="";
			cout << endl << "Odebrane: ";
			for (int i=7;i<15;i=i+1){
				odebrane=odebrane+intToString(binary[licznik+i]);
			}
			
			cout << odebrane;
			cout << endl << "Zapisane: ";
			cout << tab[0] << " " << tab[1] << " " << tab[2];
				
			cout << endl << "Temp: ";
			for (int i=23;i<33;i=i+1){
				temper2[i-23]=binary[licznik+i];
				cout << binary[licznik+i];
				cout << temper2[i-23] << " ";
			}

			/*	STARA WERSJA PRZELICZNIKA
			
				temper = 	temper2[0]*1+
							temper2[1]*2+
							temper2[2]*4+
							temper2[3]*8+
							temper2[4]*16+
							temper2[5]*32+
							temper2[6]*64+
							temper2[7]*128+
							temper2[8]*256+
							temper2[9]*512;
							*/
							
				// NOWA WERSJA
				temper=0;			
				for(int i=0;i<10;i=i+1){
					temper=temper+(temper2[i]<<i);
				}			
				
				temper = temper-400;
				temper=temper/10;
				
				if(firstrun[0]) lastTemp[0]=temper; 
				if(firstrun[1])	lastTemp[1]=temper;
				if(firstrun[2])	lastTemp[2]=temper;

				if(odebrane==tab[0]) 
				{	if(fabs((lastTemp[0]-temper)<5))
					{
					roznica=fabs(lastTemp[0]-temper);	
					zapisz(temper2String(temper),"temp1.txt"); 
					cout << endl << "Czujnik 1: " << temper << " (" << lastTemp[0] << ") ";
					firstrun[0]=false; lastTemp[0]=temper; cout << roznica;
					digitalWrite (29, HIGH) ; delay (51) ;
					digitalWrite (29,  LOW) ;
					}
				} else if(odebrane==tab[1])
				{	if(fabs((lastTemp[1]-temper)<5))
					{
					roznica=fabs(lastTemp[1]-temper);
					zapisz(temper2String(temper),"temp2.txt"); 
					cout << endl << "Czujnik 2: " << temper << " (" << lastTemp[1] << ") ";
					firstrun[1]=false; lastTemp[1]=temper; cout << roznica;
					digitalWrite (29, HIGH) ; delay (53) ;
					digitalWrite (29,  LOW) ;
					}
				} else if(odebrane==tab[2])
				{	if(fabs((lastTemp[2]-temper)<5))
					{
					roznica=fabs(lastTemp[2]-temper);
					zapisz(temper2String(temper),"temp3.txt"); 
					cout << endl << "Czujnik 3: " << temper << " (" << lastTemp[2] << ") ";
					firstrun[2]=false; lastTemp[2]=temper; cout << roznica;
					digitalWrite (29, HIGH) ; delay (55) ;
					digitalWrite (29,  LOW) ;
					}
				} else cout << "brak synchronizacji";
									
			licznik=-1;
		} 
						

		
    } else {
      //store duration
      durations[changeCount++] = duration;
    }
  } else {
    //wait for another 
    changeCount = 0;
    lockChange = 0;
    lockPassed = 0;
  }	
  lastTime = time;  
}



int main(void) {
  if(wiringPiSetup() == -1)
       return 0;

	 pinMode (29, OUTPUT) ;
	 digitalWrite (29,  LOW) ;
	 
	cout << "Odczytanie bitow synchronizacji z pliku... \n";
    odczyt("1.txt",1);
    odczyt("2.txt",2);
	odczyt("3.txt",3);
        //attach interrupt to changes on the pin
        wiringPiISR(2, INT_EDGE_BOTH, &handleInterrupt);
  //interrupt will handle changes
  while(true);

}