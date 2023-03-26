/// Progra III 
//Aqui se incluyen las liberias a usar
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#include <cstdlib> // contiene la funcion system("pause")
#include <string> 
#include<sstream>  
#include <locale.h> // Libreria que contiene la funcion setlocales
#include <cctype>
#include <bits/stdc++.h>

/// Aqui se definen las variables locales
std::string path ="..\\voices\\"; //path de archivos de audio
std::string diccionario_file ="..\\diccionario.txt"; //path de archivo de diccionario
std::string user_profiles ="";//path de user profiles
int correlativo=0; //variable de correlativo global
std::string diccionario_a[5][1000]; //array de 5 columnas por 1000 filas
using namespace std;


//Funcion para cargar valores predeterminados
void defaults(){
	
	//carga los parametros iniciales desde el archivo de configuracion config.cfg
	//carga correlativos y ubicacion del diccionario
	string nombreArchivo = "c:\\temp\\config.cfg";
	ifstream archivo(nombreArchivo.c_str());
	string linea;
	int icontador=0;
	// Obtener línea de archivo, y almacenar contenido en "linea"
	getline(archivo, linea);
	stringstream ss(linea);  
    string word;
    while (ss >> word) { // Extract word from the stream.
        icontador+=1;
		if (icontador==1) correlativo=atoi(word.c_str());
		//if (icontador==2) path=word;
		if (icontador==3) diccionario_file=word;
		//cout << word << endl;
    }
	//cout<<"correlativo: "<<correlativo<<" path de audio "<<path<<" diccionario: "<<diccionario_file<<endl;
}

//Funcion para cargar el diccionario a estructuras
// Kenny Saenz aqui va tu parte

///// Esto es temporal mientras se integra la parte de Kenny

void carga_diccionario(){
	setlocale(LC_ALL, ""); 
	//string nombreArchivo = "c:\\temp\\config.cfg";
	//cout<<"archivo de configuracion: "<<diccionario_file<<endl;
	string nombre_archivo="c:\\temp\\diccionario.txt";
	ifstream archivo(nombre_archivo.c_str());
	string linea;
	int fila=0;
	int palabra=0;
	getline(archivo, linea);
	//cout<<"carga palabras"<<linea<<endl;
	do{
		
		//cout<<"linea--"<<linea<<endl;
		stringstream ss(linea);  
	    string word;
	    while (ss >> word) { // Extract word from the stream.
	    	//cout<<"palabra->"<<word<<" fila: "<<fila<<" palabra: "<<palabra<<endl;
	       diccionario_a[fila][palabra]=word;
	       palabra+=1;
	    }
	    linea="";
	    getline(archivo, linea);
	    fila+=1;		
	}while(linea != "");
	
	//cout<<"cargo el diccionario"<<endl;
	//system("pause");
	
	fila=0;
	palabra=0;
	for(int i=0;i<1000;i++){ //top 1000 palabras
		for(int e=0;e<5;e++){
			//cout<<diccionario_a[i][e]<<endl;
		}
		//cout<<endl;
		string word=diccionario_a[i][0];
		if(word =="") {
			break;
		}
	}
	//system("pause");
}

//Funcion para generar audios desde AWS Polly y luego de descargarlo en MP3 lo convierte en WAV
string aws_audio(int index, string word, int wordindex, string palabra){
	std::string comando; 
	std::string fullPath = path;
	std::string genfullPath = path;
	//En base a la sesleccion asigna la carpeta del idioma
	if (index==0) fullPath +="spanish\\"; //Español
	if (index==1) fullPath+="english\\"; //Ingles
	if (index==2) fullPath+="german\\"; //Aleman
	if (index==3) fullPath+="french\\"; //Frances
	if (index==4) fullPath+="italian\\"; //Italiano
	//Toma el path generico y se guarda por aparte
	genfullPath=fullPath; //
	stringstream ss;  
	ss<<wordindex+1;  
	string s;  
	ss>>s; 
	//string str = to_string(wordindex;
	//evalua el idioma para construir el string
	comando="aws polly synthesize-speech --output-format mp3 --voice-id ";
	if (index==0) comando +="Penelope"; //Español
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
	comando+=">salida.txt";
	
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
	comando+=".wav > salida.txt";
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
	//cout<<word<<" la palabra"<<endl;
	//system("pause");
	//En base a la sesleccion asigna la carpeta del idioma
	if (index==0) fullPath +="spanish\\"; //Español
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
		//cout<<" no aparece el archivo"<<" Correlativo es "<<correlativo<<endl;
		iresp=aws_audio(index,word,correlativo,palabra);
		//No lo encontró
		fullPath=iresp;
		//fullPath+=iresp;
		//fullPath+=".wav";
		cout<<fullPath<<" path del archivo -- respuesta de funcion: "<<iresp<<endl;
		//system("pause");
		//system("cls");
	}
	const char *folder = fullPath.c_str();
	int ires;
	cout<<"path ->"<<folder<<endl;
	ires=PlaySound(folder, NULL, SND_FILENAME); //SND_FILENAME or SND_LOOP
	//cout<<"respuesta: "<<ires<<endl;
}


