/******************************************************************************

                              DARIUSZ S. SKOWRONSKI
               PAROWANIE DLA 3 BITEW BEZ PROBLEMU, DLA WIEKSZEJ ILOSCI MOGA WYSTEPOWAC BLEDY
			Zalecane prowadzenie dodatkowej dokumentacji podczas turnieju

*******************************************************************************/
#define BITWY 5
#include <iostream>
#include <cstdlib>

using namespace std;

class CGracz
{
    private:
        int ID_gracza;
        string imie_gracza, nazwisko_gracza, nick_gracza;
        int iloscBitew;
        string aPrzeciwnicy_gracza[BITWY];
        int VP_gracza[BITWY];
        int GP_gracza[BITWY];
        int sumaVP_gracza, sumaGP_gracza;
        bool Pauza_gracza;
        string Przeciwnik_gracza;
    protected:
        
    public:
        CGracz(){
            ID_gracza = 0;
            imie_gracza = "Janusz";
            nazwisko_gracza = "Nosal";
            nick_gracza = "Nochal"; 
            sumaVP_gracza = 0;
            sumaGP_gracza = 0;
            Pauza_gracza = false;
            iloscBitew = BITWY;
            for(int i = 0; i < BITWY;i++){
                aPrzeciwnicy_gracza[i] = "nikt";    
            }
            
        }
        CGracz(int ID_k,string imie_k,string nazwisko_k,string nick_k) {
            ID_gracza = ID_k;
            imie_gracza = imie_k;
            nazwisko_gracza = nazwisko_k;
            nick_gracza = nick_k;
            sumaVP_gracza = 0;
            sumaGP_gracza = 0;
            Pauza_gracza = false;
            iloscBitew = BITWY;
            for(int i = 0; i < BITWY;i++){
                aPrzeciwnicy_gracza[i] = "nikt";    
            }
        }
        CGracz(int ID_k,string nick_k){
            ID_gracza = ID_k;
            imie_gracza = " ";
            nazwisko_gracza = " ";
            nick_gracza = nick_k;
            sumaVP_gracza = 0;
            sumaGP_gracza = 0;
            Pauza_gracza = false;
            iloscBitew = BITWY;
            for(int i = 0; i < BITWY;i++){
                aPrzeciwnicy_gracza[i] = "nikt";    
            }
        }
 //-------------------------------------------------------------
 // metody
        int addPrzeciwnik(string przeciwnik, int battle) { 
            bool jest = false;
            int j = 0;
            for(int i = 0; i< BITWY;i++){
              if(aPrzeciwnicy_gracza[i] == przeciwnik) {
                  jest = true;
				   return 0;
              }  
			  if(aPrzeciwnicy_gracza[i] != "nikt"){
			  	j++;
			  }            
            }
             if(!jest)
            aPrzeciwnicy_gracza[battle] = przeciwnik; 
            return 1; }
        int addPoints(int VPtoAdd, int GPtoAdd, int whichBattle){
            sumaVP_gracza += VPtoAdd;
            sumaGP_gracza += GPtoAdd;
            VP_gracza[whichBattle] = VPtoAdd;
            GP_gracza[whichBattle] = GPtoAdd;
        } 
        bool setPauza(bool set){
            Pauza_gracza = set;
        }
        int getSumVP(){
            return sumaVP_gracza;
        }
        int getSumGP(){
            return sumaGP_gracza;
        }
        bool getPauza(){
            return Pauza_gracza;
        }
        string getNick(){
            return nick_gracza;
        }
        int getId(){
            return ID_gracza;
        }
        string getPrzeciwnik(int i){
            return aPrzeciwnicy_gracza[i];
        }
        int getNumPrzeciwnik(){
            return sizeof(aPrzeciwnicy_gracza)-1;
        }
        int getID(){
            return ID_gracza;
        }
        int Wypisz() { 
            cout<<imie_gracza<<" "<<nazwisko_gracza<<" "<<nick_gracza<<" "<<sumaVP_gracza<<" "<<sumaGP_gracza<<endl;
            return 0; }
        
}; 

