/******************************************************************************

                              DARIUSZ S. SKOWRONSKI
               Program podlicza punkty na rzecz Ligi Pomorskiej
			

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
struct SwynikiGracza{
	string Przeciwnik;
	int liczbaBitew;
	int sumaPkt;
};
class CGracz{
	private:        
        string nick_gracza;
        SwynikiGracza wyniki_gracza[25];
    
    public:
    	CGracz(){
    		nick_gracza = "brak danych";
			for(int i = 0; i < 25 ;i++){
                wyniki_gracza[i].Przeciwnik = " "; 
				wyniki_gracza[i].liczbaBitew = 0;
				wyniki_gracza[i].sumaPkt = 0;   
            }    		
		}
		CGracz(string nickToSet){
			nick_gracza = nickToSet;
			for(int i = 0; i < 25 ;i++){
                wyniki_gracza[i].Przeciwnik = " "; 
				wyniki_gracza[i].liczbaBitew = 0;
				wyniki_gracza[i].sumaPkt = 0;   
            }
		}
    	void setNick(string nickToSet){
    		nick_gracza = nickToSet;
		}
		void addWynik(string przeciwnikToSet, int wynikToSet){
			for(int i = 0; i < 25 ;i++){
                if(wyniki_gracza[i].Przeciwnik == przeciwnikToSet){
                	wyniki_gracza[i].liczbaBitew++;
                	wyniki_gracza[i].sumaPkt += wynikToSet;
                	break;
				};
				if(wyniki_gracza[i].Przeciwnik == " "){
					wyniki_gracza[i].Przeciwnik = przeciwnikToSet;
					wyniki_gracza[i].liczbaBitew++;
                	wyniki_gracza[i].sumaPkt += wynikToSet;
                	break;
				} 				   
            }
		}
		string getNick(){
			return nick_gracza;
		}
		void dispWynik(){
			cout<< nick_gracza<< " wyniki: "<<endl;
			for(int i = 0; i < 25 ;i++){
                cout<<wyniki_gracza[i].Przeciwnik<< " "<< wyniki_gracza[i].liczbaBitew<<" "<<wyniki_gracza[i].sumaPkt<<endl; 				   
            }
		}
		float wynikiSuma(){
			float suma = 0;
			for(int i = 0; i < 25 ;i++){
				if(wyniki_gracza[i].Przeciwnik != " "){
					suma = suma + (wyniki_gracza[i].sumaPkt / wyniki_gracza[i].liczbaBitew);
				}			
			}
			return suma;
		}
	
};
enum stan{
	CZEKAM_NA_GRACZA,
	ODCZYT_1_GRACZA,
	ODCZYT_2_GRACZA,
	WYNIK
};

void dodajWynikGracza(CGracz tablica[25], string nickDoZnalezienia, string nickPrzeciwnika, int wynik);

int main(){
	
	fstream plik;
    string odczyt;
    char a[255];
    string nickZnaleziony;
    string nickPrzeciwnika;
    CGracz Gracze[25];
    stan stanOdczytu = CZEKAM_NA_GRACZA;
    
    char pomocniczyNickGracza[63];
    char pomocniczyNickPrzeciwnika[63];
    int pomocniczyWynik;
    int j = 0;
    
    cout<<"Wczytywanie danych z pliku"<<endl;
	 
    plik.open("nazwaTurniejuTuBedzie.txt", ios::in );
    if(plik.good() == true)
    {
    	
		while( !plik.eof() )
        {
        	plik.getline(  a , 255);
            if(a[0] != '-'){
            	stanOdczytu =  ODCZYT_1_GRACZA; 
            	
            	
            	for (int x = 0; x < 255; x++){
            		if(a[x] >= 'A' && a[x] <= 'z' && stanOdczytu == ODCZYT_1_GRACZA){
            			pomocniczyNickGracza[j] = a[x];
            			j++;
					}
					if(a[x] == 32 && stanOdczytu == ODCZYT_1_GRACZA){						
						stanOdczytu=ODCZYT_2_GRACZA;
						x++;
						j = 0;	
					}
					if(a[x] >= 'A' && a[x] <= 'z' && stanOdczytu ==ODCZYT_2_GRACZA){
            			pomocniczyNickPrzeciwnika[j] = a[x];            			
						j++;
					}
					if(a[x] == 32 && stanOdczytu == ODCZYT_2_GRACZA){						
						stanOdczytu = WYNIK;
						x++;
						j = 0;	
					}
					if (a[x] >= '0' && a[x] <= '9' && stanOdczytu == WYNIK){
						pomocniczyWynik = (int)a[x]-48;
						stanOdczytu = CZEKAM_NA_GRACZA;
					}
				} 
				nickZnaleziony = pomocniczyNickGracza;
				nickPrzeciwnika = pomocniczyNickPrzeciwnika;
			//	cout<<nickZnaleziony<<" "<< nickPrzeciwnika<<" "<< pomocniczyWynik<<endl;
				dodajWynikGracza(Gracze, nickZnaleziony, nickPrzeciwnika, pomocniczyWynik);           	
            	
				if(stanOdczytu == CZEKAM_NA_GRACZA){
					for(int z=0; z<63; z++)
				{
					pomocniczyNickGracza[z] = 0;
					pomocniczyNickPrzeciwnika[z] = 0;
				}
				};
				           	
			}
        }
		for(int i = 0; i < 25 ;i++){ 
			if(Gracze[i].getNick() != "brak danych"){	
				cout<<"suma punktow gracza "<<Gracze[i].getNick()<< " wynosi: "<<Gracze[i].wynikiSuma()<<endl;		
			}
		}
        plik.close();
    }
	
   printf("\a");
   return 0;
}

void dodajWynikGracza(CGracz tablica[25], string nickDoZnalezienia, string nickPrzeciwnika, int wynik){
	bool czyJest = false;
	for(int i = 0; i < 25 ;i++){
		if(tablica[i].getNick() == nickDoZnalezienia){
			tablica[i].addWynik(nickPrzeciwnika, wynik);
			czyJest = true;	
			break;		
		}
		if(tablica[i].getNick() == "brak danych"){
				tablica[i].setNick(nickDoZnalezienia);
				tablica[i].addWynik(nickPrzeciwnika, wynik);
				break;
			}
	}
	
}

