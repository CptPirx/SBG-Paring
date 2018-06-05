/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

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

void Wypis_Graczy (CGracz *table, int ilosc);
void Sortowanie(CGracz *table, int ilosc );
bool Paring(CGracz *table, int ilosc, int whichBattle, spisGraczy lista[]);
string szukajNickGracza(int id, spisGraczy lista[]);
bool czyGral(CGracz pier, CGracz dwa);
int szukajGracza(CGracz *table, string nickSzuk, int ilosc);

int main()
{
    int ilosc_graczy;
    
        cout<<"podaj liczbe graczy"<<endl;
        cin>>ilosc_graczy;
        //WCZYTANIE GRACZY
        CGracz *table = (CGracz*) new char[sizeof(CGracz)*ilosc_graczy];
        spisGraczy lista[ilosc_graczy];
        for(int i=0;i<ilosc_graczy;i++){
            int id;
            string imie, nazwisko, nick; 
            cout<<"Dane gracza: ";
            //cin>>nick>>imie>>nazwisko;
            //new (table+i) CGracz(i+1,imie,nazwisko,nick);
            cin>>nick;
            new (table+i) CGracz(i+1,nick);
            lista[i].id=i+1;
            lista[i].name=nick;
        }
        //WYPISYWANIE GRACZY
        Wypis_Graczy(table, ilosc_graczy);
        int numBitwy = 0;
        
    while(1){
        //PARING
        Paring(table, ilosc_graczy, numBitwy, lista);
        //WYPISYWANIE GRACZY
        Wypis_Graczy(table, ilosc_graczy);
        //DODAWANIE PUNKTOW
        for(int i=0;i<ilosc_graczy;i++){
            int idToAdd, VPtoAdd, GPtoAdd, whichBattle;
            string nickToAdd;
            cout<<"Podaj nazwe gracza, VP, GP: ";
///            cin>> VPtoAdd;
///            cout<<"dodano pkt"<<endl;
///           (table+i)->addPoints(VPtoAdd, VPtoAdd, numBitwy);           
			cin>> nickToAdd >> VPtoAdd >> GPtoAdd;
			idToAdd = szukajGracza(table, nickToAdd, ilosc_graczy+1);
            (table+idToAdd)->addPoints(VPtoAdd, GPtoAdd, numBitwy);
        }
        //SORTOWANIE GRACZY
        Sortowanie(table, ilosc_graczy);
        //WYPISYWANIE GRACZY
		cout<<"WYNIKI: "<<endl;
        Wypis_Graczy(table, ilosc_graczy);
        numBitwy++;
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
    int paring_zapas[2][2];    
    string pauzaName = " ";
    CGracz pom[ilosc];
    int ilosc_old = ilosc, ilosc_zap = ilosc;
    int graczyDoPom = 1;
    CGracz pom2[ilosc-1];
    CGracz pom_zapas[4];
    //cout<<"tablica pom"<<endl;
    for(int x = 0; x<ilosc; x++){
        pom[x] = *(table+x);
    }
//ogarniecie pauzuj¹cego    
    if (ilosc%2 != 0) {
    	//cout<<"nieparzyscie"<<endl;
        i = ilosc-1;
        ilosc_zap--;
        bool pauza = false;
        CGracz pom2[ilosc-1];
       // cout<<"tablica pom2"<<endl;
        for(int x = 0; x<ilosc-1; x++){
            pom2[x] = pom[x];
            }
        while(!pauza && i>=0){
          if((table + i)->getPauza() == false){
           /// cout<<"znaleziono pauzujacego"<<endl;
			pauza = true;
			///cout<<"ustawia pauze dla gracza"<<endl;
            (table + i)->setPauza(true);
    
            pauzaName = (table + i)->getNick();
            ///cout<<"usuwanie pauzujacego z tab. pom."<<endl;
            for(int x = i; x<ilosc-1;x++){
                 pom2[x] = pom[x+1];
                 pom[x] = pom2[x];
                }
            ilosc--;
            }  else i--;
        }
//        cout<<"wypisanie po usunieciu pauzy"<<endl;
//        for(int i=0;i<ilosc;i++){
//            cout<<i+1;
//            pom[i].Wypisz();
//        }
        cout<<"wypisano"<<endl;
    //cout<<"wszytko spoko z pauzuj¹cym"<<endl;   
    };
//ustalenie paringów z wy³aczeniem ostatnich 4 graczy
    while(ilosc>4){
//    	cout<<"jacy gracze zostali:"<<endl;
//        for(int x=0;x<ilosc;x++){
//            cout<<x+1;
//            pom[x].Wypisz();
//        }
 //       cout<<"wypisano"<<endl;
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
            
		paring[0][numerStolu] = pom[i].getId();
        paring[1][numerStolu] = pom[j].getId();
           
//        cout<<"dodanie przeciwników do tablic"<<endl; 
        pomocnicza = szukajGracza(table ,pom[i].getNick(), ilosc_old);
        //cout<<"pom: "<<pomocnicza<<endl;
		//cout<<"nick1: "<<pom[i].getId()<<endl;
		//cout<<"nick2: "<<pom[j].getId()<<endl;  
        if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[j].getNick(), whichBattle);
        pomocnicza = szukajGracza(table ,pom[j].getNick(), ilosc_old);
        //cout<<"pom: "<<pomocnicza<<endl;             
		if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[i].getNick(), whichBattle);
			
//        cout<<"dodano"<<endl; 
        numerStolu++;        
//        cout<<"usuwanie graczy z tab.pom."<<endl; 
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
////        cout<<"usunieto"<<endl;  
    }
    
    //zapis do zmiennej pomocniczej ostatnich 4 graczy w tabeli
    for(int x = 0; x < 4; x++){
    pom_zapas[x] = pom[x];
    }
