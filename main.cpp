/// Progra III 
//Aqui se incluyen las liberias a usar
#include <iostream>
#include "mis_funciones.h"
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <Mmsystem.h>
#if defined(_MSC_VER)
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")
#endif

//#pragma comment(lib, "Winmm.lib")
#include <cstdlib> // contiene la funcion system("pause")
#include <string> 
#include<sstream>  
#include <locale.h> // Libreria que contiene la funcion setlocales
#include <cctype>
#include <bits/stdc++.h>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>

/// Aqui se definen las variables globales
std::string path ="c:\\lib\\voices\\"; //path de archivos de audio
std::string diccionario_file ="..\\diccionario.txt"; //path de archivo de diccionario
std::string user_profiles ="";//path de user profiles
int correlativo=200; //variable de correlativo global
std::string diccionario_a[5][1000]; //array de 5 columnas por 1000 filas
bool menu_sound=false;
//Se define estructura para cada idioma
struct Palabra {
    std::string espanol;
    std::string italiano;
    std::string frances;
    std::string aleman;
    std::string ingles;
};
//Se usa boost para funciones de cadenas

using namespace boost::algorithm;
using namespace std;

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  
int opc=0;

void Say(const char *txt)
{   
	printf("%s",txt);
}

void Say(int x,int y,const char *txt)
{   
	gotoxy(x,y);
	printf("%s",txt);
}

void Replicate(const char c,int can)
{
	for(int i=0;i<can;i++)
	 {
		printf("%c",c);	
	 }
} 

void ReplicateH(int x,int y,const char *c,int can)
{
	for(int i=0;i<can;i++)
	 {
		Say(x+i,y,c);	
	 }
}

void ReplicateV(int x,int y,const char *c,int can)
{
	for(int i=0;i<can;i++)
	 {
		Say(x,y+i,c);	
	 }
}

void Rectangle(int x,int y,int w,int h,const char *c)
{  
		ReplicateH(x,y,c,w);//fila 1
		ReplicateH(x,y+h,c,w);//fila 2
		ReplicateV(x,y,c,h);//col 1
		ReplicateV(x+w-1,y,c,h);//col 2
   
} 

void SetColorA(int color,int colorf)
{
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | colorf | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY );
}

void SetColorB(int color,int colorf)
{
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | colorf | BACKGROUND_INTENSITY );
}

void SetColorC(int color,int colorf)
{
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | colorf);
}


void TextColor(int color)
{
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); 
}



void MSGBOX(const char *m1,const char *m2)
{
     MessageBox(NULL,m1 ,m2,MB_ICONEXCLAMATION);
}


void Cls()
{
	system("cls");
}
//CLASE MENU 

MENU::MENU()
{
	con=0;
	COLOR=15;
	COLORB=21;
	OPC_SEL=1;
	ESPACIO=1;
}

MENU::~MENU()
{
}

void MENU::Set_Color(int color,int colorb)
{
	COLOR=color;
	COLORB=colorb;

}

void MENU::Add_Items(const char *txt, int index)
{
	Opc[index].id=index;
	sprintf(Opc[index].name,"%s",txt);
	con=con+1;
}

void MENU::Set_Space(int s)
{
	ESPACIO=s;
}

int MENU::Draw(int x,int y)
{   int tecla;
	bool Sel=false;
	int FILA;
	while(tecla!=13) 
	{
	FILA=y;	
	for(int i=1;i<con+1;i++)
	  {     SetColorA(COLOR,COLORB);
			
			if(OPC_SEL==i)
			{   
				SetColorA(15,2);
			}
			gotoxy(x,FILA);printf("%s",Opc[i].name);
			FILA=FILA+ESPACIO;
	  }
      SetColorC(15,0);
      
      tecla=_getch();  
      
	  switch ( tecla ) 
	  {     case 72://Arriba
	            OPC_SEL=OPC_SEL-1;
	            if(OPC_SEL<1)
	               {OPC_SEL=1;}
	  			break;
		    case 80://Abajo
	            OPC_SEL=OPC_SEL+1;
	            if(OPC_SEL>con)
	               {OPC_SEL=con;}
	  			break;
	  } 
      
	}
	
	return OPC_SEL;
}
void Ingresar()
{
  TextColor(12);  
  Rectangle(20,8,40,12,"%"); 
  
  SetColorA(2,22);  
  Say(28,10,"*** INGRESAR DATOS ***");
  int tec=getch();
  opc=0;
}
 
void Eliminar()
{
  TextColor(12);  
  Rectangle(20,8,40,12,":"); 
  
  SetColorA(2,22);  
  Say(28,10,"*** ELIMINAR DATOS ***");
  int tec=getch();
  opc=0;
}