//Funcion que devuelve la palabra traducida
//Falta afinar que pida el idioma origen
void traduce (){
	char palabras1[0][0];
	char palabras2[0][0];
	int respuesta;
	std::string palabra;
	string translation;
	string comando;
	int word;
	int idioma_origen;
	
	cout<<"Ingrese la palabra a decir: "<<endl;
	cin>>palabra;
	cout<<"ingrese el idioma [0] español [1] ingles [2] aleman [3] frances [4] italiano"<<endl;
	cin>>respuesta;
	play(respuesta, "404", palabra);
	system("pause");
	return;
	
	do{
		
		system("cls");
		system("color 0a");
		cout<<"###########################################################"<<endl;
		cout<<"#            Selecciona el idimoa que deseas              #"<<endl;
		cout<<"###########################################################"<<endl;
		cout<<" "<<endl;
		cout<<"###########################################################"<<endl;
		cout<<" Selecciona el idioma "<<endl;
		cout<<endl;
		cout<<" [1] Español"<<endl;
		cout<<" [2] Inglés"<<endl;
		cout<<" [3] Alemán"<<endl;
		cout<<" [4] Francés"<<endl;
		cout<<" [5] Italiano"<<endl;
		cout<<" [0] Salir"<<endl;
		cin>>respuesta;
		if(respuesta!=0){
			word=403;
			cout<<endl<<endl<<"Ingrese la palabra a traducir:"<<endl;
			cin>>palabra;
			
			
			//ciclo para buscar las palabras
			for(int i=0;i<5;i++){
				if(diccionario_a[i]) {
					
					word=i;
					if (word==0) cout<<"La palabra esta en Español y sera traducida al ";
					if (word==1) cout<<"La palabra esta en Inglés y sera traducida al ";
					if (word==2) cout<<"La palabra esta en Alemán y sera traducida al ";
					if (word==3) cout<<"La palabra esta en Francés y sera traducida al ";
					if (word==4) cout<<"La palabra esta en Italiano y sera traducida al ";
					
					if (respuesta-1==0) cout<<"Español"<<endl;
					if (respuesta-1==1) cout<<"Inglés"<<endl;
					if (respuesta-1==2) cout<<"Alemán"<<endl;
					if (respuesta-1==3) cout<<"Francés"<<endl;
					if (respuesta-1==4) cout<<"Italiano"<<endl;
					if (word!=0) {//La palabra esta en otro idioma y la traducimos al español
						word = 0;	
					}
					translation=palabras1[respuesta-1];
					//cout<<"Entro en validacion: "<<palabra<<" == "<<palabras1[i]<<" word :"<<word<<" indice: "<<i<<endl;
				}
				if(palabras2[i]== palabra) {
					word=i;
					cout<<"palabra encontrada..."<<word<<endl;
					if (word==0) cout<<"La palabra esta en Español y sera traducida al ";
					if (word==1) cout<<"La palabra esta en Inglés y sera traducida al ";
					if (word==2) cout<<"La palabra esta en Alemán y sera traducida al ";
					if (word==3) cout<<"La palabra esta en Francés y sera traducida al ";
					if (word==4) cout<<"La palabra esta en Italiano y sera traducida al ";
					
					if (respuesta-1==0) cout<<"Español"<<endl;
					if (respuesta-1==1) cout<<"Inglés"<<endl;
					if (respuesta-1==2) cout<<"Alemán"<<endl;
					if (respuesta-1==3) cout<<"Francés"<<endl;
					if (respuesta-1==4) cout<<"Italiano"<<endl;
					//if (word!=0) {//La palabra esta en otro idioma y la traducimos al español
						word = 1;	
					//}
					translation=palabras2[respuesta-1];
					//cout<<"Entro en validacion: "<<palabra<<" == "<<palabras1[i]<<" word :"<<word<<" indice: "<<i<<endl;
				}
				//cout<<palabras1[i];
				//system("pause");
			}
			
			//if(word.length() ==0) word="404";
			//if(!found) palabra=404
			//std::string s = std::to_string(word);
			
			stringstream ss;  
		  	ss<<word+1;  
		  	string s;  
		  	ss>>s;  
		  	int ires;
			  	
			if(word==403) {
				cout<<"Lo siento, esa palabra no la tengo registrada"<<endl;
				play(respuesta-1,s,palabra);
				///play(0,s,palabra);
			}
			else {
				
				
			  	cout<<"La palabra "<<palabra<<" Se escribe ->"<<translation<<endl;
			  	cout<<" y se pronuncia...."<<endl;
			  	do{
			  		play(respuesta-1,s,palabra);
			  		cout<<"Dese escucharla de nuevo? "<<endl;
			  		cout<<"[0] No   [1] Si"<<endl;
			  		cin>>ires;
				  }while(ires != 0);
			}
			//system("pause");
		}
	}while(respuesta !=0);
}