struct	spisGraczy {
	int id;
	string name;
};

struct	spisWynikowGraczy {
	string nickWyn;
	int VPWyn;
	int GPwyn;
};

void Wypis_Graczy (CGracz *table, int ilosc);
void Sortowanie(CGracz *table, int ilosc );
bool Paring(CGracz *table, int ilosc, int whichBattle, spisGraczy lista[]);
string szukajNickGracza(int id, spisGraczy lista[]);
bool czyGral(CGracz pier, CGracz dwa);
int szukajGracza(CGracz *table, string nickSzuk, int ilosc);
// kombinowanie na 3 bitwy
//void kombinowanie(CGracz *table,  CGracz pomocnicza[], int paringiWsk[][2], int numStolu, int ilosc_old, int whichBattle,  int g1, int g2, int g3, int g4);
//kombinowanie na max 5 bitew
void kombinowanie(CGracz *table,  CGracz pomocnicza[], int paringiWsk[][3], int numStolu, int ilosc_old, int whichBattle,  int g1, int g2, int g3, int g4, int g5, int g6);

int main()
{
    int ilosc_graczy;
    int hobby = 0;
    int liczbaBitew = 3;
    int czyKonPom;
    int j = 0;
    printf("+--   __         _______    ____________   ________    --+\n");
	printf("+--  |  |       /  ___  \\  |_____  _____| |   ___  \\   --+\n");
	printf("+--  |  |      /  /   \\  \\      |  |      |  |   \\  \\  --+\n");
	printf("+--  |  |     /  /     \\  \\     |  |      |  |___/  /  --+\n");
	printf("+--  |  |    |  |       |  |    |  |      |      __/   --+\n");
	printf("+--  |  |    |  |       |  |    |  |      |  |\\  \\     --+\n");
	printf("+--  |  |     \\  \\     /  /     |  |      |  | \\  \\    --+\n");
	printf("+--  |  |____  \\  \\___/  /      |  |      |  |  \\  \\   --+\n");
	printf("+--  |_______|  \\_______/       |__|      |__|   \\__\\  --+\n");
	printf("+--              DARIUSZ \"DARLARK\" SKOWRONSKI            --+\n");			
    	
        cout<<"Podaj liczbe graczy: ";
        cin>>ilosc_graczy;
        cout<<"Podaj liczbe bitew: ";
    	cin>>liczbaBitew;
    	if (liczbaBitew >= ilosc_graczy){
    		cout<<"Za duzo bitew przy tej licbie graczy. Podaj zmniejszona liczbe bitew: ";
    		cin>>liczbaBitew;
		}
        //WCZYTANIE GRACZY
        CGracz *table = (CGracz*) new char[sizeof(CGracz)*ilosc_graczy];
        spisGraczy lista[ilosc_graczy];
        spisWynikowGraczy listaWynikowGraczy[ilosc_graczy];
        string graczeZWynikami[ilosc_graczy];
        for(int i=0;i<ilosc_graczy;i++){
            int id;
            string imie, nazwisko, nick; 
            cout<<"Nick gracza "<< i+1<<" : ";            
            cin>>nick;
            // jesli taki gracz juz jest
			while (szukajGracza(table, nick, i+1) != -1){
			cout<<"Jest juz gracz o takim nicku. Podaj inny nick dla gracza"<< i+1<<" : ";            
            cin>>nick;				
			}
            new (table+i) CGracz(i+1,nick);
            lista[i].id=i+1;
            lista[i].name=nick;
        }
        //WYPISYWANIE GRACZY
        Wypis_Graczy(table, ilosc_graczy);
        int numBitwy = 0;
        
    while(numBitwy < liczbaBitew){
	bool koniecWynikow = false ; 
	bool blad = false;
	
        //PARING
        Paring(table, ilosc_graczy, numBitwy, lista);
//        //WYPISYWANIE GRACZY
//        Wypis_Graczy(table, ilosc_graczy);
        //DODAWANIE PUNKTOW
        while(!koniecWynikow){
            int idToAdd, VPtoAdd, GPtoAdd, whichBattle;
            string nickToAdd;
            if(j<=ilosc_graczy){
	            cout<<"Podaj nazwe gracza, VP, GP: ";           
				cin>> nickToAdd >> VPtoAdd >> GPtoAdd;
				for (int x = 0; x < j; x ++){
						if (nickToAdd == listaWynikowGraczy[j].nickWyn) blad = true;
				}
				if (blad){
					cout<<"Dodawales juz wyniki temu graczowi. Podaj nazwe gracza, VP, GP: ";           
					cin>> nickToAdd >> VPtoAdd >> GPtoAdd;
				}
				if (szukajGracza(table, nickToAdd, ilosc_graczy+1)>=0 && VPtoAdd>=0 && VPtoAdd <= 12 && (GPtoAdd == 1 || GPtoAdd == 3 || GPtoAdd == 5 || GPtoAdd == 7 || GPtoAdd == 9)){
					idToAdd = szukajGracza(table, nickToAdd, ilosc_graczy+1);
	            	(table+idToAdd)->addPoints(VPtoAdd, GPtoAdd, numBitwy);
	            	listaWynikowGraczy[j].nickWyn = nickToAdd;
	            	listaWynikowGraczy[j].VPWyn = VPtoAdd;
	            	listaWynikowGraczy[j].GPwyn = GPtoAdd;
				}		
				else {
						cout<<"Podaj jeszcze raz (tylko teraz wpisz dobrze) nazwe gracza, VP, GP: ";
						cin>> nickToAdd >> VPtoAdd >> GPtoAdd;
						idToAdd = szukajGracza(table, nickToAdd, ilosc_graczy+1);
		            	(table+idToAdd)->addPoints(VPtoAdd, GPtoAdd, numBitwy);			
				}	
			}            
			j++;
			if(j == ilosc_graczy){
				printf("+--Wpisane wyniki za bitwe %d--+\n",numBitwy+1);
				for(int i=0;i<ilosc_graczy;i++){
					printf("%10s %d %d \n", listaWynikowGraczy[i].nickWyn.c_str(), listaWynikowGraczy[i].VPWyn, listaWynikowGraczy[i].GPwyn);
       			}
			}
			if(j>= ilosc_graczy){
				cout<<"Czy koniec wynikow? (1-tak)";
				cin>>czyKonPom;
				if(czyKonPom == 1) 
				{
				koniecWynikow = true;
				j = 0;
				for (int x = 0; x < ilosc_graczy; x ++){
					listaWynikowGraczy[x].nickWyn = " ";
					listaWynikowGraczy[x].VPWyn = 0;
					listaWynikowGraczy[x].GPwyn = 0;
				}
				break;}
				cout<<"Podaj gracza ktoremu chcesz cos poprawic oraz te poprawki";
				cin>> nickToAdd >> VPtoAdd >> GPtoAdd;
				idToAdd = szukajGracza(table, nickToAdd, ilosc_graczy+1);
            	(table+idToAdd)->addPoints(VPtoAdd, GPtoAdd, numBitwy);
				
			}						
        }
        //SORTOWANIE GRACZY
        Sortowanie(table, ilosc_graczy);
        //WYPISYWANIE GRACZY
		cout<<"WYNIKI PO"<<numBitwy+1<<" bitwie: "<<endl;
        Wypis_Graczy(table, ilosc_graczy);
        numBitwy++; 
		if(numBitwy >= liczbaBitew){
			cout<<"Czy dodaæ hobbystyke? (1-tak) ";
			cin>>hobby;
			if(hobby = 1){
				for ( int x = 0; x < ilosc_graczy; x++){
				int idToAdd = 0, GPtoAdd = 0;
				string nickToAdd;
				cout<<"Podaj gracza ktoremu chcesz dac punkty oraz punkty";
				cin>> nickToAdd >> GPtoAdd;
				idToAdd = szukajGracza(table, nickToAdd, ilosc_graczy+1);
            	(table+idToAdd)->addPoints(0, GPtoAdd, numBitwy);
				}
				
			}
		}       
    }
    return 0;
}