MENU miMenu;
//pantalla completa
void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);

     CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo; 

    // Get console handle and get screen buffer information from that handle.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);

    // Get rid of the scrollbar by setting the screen buffer size the same as 
    // the console window size.
    COORD new_screen_buffer_size;

    // screenBufferInfo.srWindow allows us to obtain the width and height info 
    // of the visible console in character cells.
    // That visible portion is what we want to set the screen buffer to, so that 
    // no scroll bars are needed to view the entire buffer.
    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - 
    screenBufferInfo.srWindow.Left + 1; // Columns
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - 
    screenBufferInfo.srWindow.Top + 1; // Rows

    // Set new buffer size
    SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);

    //std::cout << "There are no scrollbars in this console!" << std::endl;

    //return 0;
  //	return;
}

 
//Funcion para generar audios desde AWS Polly y luego de descargarlo en MP3 lo convierte en WAV
string aws_audio(int index, string word, int wordindex, string palabra){
	std::string comando; 
	std::string fullPath = path;
	std::string genfullPath = path;
	
	//cout<<"va a generar el archivo desde polly"<<endl;
	//system("pause");
	//En base a la sesleccion asigna la carpeta del idioma
	if (index==0) fullPath +="spanish\\"; //Espa√±ol
	if (index==1) fullPath+="english\\"; //Ingles
	if (index==2) fullPath+="german\\"; //Aleman
	if (index==3) fullPath+="french\\"; //Frances
	if (index==4) fullPath+="italian\\"; //Italiano
	//Toma el path generico y se guarda por aparte
	genfullPath=fullPath; //
	stringstream ss;  
	///////ss<<wordindex+1;  
	ss<<wordindex;  
	string s;  
	ss>>s; 
	//string str = to_string(wordindex;
	//evalua el idioma para construir el string
	//comando="aws polly synthesize-speech --output-format mp3 --voice-id ";
	if (index==0) comando +="Penelope"; //Espa√±ol
	if (index==1) comando +="Salli"; //Ingles
	if (index==2) comando +="Vicki"; //Aleman
	if (index==3) comando +="Lea"; //Frances
	if (index==4) comando +="Bianca"; //Italiano
	
	fullPath+=s;
	fullPath+=".mp3";
	comando+=" --text '";
	comando+=palabra;
	comando+="' ";
	comando+=fullPath;
	comando+=" > nul"; //volver a poner para capturar el output
	//cout<<" ya debio haber generado el archivo"<<endl;
	//cout<<" path: "<<fullPath<<endl;
	//cout<<" el comando es: "<<comando<<endl;
	//cout<<comando<<endl;
	//system("pause");
	//std::string str;
	const char * c = comando.c_str();
	//manda a generar el audio de aws
	system(c);
	//cout<<"el path completo es: "<<s<<endl;
	comando="ffmpeg -hide_banner -log_level error -i ";
	comando+=genfullPath;
	comando+=s;
	comando+=".mp3 ";
	comando+=genfullPath;
	comando+=s;
	comando+=".wav > nul";
	//cout<<comando<<endl;
	//system("pause");
	const char * c1 = comando.c_str();
	//Convierte mp3 a Wav
	system(c1);
	//devuelve  el valor en la rutina
	correlativo+=1;
	genfullPath+=s;
	genfullPath+=".wav";
	return genfullPath;
	//comando=palabra+".mp3";
	//const char * c2 = comando.c_str();
	
	//system(c2);
	//system("pause");
	//word=403;	
}

//Funcion para reproducir sonidos
void play(int index, string word, string palabra){
	string iresp;
	std::string fullPath = path;
	if(word=="404") word+="1";
	//cout<<" inicia rutina de reproduccion de audio"<<endl;
	//cout<<word<<" la palabra "<<palabra<<endl;
	//system("pause");
	//En base a la sesleccion asigna la carpeta del idioma
	if (index==0) fullPath +="spanish\\"; //Espa√±ol
	if (index==1) fullPath+="english\\"; //Ingles
	if (index==2) fullPath+="german\\"; //Aleman
	if (index==3) fullPath+="french\\"; //Frances
	if (index==4) fullPath+="italian\\"; //Italiano
	
	fullPath += word;
	fullPath += ".wav";
	string archivo=fullPath;
	
	string nombreArchivo = archivo;
	ifstream archivo1(nombreArchivo.c_str());
	//file = fopen(archivo, "w");
	if(archivo1){
		//Todo OK y se reproduce el archivo
	}
	else {
		
		//cout<<" no aparece el archivo"<<" Correlativo es "<<correlativo<<" y la palabra es: "<<palabra<<endl;
		//system("pause");
        iresp=aws_audio(index,word,correlativo,palabra);
		stringstream ss; 
   		//string str = "7";
	    int num;
	   	ss << word;
	   	ss >> num;
	   	
		//iresp=aws_audio(index,word,num,palabra);
		//No lo encontr√≥
		fullPath=iresp;
		//fullPath+=iresp;
		//fullPath+=".wav";
		//cout<<fullPath<<" path del archivo -- respuesta de funcion: "<<iresp<<endl;
		//system("pause");
		//system("cls");
	}
	const char *folder = fullPath.c_str();
	int ires;
	//cout<<"path ->"<<folder<<endl;
	ires=PlaySound(folder, NULL, SND_FILENAME); //SND_FILENAME or SND_LOOP
	//cout<<"respuesta: "<<ires<<endl;
}