//Funcion para imprimir el diccionario
void diccionario(){
	
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
	
	
	// Obtener línea de archivo, y almacenar contenido en "linea"
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
	cout<<"      ___           ___           ___     "<<endl;
cout<<"     //\\__\\         //\\__\\         //\\  \\    "<<endl;
cout<<"    //://  //        //::|  |       //::\\  \\   "<<endl;
cout<<"   //://  //        //:|:|  |      //://\\:\\  \\  "<<endl;
cout<<"  //://  //  ___   //://|:|__|__   //://  \\:\\  \\ "<<endl;
cout<<" //://__//  //\\__\\ //:// |::::\\__\\ //://__//_\\:\\__\\"<<endl;
cout<<" \\:\\  \\ //://  // \\//__//~~//://  // \\:\\  //\\ \\//__//"<<endl;
cout<<"  \\:\\  //://  //        //://  //   \\:\\ \\:\\__\\  "<<endl;
cout<<"   \\:\\//://  //        //://  //     \\:\\//://  //  "<<endl;
cout<<"    \\:://  //        //://  //       \\:://  //   "<<endl;
cout<<"     \\//__//         \\//__//         \\//__//    "<<endl;
	cout<<""<<endl;
	cout<<" Gracias por usar nuestro Software..."<<endl;
}

//Funcion de menu temporal
//Manuel aqui iria tu aporte y se copiaria al resto de pantallas
void menu (){
	system("cls");
	system("color 0a");
	int resp;
	do{
		cout<<"######################################################################"<<endl;
		cout<<"##                     Menu Principal      DEV MODE                          #"<<endl;
		cout<<"######################################################################"<<endl;
		cout<<""<<endl;
		cout<<"             [1] Traducir palabra                                      "<<endl;
		cout<<"             [2] Agregar  palabra                                      "<<endl;
		cout<<"             [3] Consultar diccionario                                 "<<endl;
		cout<<"             [0] Salir                                               "<<endl;
		
		cout<<"######################################################################"<<endl;
		cin>>resp;
		if(resp==1) traduce();
		if(resp==2) agrega();
		if(resp==3) diccionario();
		
	}while(resp==0);
	salida();
}

//Metodo principal para llamar las distintas funciones
int main() {
	defaults();
	//system("pause");
	//fullscreen();
	//intro();
	carga_diccionario();
	menu();
	string palabra;
	cout<<"Por favor ingrese la palabra a cifrar"<<endl;
	cin>>palabra;
	cifrado(palabra);
	
	return 0;
}
