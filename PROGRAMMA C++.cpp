#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//STRUCT
struct spesa
{
	string data;
	string categoria;
	string descrizione;
	int importo;
	
};

const int MAX=100;

//FUNZIONE MENU'
int menu();

//FUNZIONI CONTROLLO
int controllo_importo(spesa v[], int num_spese);
int controllo_data(string data);

//FUNZIONI GESTIONE STRUCT
int carica( spesa v[], int num_spese);
void visualizza(spesa v[], int num_spese);
void modifica_spesa();
void elimina_spesa();

// FUNZIONI FILE
void Crea_Record(spesa v[], int num_spese );
void Leggi_Record(spesa v[], int num_spese);
void Aggiorna_Record(spesa v[], int num_spese);
void Cancella_Record(spesa v[], int num_spese);

//MAIN 
int main ()
{   
	bool flag=false;
	int scelta, num_spese;
		do
	{
		cout<<"quante spese vuoi inserire?"<<endl;
		cin>>num_spese;
	} while (num_spese<0 || num_spese>MAX);

	spesa v[num_spese];


	do
	{
	scelta=menu();
	switch(scelta)
	 {
		case 1: 
		Crea_Record(v, num_spese);
		flag=true;
			break;

		case 2: if(flag)
		{
			Leggi_Record(v,  num_spese);
		}
			else
		{
			cout<<"prima devi caricare un record nel file"<<endl;
		}
			break;

		case 3: if(flag)
		{
			Aggiorna_Record(v,  num_spese);
		}
			else
		{
			cout<<"prima devi caricare un record nel file"<<endl;
		}
			break;

		case 4: if(flag)
		{
			Cancella_Record(v, num_spese);
		}
		else
		{
			cout<<"prima devi caricare un record nel file"<<endl;
		}
			break;
			
		case 5: cout<<"uscita dal programma"<<endl;
		    break;
		    
		default: cout<<"errore"<<endl;
	 } 
	 }
	 while (scelta!=5);
	 return 0;
 }

//MENU'
int menu()
{
	int scelta;
	do
	{
		cout<<"1)Crea un record"<<endl;
		cout<<"2)Leggi un record"<<endl;
		cout<<"3)Aggiorna un record"<<endl;
		cout<<"4)Cancella un record"<<endl;
		cout<<"5)Esci"<<endl;
		cin>>scelta;
	}
	while (scelta<1 || scelta>5);
	return scelta;
}

//CONTROLLO DATA E IMPOROTO
int controllo_importo(spesa v[], int num_spese)
{
   if(v[num_spese].importo<0)
   {
	return-1;
   }
   return 2;
}

int controllo_data( string data)
{
	int giorno=stoi(data.substr(0,2));
	int mese=stoi(data.substr(3,2));
	int anno=stoi(data.substr(6,4));
	
	//mese
	if(mese<1 || mese>12)
	{
		return -1;
	}
	
    //vettore giorni dei mesi
	int giorni_mesi[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	
	//anno bisestile
	if((anno%4==0 && anno%100!=0)||(anno%400==0))
	{
		giorni_mesi[1]=29;
	}
	
	//giorno
	if (giorno<1 || giorno>giorni_mesi[mese-1])
	{
		return -1;
	}
	
	return 2;
}

//CARICAMENTO SPESA
int carica (spesa v[], int num_spese)
{
	int contatore=0;
	ofstream file("spese.txt", ios::app);
	if(num_spese>MAX)
	{
		cout<<"non puoi piu' aggiungere spese"<<endl;
		return num_spese;
	}
	do
	{
	cout<<"DATA IN CUI E' STATA EFFETTUATA LA SPESA (gg/mm/aaaa):";
	getline(cin,v[num_spese].data);
	int controllo0=controllo_data(v[num_spese].data);
	if(controllo0==-1)
	{
		cout<<"errore hai inserito una data inesistente"<<endl;
		return contatore;
	}
	cout<<"CATEGORIA SPESA:";
	getline(cin, v[num_spese].categoria);
	cout<<"DESCRIZIONE SPESA";
	getline(cin, v[num_spese].descrizione);
	cout<<"IMPORTO SPESA";
	cin >> v[num_spese].importo;
	int controllo1=controllo_importo(v, num_spese);
	if(controllo1==-1)
	{
		cout<<"errore hai inserito un importo errato"<<endl;
		return contatore;
	}
	contatore++;
}while(contatore<num_spese);

	file<<v[num_spese].data<<" "<<v[num_spese].categoria<<" "<<v[num_spese].descrizione<<" "<<v[num_spese].importo<<endl;
	file.close();

	cout<<"Spesa aggiunta "<<endl;
	return num_spese+1;
}

//STAMPA SPESA
void visualizza(spesa v[], int num_spese)
{
	ifstream file("spese.txt");
	if(num_spese==0)
	{
		cout<<"non sono state effettuate spese"<<endl;
		return;
	}
	
	for(int i=0; i<num_spese; i++)
	{
		cout<<"DATA:"<<v[i].data<<endl;
		cout<<"CATEGORIA:"<<v[i].categoria<<endl;
		cout<<"DESCRIZIONE:"<<v[i].descrizione<<endl;
		cout<<"IMPORTO:"<<v[i].importo<<endl;
	}
	file.close();
}

//AGGIORNA SPESA
void modifica_spesa()
{

    ifstream file("spese.txt");
    ofstream temp("temp.txt");

    string cerca;
    bool trovato=false;
    cout<<"Descrizione della spesa da modificare: ";
    getline(cin,cerca);

    spesa s;
    string importoString;

    while(getline(file,s.descrizione,'|'))
	{

        if(s.descrizione==cerca)
        {

            trovato=true;

            cout<<"Nuova descrizione: ";
            getline(cin,s.descrizione);

            cout<<"Nuovo importo: ";
            cin>>s.importo;

            cout<<"Nuova data: ";
            cin>>s.data;
        }

        temp<<s.descrizione<<"|"
            <<s.importo<<"|"
            <<s.data<<endl;
    }

    file.close();
    temp.close();

    remove("spese.txt");
    rename("temp.txt","spese.txt");

    if(trovato)
      cout<<"Spesa modificata!";
    else
      cout<<"Spesa non trovata.";
}

//ELIMINA SPESA
void elimina_spesa(){

    ifstream file("spese.txt");
    ofstream temp("temp.txt");

    string cerca;
    bool trovato=false;

    cout<<"Descrizione spesa da eliminare: ";
    getline(cin,cerca);

    spesa s;

    while(getline(file,s.descrizione,'|')){

        if(s.descrizione!=cerca){
            temp<<s.descrizione<<"|"
                <<s.importo<<"|"
                <<s.data<<endl;
        }
        else{
            trovato=true;
        }
    }

    file.close();
    temp.close();

    remove("spese.txt");
    rename("temp.txt","spese.txt");

    if(trovato)
      cout<<"Spesa eliminata!";
    else
      cout<<"Spesa non trovata.";
}

//FUNZIONI FILE

//CREA UN FILE
void Crea_Record(spesa v[], int num_spese)
{ 
	carica(v, num_spese);
}


//AGGIORNA UN FILE
void Aggiorna_Record(spesa v[], int num_spese)
{
	modifica_spesa();
}

//VISUALIZZA UN FILE
void Leggi_Record(spesa v[], int num_spese)
{ 
	visualizza(v, num_spese);
}

//ELIMINA UN RECORD DAL FILE
void Cancella_Record(spesa v[], int num_spese)
{
	elimina_spesa();
}