//sirvio para generar los audios en batch
void Modificar()
{
	string s;
	std::vector<Palabra> palabras;
    std::ifstream archivo("palabras.txt");
    std::string palabra;
    std::string palabra_traducida;
	
	//carga el diccionario
  	//Apertura de archivo y lectura de datos
    if (archivo.is_open()) {
        std::string linea;
        
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            //convierto todo a mayusculas para comparar
            
            Palabra palabra;
            //palabra=to_upper(palabra);
			std::getline(ss, palabra.espanol, ',');
            std::getline(ss, palabra.italiano, ',');
            std::getline(ss, palabra.frances, ',');
            std::getline(ss, palabra.aleman, ',');
            std::getline(ss, palabra.ingles, ',');
            palabras.push_back(palabra);
        }
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo del diccionario, por favor consulte con el administrador" << std::endl;
        system("pause");
        //return 1;
    }
    
    
    //recorre el diccionario y envia la reproduccion del audio
    for (int i = 0; i < palabras.size(); i++) {
	    	//cout<<"palabra # "<<i<<"-"<<palabras[i].ingles<<"-"<<" con trim -";
	    stringstream ss;  
	  	ss<<i;  
	  	ss>>s; 
		std::string paword1=palabras[i].espanol;
		std::string paword2=palabras[i].ingles;
		std::string paword3=palabras[i].aleman;
		std::string paword4=palabras[i].frances;
		std::string paword5=palabras[i].italiano;

		boost::trim_left( paword1 );
		boost::trim_left( paword2 );
		boost::trim_left( paword3 );
		boost::trim_left( paword4 );
		boost::trim_left( paword5 );
		
		boost::trim_right( paword1 );
		boost::trim_right( paword2 );
		boost::trim_right( paword3 );
		boost::trim_right( paword4 );
		boost::trim_right( paword5 );
		
        std::cout << palabras[i].espanol << std::endl;
        cout<<"****************palabra->"<<paword1<<" indice: "<<s<<endl;
		play(0, s, paword1);
        
		std::cout << palabras[i].ingles << std::endl;
        cout<<"****************palabra->"<<paword2<<" indice: "<<s<<endl;
		play(1, s, paword2);
        
        std::cout << palabras[i].aleman << std::endl;
        cout<<"****************palabra->"<<paword3<<" indice: "<<s<<endl;
		play(2, s, paword3);
 		
        std::cout << palabras[i].frances << std::endl;
        cout<<"****************palabra->"<<paword4<<" indice: "<<s<<endl;
		play(3, s, paword4);
  		
        std::cout << palabras[i].italiano << std::endl;
        cout<<"****************palabra->"<<paword5<<" indice: "<<s<<endl;
		play(4, s, paword5);
        
}
}