//----------------------------------------------------------------------------------------//    
// parowanie dla ostatnich graczy (usun komentarze tez przed klamra troche nizej, ale tak tez dziala)
//----------------------------------------------------------------------------------------//
//    graczyDoPom = 0;
//    bool daRade = true;
//    int iloscPom = ilosc;
//// sprawdzenie czy da rade bez kombinowania
//	while(iloscPom > 0){
//		i=0;
//        j=i+1;
//		while(czyGral(pom[i],pom[j])) {
//	        j++;
//	        if (j >= ilosc - 1){
//	            cout<<"nie da³o rady za "<< graczyDoPom+1<<" razem"<<endl;
//	            daRade = false;
//	            graczyDoPom++;
//			}
//	    }
//	    for(int x = j; x<ilosc-1;x++){
//	             pom2[x] = pom[x+1];
//	             pom[x] = pom2[x];
//	            }
//	    iloscPom--;
//	        for(int x = i; x<ilosc-1;x++){
//	            pom2[x] = pom[x+1];
//	            pom[x] = pom2[x];
//	            }
//	    iloscPom--; 
//	}	
//// jesli da rade to parujemy
//	for(int x = 0; x < 4; x++){ //przywrocenie starej tablicy
//    	pom[x] = pom_zapas[x];
//    }	
//	if(daRade){	
//	if(true){
//		while(ilosc > 0){
//			i=0;
//	        j=i+1;
//			while(czyGral(pom[i],pom[j])) {
//		    	j++;    
//		    }
//		    paring[0][numerStolu] = pom[i].getNick();
//	        paring[1][numerStolu] = pom[j].getNick();
//	           
//	        cout<<"dodanie przeciwników do tablic"<<endl; 
//	        pomocnicza = szukajGracza(table ,pom[i].getNick(), ilosc_old);
//	        //cout<<"pom: "<<pomocnicza<<endl;
//			//cout<<"nick1: "<<pom[i].getNick()<<endl;
//			//cout<<"nick2: "<<pom[j].getNick()<<endl;  
//	        if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[j].getNick(), whichBattle);
//	        pomocnicza = szukajGracza(table ,pom[j].getNick(), ilosc_old);
//	        //cout<<"pom: "<<pomocnicza<<endl;             
//			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[i].getNick(), whichBattle);
//				
//	        cout<<"dodano"<<endl; 
//	        numerStolu++;        
//	        cout<<"usuwanie graczy z tab.pom."<<endl; 
//		    for(int x = j; x<ilosc-1;x++){
//		             pom2[x] = pom[x+1];
//		             pom[x] = pom2[x];
//		            }
//		    ilosc--;
//		        for(int x = i; x<ilosc-1;x++){
//		            pom2[x] = pom[x+1];
//		            pom[x] = pom2[x];
//		            }
//		    ilosc--;
//		}
//	}
//// jesli nie da rady to kombinujemy
//	else {
		if(!czyGral(pom[0],pom[1]) && !czyGral(pom[2],pom[3])){
			paring[0][numerStolu] = pom[0].getId();
	        paring[1][numerStolu] = pom[1].getId();
	        numerStolu++;
	        paring[0][numerStolu] = pom[2].getId();
	        paring[1][numerStolu] = pom[3].getId();
	        
			pomocnicza = szukajGracza(table ,pom[0].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[1].getNick(), whichBattle);
			pomocnicza = szukajGracza(table ,pom[1].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[0].getNick(), whichBattle);	
			pomocnicza = szukajGracza(table ,pom[2].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[3].getNick(), whichBattle);	
			pomocnicza = szukajGracza(table ,pom[3].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[2].getNick(), whichBattle);				
		}
		else if(!czyGral(pom[0],pom[2]) && !czyGral(pom[1],pom[3])){
			paring[0][numerStolu] = pom[0].getId();
	        paring[1][numerStolu] = pom[2].getId();
	        numerStolu++;
	        paring[0][numerStolu] = pom[1].getId();
	        paring[1][numerStolu] = pom[3].getId();
	        
			pomocnicza = szukajGracza(table ,pom[0].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[2].getNick(), whichBattle);
			pomocnicza = szukajGracza(table ,pom[2].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[0].getNick(), whichBattle);	
			pomocnicza = szukajGracza(table ,pom[1].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[3].getNick(), whichBattle);	
			pomocnicza = szukajGracza(table ,pom[3].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[1].getNick(), whichBattle);	
		}
		else if(!czyGral(pom[0],pom[3]) && !czyGral(pom[1],pom[2])){
			paring[0][numerStolu] = pom[0].getId();
	        paring[1][numerStolu] = pom[3].getId();
	        numerStolu++;
	        paring[0][numerStolu] = pom[1].getId();
	        paring[1][numerStolu] = pom[2].getId();
	        
			pomocnicza = szukajGracza(table ,pom[0].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[3].getNick(), whichBattle);
			pomocnicza = szukajGracza(table ,pom[3].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[0].getNick(), whichBattle);	
			pomocnicza = szukajGracza(table ,pom[2].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[1].getNick(), whichBattle);	
			pomocnicza = szukajGracza(table ,pom[1].getNick(), ilosc_old);
			if(pomocnicza>=0) (table+pomocnicza)->addPrzeciwnik(pom[2].getNick(), whichBattle);
		}