void Wypis_Graczy (CGracz *table, int ilosc){
    for(int i=0;i<ilosc;i++){
            cout<<i+1;
            (table+i)->Wypisz();
        }
}

void Sortowanie(CGracz *table, int ilosc )
{
    CGracz pom;
    for( int i = 0; i < ilosc; i++ )
    {
        for( int j = 0; j < ilosc - 1; j++ )
        {
            if( (table+j)->getSumGP() < (table+ j + 1 )->getSumGP() ){
                pom = *(table+ j + 1 );
                *(table+ j + 1 ) = *(table+j);
                *(table+j) = pom;
            }
            if( ((table+j)->getSumGP() == (table+ j + 1 )->getSumGP()) && ((table+j)->getSumVP() < (table+ j + 1 )->getSumVP()) ){
                pom = *(table+ j + 1 );
                *(table+ j + 1 ) = *(table+j);
                *(table+j) = pom;
            }
        }
    }
}

bool Paring(CGracz *table, int ilosc, int whichBattle, spisGraczy lista[] ){
    int i = 0, j = 0, numerStolu = 0, numerStolu_zapas=0, pomocnicza = 0;
    int paring[2][ilosc/2];
    int paring_zapas[2][3];    
    string pauzaName = " ";
    CGracz pom[ilosc];
    int ilosc_old = ilosc, ilosc_zap = ilosc;
    int graczyDoPom = 1;
    CGracz pom2[ilosc-1];
    CGracz pom_zapas[4];
    for(int x = 0; x<ilosc; x++){
        pom[x] = *(table+x);
    }
//ogarniecie pauzuj¹cego    
    if (ilosc%2 != 0) {
        i = ilosc-1;
        ilosc_zap--;
        bool pauza = false;
        CGracz pom2[ilosc-1];
        for(int x = 0; x<ilosc-1; x++){
            pom2[x] = pom[x];
            }
        while(!pauza && i>=0){
          if((table + i)->getPauza() == false){
			pauza = true;
            (table + i)->setPauza(true);    
            pauzaName = (table + i)->getNick();                        
            }  else i--;
        }        
		for(int x = i; x<ilosc-1;x++){
                 pom2[x] = pom[x+1];
                 pom[x] = pom2[x];
                }                
//        cout<<"wypisano"<<endl;        
		ilosc--;
    };
//ustalenie paringów z wy³aczeniem ostatnich 4 graczy
    while(ilosc>6){
        i=0;
        j=i+1;
        cout<<ilosc<<endl; 

        while(czyGral(pom[i],pom[j])) {
            j++;
            if (j >= ilosc - 1){
                cout<<"Trzeba wiecej kminienia, ostatni pozostali zawodnicy grali ze soba"<<endl;
//TU BYL KOD Z KMINIENEIM ALE BYL ZLY I OKROTNY
			}
        }
// DOPISANIE DO PARINGOW, ORAZ DOPISANIE PRZECIWNIKOW DO LISTY GRACZA            
		paring[0][numerStolu] = pom[i].getId();
        paring[1][numerStolu] = pom[j].getId();
        pomocnicza = szukajGracza(table ,pom[i].getNick(), ilosc_old);
        if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[j].getNick(), whichBattle);
        pomocnicza = szukajGracza(table ,pom[j].getNick(), ilosc_old);
		if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[i].getNick(), whichBattle);
        numerStolu++; 