//Declarar el variable palabras de tipo PALABRA
int buscarpalabra(){
	//Crea menu de busqueda
	
	
	//se usa para poder utilizar los caracteres como Ò, tildes, etc.
	setlocale(LC_ALL, ""); 
	
	std::vector<Palabra> palabras;
    std::ifstream archivo("palabras.txt");
    std::string palabra;
    std::string palabra_traducida;
	bool palabra_encontrada = false;
    int indice_idioma;
    int idioma_origen;
	std::string paword1;
	std::string paword2;
	std::string paword3;
	std::string paword4;
	std::string paword5;
	string s;  
	
	
	//Apertura de archivo y lectura de datos
    if (archivo.is_open()) {
        std::string linea;
        
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            //convierto todo a mayusculas para comparar
            
            Palabra palabra;
            //palabra=to_upper(palabra);
			std::getline(ss, palabra.espanol, ',');
            std::getline(ss, palabra.italiano, ',');
            std::getline(ss, palabra.frances, ',');
            std::getline(ss, palabra.aleman, ',');
            std::getline(ss, palabra.ingles, ',');
            palabras.push_back(palabra);
        }
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo del diccionario, por favor consulte con el administrador" << std::endl;
        system("pause");
        return 1;
    }
    do {
	
    //Busqueda de palabras en el archivo
	
	//Crea el menu y ciclo para traducir palabras
		system("cls");
		system("color 0a");
		gotoxy(50,9);
		//cout<<"                                                         Para salir presione [0]"
		gotoxy(50,10);
		cout<<"######################################################################";
		gotoxy(50,11);
		cout<<"##                      Menu Traducir                                #"<<endl;
		gotoxy(50,12);
		cout<<"#############################################Para Salir presione ESC #"<<endl;
		gotoxy(50,13);
		cout<<""<<endl;
		gotoxy(50,14);
		//int tec=getch();
		//cout<<"             [1] Traducir palabra                                      "<<endl;
	    std::cout << "  Ingrese la palabra a buscar: ";
	    int palint=getch();
	    if (palint==27) return 0;
	    palabra_encontrada = false;
		gotoxy(82,14);
        std::cin >> palabra;
	    boost::to_upper(palabra);
	    bool idioma_valido = false;
	    while (idioma_valido == false){
	    	gotoxy(50,16);
		    std::cout << "Ingrese el idioma al que desea traducir: "<<endl;
		    gotoxy(50,17);
			std::cout <<"[1] EspaÒol [2] InglÈs [3] Alem·n [4] FrancÈs [5] Italiano [0] Salir";
		    gotoxy(50,18);
		    int palint=getch();
	    if ( palint==27) return 0;
	    	std::cin >> indice_idioma;
	    	if(indice_idioma > 5) idioma_valido=false;
	    	else idioma_valido=true;
	    }
	    gotoxy(50,19);
	    if(indice_idioma > 0) {
		
		    cout<<"La palabra se escribe: ";
			//cout<<"la palabra es: -"<<palabra<<"-"<<endl;
		    for (int i = 0; i < palabras.size(); i++) {
		    	//cout<<"palabra # "<<i<<"-"<<palabras[i].ingles<<"-"<<" con trim -";
		    	
				std::string paword1=palabras[i].espanol;
				std::string paword2=palabras[i].ingles;
				std::string paword3=palabras[i].aleman;
				std::string paword4=palabras[i].frances;
				std::string paword5=palabras[i].italiano;
				//Se remueven los espacios a la izquierda de cada palabra
				boost::trim_left( paword1 );
				boost::trim_left( paword2 );
				boost::trim_left( paword3 );
				boost::trim_left( paword4 );
				boost::trim_left( paword5 );
				
				//Se convierten a mayusculas las palabras para comparar
				boost::to_upper( paword1 );
				boost::to_upper( paword2 );
				boost::to_upper( paword3 );
				boost::to_upper( paword4 );
				boost::to_upper( paword5 );
				
				//string word = i;
				stringstream ss;  
			  	ss<<i;  
			  	ss>>s; 
			  	
			  	
				//cout<<paword<<"-"<<endl;
				if (paword1 == palabra) {
					//cout<<"entro a buscar en espaÒol..."<<endl;
					//	system("pause");
					palabra_encontrada = true;
		            switch (indice_idioma) {
		                case 1:
		                    std::cout << palabras[i].espanol << std::endl;
		                    palabra_traducida=palabras[i].espanol;
		                    break;
		                case 2:
		                    std::cout << palabras[i].ingles << std::endl;
		                    palabra_traducida=palabras[i].ingles;
		                    break;
		                case 3:
		                    std::cout << palabras[i].aleman << std::endl;
		                    palabra_traducida=palabras[i].aleman;
		                    break;
		                case 4:
		                    std::cout << palabras[i].frances << std::endl;
		                    palabra_traducida=palabras[i].frances;
		                    break;
		                case 5:
		                    std::cout << palabras[i].italiano << std::endl;
		                    palabra_traducida=palabras[i].italiano;
		                    break;
		                default:
		                    std::cout << "Indice de idioma invalido" << std::endl;
		                    break;
		                    
		            	}break;
					}
					else if (paword2 == palabra){
						palabra_encontrada = true;
		            switch (indice_idioma) {
		                case 1:
		                    std::cout << palabras[i].espanol << std::endl;
		                    palabra_traducida=palabras[i].espanol;
		                    break;
		                case 2:
		                    std::cout << palabras[i].ingles << std::endl;
		                    palabra_traducida=palabras[i].ingles;
		                    break;
		                case 3:
		                    std::cout << palabras[i].aleman << std::endl;
		                    palabra_traducida=palabras[i].aleman;
		                    break;
		                case 4:
		                    std::cout << palabras[i].frances << std::endl;
		                    palabra_traducida=palabras[i].frances;
		                    break;
		                case 5:
		                    std::cout << palabras[i].italiano << std::endl;
		                    palabra_traducida=palabras[i].italiano;
		                    break;
		                default:
		                    std::cout << "El numero de idioma colocado no es valido" << std::endl;
		                    break;
		                    
		            	}
		            	break;
		        	}
					else if (paword3 == palabra){
						palabra_encontrada = true;
		        	switch (indice_idioma) {
		                case 1:
		                    std::cout << palabras[i].espanol << std::endl;
		                    palabra_traducida=palabras[i].espanol;
		                    break;
		                case 2:
		                    std::cout << palabras[i].ingles << std::endl;
		                    palabra_traducida=palabras[i].ingles;
		                    break;
		                case 3:
		                    std::cout << palabras[i].aleman << std::endl;
		                    palabra_traducida=palabras[i].aleman;
		                    break;
		                case 4:
		                    std::cout << palabras[i].frances << std::endl;
		                    palabra_traducida=palabras[i].frances;
		                    break;
		                case 5:
		                    std::cout << palabras[i].italiano << std::endl;
		                    palabra_traducida=palabras[i].italiano;
		                    break;
		                default:
		                    std::cout << "El numero de idioma colocado no es valido" << std::endl;
		                    break;
		                    
		            	}
		            	break;
					}
					else if(paword4 == palabra){
						palabra_encontrada = true;
					switch (indice_idioma) {
		                case 1:
		                    std::cout << palabras[i].espanol << std::endl;
		                    palabra_traducida=palabras[i].espanol;
		                    break;
		                case 2:
		                    std::cout << palabras[i].ingles << std::endl;
		                    palabra_traducida=palabras[i].ingles;
		                    break;
		                case 3:
		                    std::cout << palabras[i].aleman << std::endl;
		                    palabra_traducida=palabras[i].aleman;
		                    break;
		                case 4:
		                    std::cout << palabras[i].frances << std::endl;
		                    palabra_traducida=palabras[i].frances;
		                    break;
		                case 5:
		                    std::cout << palabras[i].italiano << std::endl;
		                    palabra_traducida=palabras[i].italiano;
		                    break;
		                default:
		                    std::cout << "El numero de idioma colocado no es valido" << std::endl;
		                    break;
		                    
		            	}
		            	break;
					}
					//else 
					//if (palabras[i].ingles == palabra){
					if (paword5 == palabra){
						palabra_encontrada = true;
					switch (indice_idioma) {
		                case 1:
		                    std::cout << palabras[i].espanol << std::endl;
		                    palabra_traducida=palabras[i].espanol;
		                    break;
		                case 2:
		                    std::cout << palabras[i].ingles << std::endl;
		                    palabra_traducida=palabras[i].ingles;
		                    break;
		                case 3:
		                    std::cout << palabras[i].aleman << std::endl;
		                    palabra_traducida=palabras[i].aleman;
		                    break;
		                case 4:
		                    std::cout << palabras[i].frances << std::endl;
		                    palabra_traducida=palabras[i].frances;
		                    break;
		                case 5:
		                    std::cout << palabras[i].italiano << std::endl;
		                    palabra_traducida=palabras[i].italiano;
		                    break;
		                default:
		                    std::cout << "El numero de idioma colocado no es valido" << std::endl;
		                    break;
		                    
		            }
		            break;
				}
		   	 }
		   	 if(palabra_encontrada==false){
		   	 	gotoxy(50,18);
		   	 	cout<<"Su palabra no existe en el diccionario pero la encontraremos en linea..."<<endl;
		   	 	gotoxy(50,19);
		   	 	cout << "Ingrese el idioma original de la palabra [1] EspaÒol [2] InglÈs [3] Alem·n [4] FrancÈs [5] Italiano";
		   	 	gotoxy(50,20);
		   	 	cin>>idioma_origen;
		   	 	string idioma_traducir;
		   	 	string idioma_destino;
		   	 	if(idioma_origen ==1) idioma_traducir="es";
		   	 	if(idioma_origen ==2) idioma_traducir="en";
		   	 	if(idioma_origen ==3) idioma_traducir="de";
		   	 	if(idioma_origen ==4) idioma_traducir="fr";
		   	 	if(idioma_origen ==5) idioma_traducir="it";
		   	 	
		   	 	if(indice_idioma ==1) idioma_destino="es";
		   	 	if(indice_idioma ==2) idioma_destino="en";
		   	 	if(indice_idioma ==3) idioma_destino="de";
		   	 	if(indice_idioma ==4) idioma_destino="fr";
		   	 	if(indice_idioma ==5) idioma_destino="it";
		   	 	std::string comando; 
		   	 	comando="python translate.py --text ";
				comando+=palabra;
				comando+=" --target-language ";
				comando+=idioma_destino;
				comando+=" --api-key '123456asdfasdfaf' --src_lan ";
				comando+=idioma_traducir;
				comando+=" >output.txt";
				
		   	 	const char * c1 = comando.c_str();
		   	 	gotoxy(50,21);
		   	 	palabra_traducida=system(c1);
		   	 	std::ifstream archivo("output.txt");
		   	 	std::getline(archivo, palabra_traducida);
		   	 	palabra=system(c1);
		   	 	cout<<palabra_traducida<<endl;
		   	 	stringstream ss;
				ss<<correlativo;
				ss>>s; 
				
				} 
				//cout<<"veamos la palabra traducida antes del trim "<<palabra<<endl;
				boost::trim_left( palabra_traducida );
				//cout<<"veamos la palabra traducida"<<endl;
				//cout<<"el indice de la palabra es : "<<s<<"la palabra es: "<<palabra_traducida<<endl;
				//system("pause");
				play(indice_idioma-1, s, palabra_traducida);
		   gotoxy(50,23);
		   system("pause"); 
		   
			}
	} while(indice_idioma > 0);
   //if(indice_idioma!=0) buscarpalabra();
   return 0;
   //menu();	
}

