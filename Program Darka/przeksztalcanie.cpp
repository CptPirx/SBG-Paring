/******************************************************************************

                              DARIUSZ S. SKOWRONSKI
               Program podlicza punkty na rzecz Ligi Pomorskiej
			

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

enum stan{
	CZEKAM_NA_GRACZA,
	ODCZYT_NICK_TUR,
	ODCZYT_ID,
	ODCZYT_IMIE,
	ODCZYT_NAZWISKO,
	ODCZYT_NICK
};
string przeksztalcanie(){
	
	fstream plikDaneLO;
    char a[255];
    string graczeLO[2][25];
    string IDLO, Imie, Nazwisko, Nick;
    char pomocniczyNickTur[63];
    char pomocniczyIDLO[63];
    char pomocniczyImie[63];
    char pomocniczyNazwisko[63];
    char pomocniczyNick[63];
    stan stanOdczytu = CZEKAM_NA_GRACZA;
    int j = 0;
    int x = 0;
    
    plikDaneLO.open("DaneLO.txt", ios::in );
    if(plikDaneLO.good() == true)
    {
    	int i=0;
		while( !plikDaneLO.eof() )
        {
        	//getline(  plikDaneLO , graczeLO[i]); 
			//cout<<graczeLO[i]<<" index: "<<i<<endl;
			i++;      
			
			plikDaneLO.getline(  a , 255);
            stanOdczytu =  ODCZYT_NICK_TUR; 
            	
            	
            	for (int x = 0; x < 255; x++){
            		if(a[x] >= 'A' && a[x] <= 'z' && stanOdczytu == ODCZYT_NICK_TUR){
            			pomocniczyNickTur[j] = a[x];
            			j++;
					}
					if(a[x] == 32 && stanOdczytu == ODCZYT_NICK_TUR){						
						stanOdczytu=ODCZYT_ID;
						x++;
						j = 0;	
					}
            		if(a[x] > 32 && stanOdczytu == ODCZYT_ID){
            			pomocniczyIDLO[j] = a[x];
            			j++;
					}
					if(a[x] == 32 && stanOdczytu == ODCZYT_ID){						
						stanOdczytu=ODCZYT_IMIE;
						x++;
						j = 0;	
					}
					if(a[x] >= 'A' && a[x] <= 'z' && stanOdczytu ==ODCZYT_IMIE){
            			pomocniczyImie[j] = a[x];            			
						j++;
					}
					if(a[x] == 32 && stanOdczytu == ODCZYT_IMIE){						
						stanOdczytu=ODCZYT_NAZWISKO;
						x++;
						j = 0;	
					}
					if(a[x] >= 'A' && a[x] <= 'z' && stanOdczytu ==ODCZYT_NAZWISKO){
            			pomocniczyNazwisko[j] = a[x];            			
						j++;
					}
					if(a[x] == 32 && stanOdczytu == ODCZYT_NAZWISKO){						
						stanOdczytu=ODCZYT_NICK;
						x++;
						j = 0;	
					}
					if(a[x] >= 'A' && a[x] <= 'z' && stanOdczytu ==ODCZYT_NICK){
            			pomocniczyNick[j] = a[x];            			
						j++;						
					}
					if(a[x] == 32 && stanOdczytu ==ODCZYT_NICK){
						stanOdczytu = CZEKAM_NA_GRACZA;
					}
				} 
					graczeLO[0][x]= pomocniczyNickTur;
					IDLO = pomocniczyIDLO;
					Imie = pomocniczyImie;
					Nazwisko = pomocniczyNazwisko;
					Nick = pomocniczyNick;
					graczeLO[1][x]= IDLO + " " + Imie + " " + Nazwisko + " " + Nick;
				
					
				x++;					  	

				if(stanOdczytu == CZEKAM_NA_GRACZA){
					for(int z=0; z<63; z++)
					{
						pomocniczyIDLO[z] = 0;
						pomocniczyImie[z] = 0;
						pomocniczyNazwisko[z] = 0;
						pomocniczyNick[z] = 0;
					}
				};
				
				           	
			 
        }		
        plikDaneLO.close();
    }
	
   printf("\a");
   return graczeLO;
}