//USUNIECIE GRZCZY SPAROWANYCH
        for(int x = j; x<ilosc-1;x++){
             pom2[x] = pom[x+1];
             pom[x] = pom2[x];
            }
        ilosc--;
        for(int x = i; x<ilosc-1;x++){
            pom2[x] = pom[x+1];
            pom[x] = pom2[x];
            }
        ilosc--; 
    }
//zapis do zmiennej pomocniczej ostatnich 4 graczy w tabeli
    for(int x = 0; x < 6; x++){
    pom_zapas[x] = pom[x];
    }
//    for(int x = 0; x < 6; x++){
//    	
//	}
		if(!czyGral(pom[0],pom[1]) && !czyGral(pom[2],pom[3]) && !czyGral(pom[4],pom[5])){
			cout<<"zaczalem kombinowanie 1";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 1, 2, 3, 4, 5);
		}
		else if(!czyGral(pom[0],pom[1]) && !czyGral(pom[2],pom[4]) && !czyGral(pom[3],pom[5])){
			cout<<"zaczalem kombinowanie 2";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 1, 2, 4, 3, 5);
		}
		else if(!czyGral(pom[0],pom[1]) && !czyGral(pom[2],pom[5]) && !czyGral(pom[3],pom[4])){
			cout<<"zaczalem kombinowanie 3";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 1,2,5,3,4);
		}
		else if(!czyGral(pom[0],pom[2]) && !czyGral(pom[1],pom[3]) && !czyGral(pom[4],pom[5])){
			cout<<"zaczalem kombinowanie 4";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0,2,1,3,4,5);
		}
		else if(!czyGral(pom[0],pom[2]) && !czyGral(pom[1],pom[4]) && !czyGral(pom[3],pom[5])){
			cout<<"zaczalem kombinowanie 5";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0,2,1,4,3,5);
		}
		else if(!czyGral(pom[0],pom[2]) && !czyGral(pom[1],pom[5]) && !czyGral(pom[3],pom[4])){
			cout<<"zaczalem kombinowanie 6";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0,2,1,5,3,4);
		}
		else if(!czyGral(pom[0],pom[3]) && !czyGral(pom[1],pom[2]) && !czyGral(pom[4],pom[5])){
			cout<<"zaczalem kombinowanie 7";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 3, 1, 2,4,5);
		}
		else if(!czyGral(pom[0],pom[3]) && !czyGral(pom[1],pom[4]) && !czyGral(pom[2],pom[5])){
			cout<<"zaczalem kombinowanie 8";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 3, 1, 4,2,5);
		}
		else if(!czyGral(pom[0],pom[3]) && !czyGral(pom[1],pom[5]) && !czyGral(pom[2],pom[4])){
			cout<<"zaczalem kombinowanie 9";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 3, 1,5,2,4);
		}
		else if(!czyGral(pom[0],pom[4]) && !czyGral(pom[1],pom[2]) && !czyGral(pom[3],pom[5])){
			cout<<"zaczalem kombinowanie 10";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 4,1,2,3,5);
		}
		else if(!czyGral(pom[0],pom[4]) && !czyGral(pom[1],pom[3]) && !czyGral(pom[2],pom[5])){
			cout<<"zaczalem kombinowanie 11";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 4,1,3,2,5);
		}
		else if(!czyGral(pom[0],pom[4]) && !czyGral(pom[1],pom[5]) && !czyGral(pom[2],pom[3])){
			cout<<"zaczalem kombinowanie 12";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 4,1,5,2,3);
		}
		else if(!czyGral(pom[0],pom[5]) && !czyGral(pom[1],pom[2]) && !czyGral(pom[3],pom[4])){
			cout<<"zaczalem kombinowanie 13";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 5,1,2,3,4);
		}
		else if(!czyGral(pom[0],pom[5]) && !czyGral(pom[1],pom[3]) && !czyGral(pom[2],pom[4])){
			cout<<"zaczalem kombinowanie 14";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 5,1,3,2,4);
		}
		else if(!czyGral(pom[0],pom[5]) && !czyGral(pom[1],pom[4]) && !czyGral(pom[2],pom[3])){
			cout<<"zaczalem kombinowanie 15";
			kombinowanie(table, pom, paring_zapas, 0, ilosc_old, whichBattle, 0, 5,1,4,2,3);
		}
		cout<<endl;
		
		paring[0][numerStolu] = paring_zapas[0][0];
		paring[1][numerStolu] = paring_zapas[1][0];
		numerStolu++;
		paring[0][numerStolu] = paring_zapas[0][1];
		paring[1][numerStolu] = paring_zapas[1][1];
		numerStolu++;
		paring[0][numerStolu] = paring_zapas[0][2];
		paring[1][numerStolu] = paring_zapas[1][2];
	//wYPIS PARINGOW
   	numerStolu = 1;
   	printf("+--BITWA-%d--+", whichBattle);
   	printf("+--PARINGI--+\n");
	printf("|NrS|--Gracz 1--|--Gracz 2--|\n");
	printf("+---+-----------+-----------+\n");
    for(int x = 0; x<(ilosc_old/2);x++){
    	printf("| %d |%10s | %10s |\n", numerStolu, szukajNickGracza(paring[0][x], lista).c_str(),szukajNickGracza(paring[1][x], lista).c_str());
        numerStolu++;
    }
	cout<<"Pauza: "<<pauzaName<<endl;
    return true;
}
//void kombinowanie(CGracz *table, CGracz pomocnicza[], int paringiWsk[][2], int numStolu, int ilosc_old, int whichBattle, int g1, int g2, int g3, int g4){
void kombinowanie(CGracz *table, CGracz pomocnicza[], int paringiWsk[][3], int numStolu, int ilosc_old, int whichBattle, int g1, int g2, int g3, int g4, int g5, int g6){
	int dodatkowa;
		paringiWsk[0][0] = pomocnicza[g1].getId();
	    paringiWsk[1][0] = pomocnicza[g2].getId();
	//    numStolu++;
	    paringiWsk[0][1] = pomocnicza[g3].getId();
	    paringiWsk[1][1] = pomocnicza[g4].getId();
	    
	    paringiWsk[0][2] = pomocnicza[g5].getId();
	    paringiWsk[1][2] = pomocnicza[g6].getId();
	        
		dodatkowa = szukajGracza(table ,pomocnicza[g1].getNick(), ilosc_old);
		if(dodatkowa>=0) (table+dodatkowa)->addPrzeciwnik(pomocnicza[g2].getNick(), whichBattle);
		dodatkowa = szukajGracza(table ,pomocnicza[g2].getNick(), ilosc_old);
		if(dodatkowa>=0) (table+dodatkowa)->addPrzeciwnik(pomocnicza[g1].getNick(), whichBattle);
			
		dodatkowa = szukajGracza(table ,pomocnicza[g3].getNick(), ilosc_old);
		if(dodatkowa>=0) (table+dodatkowa)->addPrzeciwnik(pomocnicza[g4].getNick(), whichBattle);	
		dodatkowa = szukajGracza(table ,pomocnicza[g4].getNick(), ilosc_old);
		if(dodatkowa>=0) (table+dodatkowa)->addPrzeciwnik(pomocnicza[g3].getNick(), whichBattle);
		
		dodatkowa = szukajGracza(table ,pomocnicza[g5].getNick(), ilosc_old);
		if(dodatkowa>=0) (table+dodatkowa)->addPrzeciwnik(pomocnicza[g6].getNick(), whichBattle);	
		dodatkowa = szukajGracza(table ,pomocnicza[g6].getNick(), ilosc_old);
		if(dodatkowa>=0) (table+dodatkowa)->addPrzeciwnik(pomocnicza[g5].getNick(), whichBattle);
}
string szukajNickGracza(int id, spisGraczy lista[]){
	string szukanyNick = "nie ma";
	szukanyNick = lista[id-1].name;
    return szukanyNick;
}
bool czyGral(CGracz pier, CGracz dwa){
    bool odp = false;
    int leng = BITWY;
    for (int i = 0; i < leng-1; i++){
        if (pier.getPrzeciwnik(i) == dwa.getNick()) {
       		odp = true;	
       		return odp;
		}
        else odp = false;
    }
    return odp;
}
int szukajGracza(CGracz *table, string nickSzuk, int ilosc){
    int numGracza = -1;
    for(int i=0;i<ilosc-1;i++){
           if((table+i)->getNick() == nickSzuk) numGracza = i; 
        }
    return numGracza;
}