void intro(){
	system("cls");
	gotoxy(50,10);
	cout<<"UNIVERSIDAD MARIANO GALVEZ DE GUATEMALA"<<endl;
	gotoxy(50,11);
	cout<<"FACULTAD DE INGENIERIA EN SISTEMAS"<<endl;
	gotoxy(50,12);
	cout<<"PROGRAMACION III"<<endl;
	gotoxy(30,14);
	cout<<"               ______                                                      ____                           "<<endl;
	gotoxy(30,15);
	cout<<"|`````````,  .~      ~.  |`````````, `````|`````       .'.       |        |                        ..'''' "<<endl;
	gotoxy(30,16);
	cout<<"|'''''''''  |          | |'''|'''''       |          .''```.     |        |______               .''       "<<endl;
	gotoxy(30,17);
	cout<<"|           |          | |    `.          |        .'       `.   |        |                  ..'          "<<endl;
	gotoxy(30,18);
	cout<<"|            `.______.'  |      `.        |      .'           `. |_______ |___________ ....''         "<<endl;
	
	gotoxy(50,30);
	cout<<"Kenny Amadeus Saenz        9989-19-05558";
	gotoxy(50,31);
	cout<<"Luis Adolfo Escobedo       9989-19-13040";
	gotoxy(50,32);
	cout<<"Jose Manuel Sanchez        9989-20-02386";
	gotoxy(50,33);
	cout<<"Erick Alfonso Juarez       9989-02-00061";
	gotoxy(40,37);
	cout<<"Recuerde que los audios deben estar en la carpeta c:\\lib\\voices\\ para mas informacion"<<endl;
	gotoxy(40,38);
	cout<<"             consulte el archivo readme.txt en la carpeta raiz del proyecto"<<endl;
	std::string fullPath="c:\\lib\\1000.wav";
		//cout<<fullPath;
		//system("pause");
		const char *folder = fullPath.c_str();
		int ires;
		//cout<<folder<<endl;
		//cout<<"path ->"<<folder<<endl;
		if (menu_sound==false) {
			ires=PlaySound(folder, NULL, SND_FILENAME);
			menu_sound=true;
		}
	//Sleep(5000);
}