//	}
	
   	
    
//    cout<<"Wypisanie paringów"<<endl;    
   	numerStolu = 1;
   	printf("+--PARINGI--+\n");
	printf("|NrS|--Gracz 1--|--Gracz 2--|\n");
	printf("+---+-----------+-----------+\n");
    for(int x = 0; x<(ilosc_old/2);x++){
 //   	printf("| %d |%d | %d |\n", numerStolu, paring[0][x], paring[1][x]);
    	printf("| %d |%10s | %10s |\n", numerStolu, szukajNickGracza(paring[0][x], lista).c_str(),szukajNickGracza(paring[1][x], lista).c_str());
   //     cout<<numerStolu<< " "<< szukajNickGracza(paring[0][x], lista))<< " "<< szukajNickGracza(paring[1][x], lista)<<endl;
        numerStolu++;
    }
	cout<<"Pauza: "<<pauzaName<<endl;
//    pomocnicza = szukajGracza(table ,"pie", ilosc_old);
//    for(int x = 0; x<=4 ; x++){
//        cout<<(table+pomocnicza)->getPrzeciwnik(x)<<" ";
//    }
//    cout<<endl;
    return true;
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
            //if((table+i)->getNick() == nickSzuk) numGracza = (table+i)->getID();
           if((table+i)->getNick() == nickSzuk) numGracza = i; 
        }
    return numGracza;
}