//Funcion para imprimir el diccionario
void Diccionario(){
	//se usa para poder utilizar los caracteres como Ò, tildes, etc.
	setlocale(LC_ALL, ""); 
	string s;
	std::vector<Palabra> palabras;
    std::ifstream archivo("palabras.txt");
    std::string palabra;
    std::string palabra_traducida;
	int icont=12;
	//carga el diccionario
  	//Apertura de archivo y lectura de datos
    if (archivo.is_open()) {
        std::string linea;
        
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            //convierto todo a mayusculas para comparar
            
            Palabra palabra;
            //palabra=to_upper(palabra);
			std::getline(ss, palabra.espanol, ',');
            std::getline(ss, palabra.italiano, ',');
            std::getline(ss, palabra.frances, ',');
            std::getline(ss, palabra.aleman, ',');
            std::getline(ss, palabra.ingles, ',');
            palabras.push_back(palabra);
        }
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo del diccionario, por favor consulte con el administrador" << std::endl;
        system("pause");
        //return 1;
    }
    gotoxy(29,9);
    std::cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
    gotoxy(30,10);
    std::cout <<"#";
    gotoxy(50,10);
	cout<<"EspaÒol";
	gotoxy(70,10);
	cout<<"InglÈs";
	gotoxy(90,10);
	cout<<"Alem·n";
	gotoxy(110,10);
	cout<<"FrancÈs";
	gotoxy(130,10);
	cout<<"Italiano"<<endl;
    gotoxy(29,11);
    std::cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
    
	
    //recorre el diccionario y envia la reproduccion del audio
    
    for (int i = 0; i < palabras.size(); i++) {	
	    	//cout<<"palabra # "<<i<<"-"<<palabras[i].ingles<<"-"<<" con trim -";
	    stringstream ss;  
	  	ss<<i;  
	  	ss>>s; 
		std::string paword1=palabras[i].espanol;
		std::string paword2=palabras[i].ingles;
		std::string paword3=palabras[i].aleman;
		std::string paword4=palabras[i].frances;
		std::string paword5=palabras[i].italiano;

		boost::trim_left( paword1 );
		boost::trim_left( paword2 );
		boost::trim_left( paword3 );
		boost::trim_left( paword4 );
		boost::trim_left( paword5 );
		
		boost::trim_right( paword1 );
		boost::trim_right( paword2 );
		boost::trim_right( paword3 );
		boost::trim_right( paword4 );
		boost::trim_right( paword5 );
		gotoxy(29,icont);
		gotoxy(30,icont);
	    std::cout <<i;
	    gotoxy(50,icont);
		cout<<paword1;
		gotoxy(70,icont);
		cout<<paword2;
		gotoxy(90,icont);
		cout<<paword3;
		gotoxy(110,icont);
		cout<<paword4;
		gotoxy(130,icont);
		cout<<paword5<<endl;
		//cout<<i<<"\t\t"<<paword1<<"\t\t"<<paword2<<"\t\t"<<paword3<<"\t\t"<<paword4<<"\t\t"<<paword5<<endl;
		icont+=1;
		
        if(icont==35){
        	system("pause");
        	system("cls");
        	gotoxy(29,9);
		    std::cout<<"+-----------------------------------------------------------------------------------+"<<endl;
		    gotoxy(30,10);
		    std::cout <<"#";
		    gotoxy(50,10);
			cout<<"EspaÒol";
			gotoxy(70,10);
			cout<<"InglÈs";
			gotoxy(90,10);
			cout<<"Alem·n";
			gotoxy(110,10);
			cout<<"FrancÈs";
			gotoxy(130,10);
			cout<<"Italiano"<<endl;
		    gotoxy(29,11);
		    std::cout<<"+-----------------------------------------------------------------------------------+"<<endl;
		    icont=12;
		}
	} 
	system("pause");
}

//Funcion para agregar las nuevas palabras
void agrega(){
	
}

//Funcion para cifrado
void cifrado(string palabra){
	string k1;
	string k2;
	string k3;
	//char str_inp1 = " ";
    //char str_inp2 = " ";
    int res;
    string letra;
	string g1="aeiouAEIOU";
	string g2="bcdfghjklmnpqrstvwxyz";
	string g3="BCDFGHJKLMNPQRSTVWXYZ";
	
	string palabra2="";
	string nombreArchivo = "c:\\temp\\llave.txt";
	ifstream archivo(nombreArchivo.c_str());
	string linea;
	
	
	// Obtener l√≠nea de archivo, y almacenar contenido en "linea"
	getline(archivo, linea);
    //cout<<"Dato original: "<<palabra<<endl;
    k1=linea[0];
    k2=linea[1];
    k3=linea[2];
    
	for(int i=0; i<=palabra.length();i++){
		//size_t find (const string& palabra[i], size_t pos = 0);
		//cout<<"-------------Entra en ciclo ---------- iteracion: "<<i<<endl;
		//valida si es vocal
		size_t found = g1.find(palabra[i]);
		if (found != string::npos){
			res = 0;
			//cout<<palabra[i]<<" Es Vocal..."<<endl;
			letra = palabra[i];
			//cout<<"La letra es: "<<letra<<endl;
			res = letra.compare("a");
			if(res==0) palabra2=palabra2+k1+"1";
			res = letra.compare("A");
			if(res==0) palabra2=palabra2+k1+"1";	
			//if(letra.compare("e")) {
			res = letra.compare("e");
			if(res==0) palabra2=palabra2+k1+"2";
			res = letra.compare("E");
			if(res==0) palabra2=palabra2+k1+"2";
			res = letra.compare("i");
			if(res==0) palabra2=palabra2+k1+"3";
			res = letra.compare("I");
			if(res==0) palabra2=palabra2+k1+"3";
			res = letra.compare("o");
			if(res==0) palabra2=palabra2+k1+"4";
			res = letra.compare("O");
			if(res==0) palabra2=palabra2+k1+"4";
			res = letra.compare("u");
			if(res==0) palabra2=palabra2+k1+"5";
			res = letra.compare("U");
			if(res==0) palabra2=palabra2+k1+"5";
			//cout<<palabra[1]<<" cifrada es: "<<palabra2<<endl;
		}
		
		found = g2.find(palabra[i]);
		if (found != string::npos){
			res = 0;
			//cout<<palabra[i]<<" Es Vocal..."<<endl;
			letra = palabra[i];
			//cout<<"La letra es: "<<letra<<endl;
			res = letra.compare("a");
			if(res==0) palabra2=palabra2+k1+"1";
			res = letra.compare("A");
			if(res==0) palabra2=palabra2+k1+"1";	
			//if(letra.compare("e")) {
			res = letra.compare("e");
			if(res==0) palabra2=palabra2+k1+"2";
			res = letra.compare("E");
			if(res==0) palabra2=palabra2+k1+"2";
			res = letra.compare("i");
			if(res==0) palabra2=palabra2+k1+"3";
			res = letra.compare("I");
			if(res==0) palabra2=palabra2+k1+"3";
			res = letra.compare("o");
			if(res==0) palabra2=palabra2+k1+"4";
			res = letra.compare("O");
			if(res==0) palabra2=palabra2+k1+"4";
			res = letra.compare("u");
			if(res==0) palabra2=palabra2+k1+"5";
			res = letra.compare("U");
			if(res==0) palabra2=palabra2+k1+"5";
			cout<<palabra[1]<<" cifrada es: "<<palabra2<<endl;
		}
		/*
		//valida si es consonante minuscula
		size_t1 found = g2.find(palabra[i]);
		if (found != string::npos){
			
		}
		
		//valida si es consonante mayudscula
		size_t2 found = g3.find(palabra[i]);
		if (found != string::npos){
			
		}
		*/
	}
	cout<<"Dato cifrado: "<<palabra2<<endl; 	
		
}


//Despedida del sistema
void salida(){
	system("cls");
	system("color 0a");
	gotoxy(50,15);
	cout<<"      ___           ___           ___     "<<endl;
	gotoxy(50,16);
	cout<<"     /\\__\\         /\\__\\         /\\  \\    "<<endl;
	gotoxy(50,17);
	cout<<"    /:/  /        /::|  |       /::\\  \\   "<<endl;
	gotoxy(50,18);
	cout<<"   /:/  /        /:|:|  |      /:/\\:\\  \\  "<<endl;
	gotoxy(50,19);
	cout<<"  /:/  /  ___   /:/|:|__|__   /:/  \\:\\  \\ "<<endl;
	gotoxy(50,20);
	cout<<" /:/__/  /\\__\\ /:/ |::::\\__\\ /:/__/_\\:\\__\\"<<endl;
	gotoxy(50,21);
	cout<<" \\:\\  \\ /:/  / \\/__/~~/:/  / \\:\\  /\\ \\/__/"<<endl;
	gotoxy(50,22);
	cout<<"  \\:\\  /:/  /        /:/  /   \\:\\ \\:\\__\\  "<<endl;
	gotoxy(50,23);
	cout<<"   \\:\\/:/  /        /:/  /     \\:\\/:/  /  "<<endl;
	gotoxy(50,24);
	cout<<"    \\::/  /        /:/  /       \\::/  /   "<<endl;
	gotoxy(50,25);
	cout<<"     \\/__/         \\/__/         \\/__/   "<<endl;
	gotoxy(50,26);
	cout<<" Gracias por usar nuestro Software..."<<endl;
	std::string fullPath="c:\\lib\\3000.wav";
		//cout<<fullPath;
		//system("pause");
		const char *folder = fullPath.c_str();
		int ires;
		//cout<<folder<<endl;
		//cout<<"path ->"<<folder<<endl;
		//if (menu_sound==false) {
			ires=PlaySound(folder, NULL, SND_FILENAME);
			menu_sound=true;
		//}
	//Sleep(2000);
	system("cls");
}

//Funcion de menu temporal
void menu(){
	bool Salir=false;
  system("cls");
  std::string fullPath="c:\\lib\\2001.wav";
  const char *folder = fullPath.c_str();
  int ires;
  
  //fullscreen();
  miMenu.Add_Items("1. Traducir  ",1);	
  miMenu.Add_Items("2. Consultar",2);	
  miMenu.Add_Items("3. Salir ",3);	
  //miMenu.Add_Items("4. Salir    ",4);	
  
  //miMenu.Set_Space(2);


do{
	TextColor(10);
	system("cls");
	Say(65,12,"TRADUCTOR");
	Say(61,13,"PROGRAMACION III");
		ires=PlaySound(folder, NULL, SND_FILENAME);
			menu_sound=true;
		//}//
		
	if(opc==0)
		{
		SetColorB(2,19);  
		Rectangle(50,17,40,12,"#"); 
		SetColorA(2,22);  
		Say(58,15,"*** MENU PRINCIPAL ***");
  		opc=miMenu.Draw(61,20);
  		
	    }	
  	
		//cout<<folder<<endl;
		//cout<<"path ->"<<folder<<endl;
		//if (menu_sound==false) {
					
   switch (opc) 
	  {     
			
			case 1:
			   Cls();
			   buscarpalabra();
			   opc=0;
			break;
			   
			case 2:
				Cls();
				Diccionario();
				opc=0;
			break;
			
			case 3:
				Salir=true;
			break;
			
			//case 4:
			//	Salir=true;
			//break;
			
	  }
  

}while(Salir==false);
  
	
}

//Manuel aqui iria tu aporte y se copiaria al resto de pantallas
void menu2 (){
	
	int resp;
	do{
		system("cls");
		system("color 0a");
		gotoxy(50,10);
		cout<<"######################################################################";
		gotoxy(50,11);
		cout<<"##                     Menu Principal                                #"<<endl;
		gotoxy(50,12);
		cout<<"######################################################################"<<endl;
		gotoxy(50,13);
		cout<<""<<endl;
		gotoxy(50,14);
		cout<<"             [1] Traducir palabra                                      "<<endl;
		//cout<<"             [2] Agregar  palabra                                      "<<endl;
		gotoxy(50,15);
		cout<<"             [2] Consultar diccionario                                 "<<endl;
		gotoxy(50,16);
		cout<<"             [0] Salir                                               "<<endl;
		gotoxy(50,17);
		cout<<"                                                                     "<<endl;
		gotoxy(50,18);
		cout<<"             [    ]                                                  "<<endl; //10
		gotoxy(50,19);                      //15
		cout<<"######################################################################"<<endl;
		gotoxy(65,18);
		std::string fullPath="c:\\lib\\2000.wav";
		//cout<<fullPath;
		//system("pause");
		const char *folder = fullPath.c_str();
		int ires;
		//cout<<folder<<endl;
		//cout<<"path ->"<<folder<<endl;
		if (menu_sound==false) {
			ires=PlaySound(folder, NULL, SND_FILENAME);
			menu_sound=true;
		}
		
		cin>>resp;
		if(resp==1) buscarpalabra();
		if(resp==2) agrega();
		if(resp==3) buscarpalabra();
		
	}while(resp!=0);
	salida();
}

//Metodo principal para llamar las distintas funciones
int main() {
	fullscreen();
	//defaults();
	//buscarpalabra();
	//system("pause");
	//fullscreen();
	intro();
	//carga_diccionario();
	menu();
	salida();
	system("exit");
	//string palabra;
	//cout<<"Por favor ingrese la palabra a cifrar"<<endl;
	//cin>>palabra;
	//cifrado(palabra);
	
	return 0;
}
