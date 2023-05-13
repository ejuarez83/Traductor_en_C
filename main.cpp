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
//librerias para audio
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")
#endif
//#include "md5.h"
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
std::string user="Invitado";
std::string user_profiles ="";//path de user profiles
int correlativo=200; //variable de correlativo global
std::string diccionario_a[5][1000]; //array de 5 columnas por 1000 filas
bool menu_sound=false;
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
	ss<<wordindex+1;  
	string s;  
	ss>>s; 
	//string str = to_string(wordindex;
	//evalua el idioma para construir el string
	comando="aws polly synthesize-speech --output-format mp3 --voice-id ";
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
	comando="ffmpeg -y -loglevel quiet -i ";
	comando+=genfullPath;
	comando+=s;
	comando+=".mp3 ";
	comando+=genfullPath;
	comando+=s;
	comando+=".wav ";
	//out<<comando<<endl;
	//system("pause");
	const char * c1 = comando.c_str();
	//Convierte mp3 a Wav
	system(c1);
	//devuelve  el valor en la rutina
	//correlativo+=1;
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
	if (index==3) fullPath+="german\\"; //Aleman
	if (index==2) fullPath+="french\\"; //Frances
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

//Funcion para cifrado
string cifrado(string palabra){
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
	string nombreArchivo = "llave.txt";
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
			if(res==0) palabra2=palabra2+k1+"6";	
			//if(letra.compare("e")) {
			res = letra.compare("e");
			if(res==0) palabra2=palabra2+k1+"2";
			res = letra.compare("E");
			if(res==0) palabra2=palabra2+k1+"7";
			res = letra.compare("i");
			if(res==0) palabra2=palabra2+k1+"3";
			res = letra.compare("I");
			if(res==0) palabra2=palabra2+k1+"8";
			res = letra.compare("o");
			if(res==0) palabra2=palabra2+k1+"4";
			res = letra.compare("O");
			if(res==0) palabra2=palabra2+k1+"9";
			res = letra.compare("u");
			if(res==0) palabra2=palabra2+k1+"5";
			res = letra.compare("U");
			if(res==0) palabra2=palabra2+k1+"10";
			//cout<<palabra[1]<<" cifrada es: "<<palabra2<<endl;
		}
		
		found = g2.find(palabra[i]);
		if (found != string::npos){
			res = 0;
			//cout<<palabra[i]<<" Es Vocal..."<<endl;
			letra = palabra[i];
			//cout<<"La letra es: "<<letra<<endl;
			res = letra.compare("b");
			if(res==0) palabra2=palabra2+k2+"1";
			res = letra.compare("c");
			if(res==0) palabra2=palabra2+k2+"2";	
			res = letra.compare("d");
			if(res==0) palabra2=palabra2+k2+"3";
			res = letra.compare("f");
			if(res==0) palabra2=palabra2+k2+"4";
			res = letra.compare("g");
			if(res==0) palabra2=palabra2+k2+"5";
			res = letra.compare("h");
			if(res==0) palabra2=palabra2+k2+"6";
			res = letra.compare("j");
			if(res==0) palabra2=palabra2+k2+"7";
			res = letra.compare("k");
			if(res==0) palabra2=palabra2+k2+"8";
			res = letra.compare("l");
			if(res==0) palabra2=palabra2+k2+"9";
			res = letra.compare("m");
			if(res==0) palabra2=palabra2+k2+"10";
			res = letra.compare("n");
			if(res==0) palabra2=palabra2+k2+"11";
			res = letra.compare("Ò");
			if(res==0) palabra2=palabra2+k2+"12";
			res = letra.compare("p");
			if(res==0) palabra2=palabra2+k2+"13";
			res = letra.compare("q");
			if(res==0) palabra2=palabra2+k2+"14";
			res = letra.compare("r");
			if(res==0) palabra2=palabra2+k2+"15";
			res = letra.compare("s");
			if(res==0) palabra2=palabra2+k2+"16";
			res = letra.compare("t");
			if(res==0) palabra2=palabra2+k2+"17";
			res = letra.compare("v");
			if(res==0) palabra2=palabra2+k2+"18";
			res = letra.compare("w");
			if(res==0) palabra2=palabra2+k2+"19";
			res = letra.compare("x");
			if(res==0) palabra2=palabra2+k2+"20";
			res = letra.compare("y");
			if(res==0) palabra2=palabra2+k2+"21";
			res = letra.compare("z");
			if(res==0) palabra2=palabra2+k2+"22";
			
			//cout<<palabra[1]<<" cifrada es: "<<palabra2<<endl;
		}
		
		
		found = g3.find(palabra[i]);
		if (found != string::npos){
			res = 0;
			//cout<<palabra[i]<<" Es Vocal..."<<endl;
			letra = palabra[i];
			//cout<<"La letra es: "<<letra<<endl;
			res = letra.compare("B");
			if(res==0) palabra2=palabra2+k3+"1";
			res = letra.compare("C");
			if(res==0) palabra2=palabra2+k3+"2";	
			res = letra.compare("D");
			if(res==0) palabra2=palabra2+k3+"3";
			res = letra.compare("F");
			if(res==0) palabra2=palabra2+k3+"4";
			res = letra.compare("G");
			if(res==0) palabra2=palabra2+k3+"5";
			res = letra.compare("H");
			if(res==0) palabra2=palabra2+k3+"6";
			res = letra.compare("J");
			if(res==0) palabra2=palabra2+k3+"7";
			res = letra.compare("K");
			if(res==0) palabra2=palabra2+k3+"8";
			res = letra.compare("L");
			if(res==0) palabra2=palabra2+k3+"9";
			res = letra.compare("M");
			if(res==0) palabra2=palabra2+k3+"10";
			res = letra.compare("N");
			if(res==0) palabra2=palabra2+k3+"11";
			res = letra.compare("—");
			if(res==0) palabra2=palabra2+k3+"12";
			res = letra.compare("P");
			if(res==0) palabra2=palabra2+k3+"13";
			res = letra.compare("Q");
			if(res==0) palabra2=palabra2+k3+"14";
			res = letra.compare("R");
			if(res==0) palabra2=palabra2+k3+"15";
			res = letra.compare("S");
			if(res==0) palabra2=palabra2+k3+"16";
			res = letra.compare("T");
			if(res==0) palabra2=palabra2+k3+"17";
			res = letra.compare("V");
			if(res==0) palabra2=palabra2+k3+"18";
			res = letra.compare("W");
			if(res==0) palabra2=palabra2+k3+"19";
			res = letra.compare("X");
			if(res==0) palabra2=palabra2+k3+"20";
			res = letra.compare("Y");
			if(res==0) palabra2=palabra2+k3+"21";
			res = letra.compare("Z");
			if(res==0) palabra2=palabra2+k3+"22";
			
			//cout<<palabra[1]<<" cifrada es: "<<palabra2<<endl;
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
	//cout<<"Dato cifrado: "<<palabra2<<endl; 	
	return(palabra2);	
}

//Funcion para cifrado
string descifrado(string palabra){
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
	string nombreArchivo = "llave.txt";
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
			res = letra.compare("b");
			if(res==0) palabra2=palabra2+k2+"1";
			res = letra.compare("c");
			if(res==0) palabra2=palabra2+k2+"2";	
			res = letra.compare("d");
			if(res==0) palabra2=palabra2+k2+"3";
			res = letra.compare("f");
			if(res==0) palabra2=palabra2+k2+"4";
			res = letra.compare("g");
			if(res==0) palabra2=palabra2+k2+"5";
			res = letra.compare("h");
			if(res==0) palabra2=palabra2+k2+"6";
			res = letra.compare("j");
			if(res==0) palabra2=palabra2+k2+"7";
			res = letra.compare("k");
			if(res==0) palabra2=palabra2+k2+"8";
			res = letra.compare("l");
			if(res==0) palabra2=palabra2+k2+"9";
			res = letra.compare("m");
			if(res==0) palabra2=palabra2+k2+"10";
			res = letra.compare("n");
			if(res==0) palabra2=palabra2+k2+"11";
			res = letra.compare("Ò");
			if(res==0) palabra2=palabra2+k2+"12";
			res = letra.compare("p");
			if(res==0) palabra2=palabra2+k2+"13";
			res = letra.compare("q");
			if(res==0) palabra2=palabra2+k2+"14";
			res = letra.compare("r");
			if(res==0) palabra2=palabra2+k2+"15";
			res = letra.compare("s");
			if(res==0) palabra2=palabra2+k2+"16";
			res = letra.compare("t");
			if(res==0) palabra2=palabra2+k2+"17";
			res = letra.compare("v");
			if(res==0) palabra2=palabra2+k2+"18";
			res = letra.compare("w");
			if(res==0) palabra2=palabra2+k2+"19";
			res = letra.compare("x");
			if(res==0) palabra2=palabra2+k2+"20";
			res = letra.compare("y");
			if(res==0) palabra2=palabra2+k2+"21";
			res = letra.compare("z");
			if(res==0) palabra2=palabra2+k2+"22";
			
			//cout<<palabra[1]<<" cifrada es: "<<palabra2<<endl;
		}
		
		
		found = g3.find(palabra[i]);
		if (found != string::npos){
			res = 0;
			//cout<<palabra[i]<<" Es Vocal..."<<endl;
			letra = palabra[i];
			//cout<<"La letra es: "<<letra<<endl;
			res = letra.compare("B");
			if(res==0) palabra2=palabra2+k3+"1";
			res = letra.compare("C");
			if(res==0) palabra2=palabra2+k3+"2";	
			res = letra.compare("D");
			if(res==0) palabra2=palabra2+k3+"3";
			res = letra.compare("F");
			if(res==0) palabra2=palabra2+k3+"4";
			res = letra.compare("G");
			if(res==0) palabra2=palabra2+k3+"5";
			res = letra.compare("H");
			if(res==0) palabra2=palabra2+k3+"6";
			res = letra.compare("J");
			if(res==0) palabra2=palabra2+k3+"7";
			res = letra.compare("K");
			if(res==0) palabra2=palabra2+k3+"8";
			res = letra.compare("L");
			if(res==0) palabra2=palabra2+k3+"9";
			res = letra.compare("M");
			if(res==0) palabra2=palabra2+k3+"10";
			res = letra.compare("N");
			if(res==0) palabra2=palabra2+k3+"11";
			res = letra.compare("—");
			if(res==0) palabra2=palabra2+k3+"12";
			res = letra.compare("P");
			if(res==0) palabra2=palabra2+k3+"13";
			res = letra.compare("Q");
			if(res==0) palabra2=palabra2+k3+"14";
			res = letra.compare("R");
			if(res==0) palabra2=palabra2+k3+"15";
			res = letra.compare("S");
			if(res==0) palabra2=palabra2+k3+"16";
			res = letra.compare("T");
			if(res==0) palabra2=palabra2+k3+"17";
			res = letra.compare("V");
			if(res==0) palabra2=palabra2+k3+"18";
			res = letra.compare("W");
			if(res==0) palabra2=palabra2+k3+"19";
			res = letra.compare("X");
			if(res==0) palabra2=palabra2+k3+"20";
			res = letra.compare("Y");
			if(res==0) palabra2=palabra2+k3+"21";
			res = letra.compare("Z");
			if(res==0) palabra2=palabra2+k3+"22";
			
			//cout<<palabra[1]<<" cifrada es: "<<palabra2<<endl;
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
	//cout<<"Dato cifrado: "<<palabra2<<endl; 	
	return(palabra2);	
}

//// SE AGREGA LA ESTRUCTURA DE ARBOL AVL

class avl
{	//int index;
	char index[4],spanish[20],english[20],french[20],german[20],italian[20];
	avl *left,*right;
	int ht;
public:
	avl* create(avl *root);
	avl* insert(avl *root,char index[],char spanish[], char english[], char french[], char german[], char italian[]);
	void display(avl*);
	int height(avl*);
	avl* rotateright(avl*);
	avl* rotateleft(avl*);
	int BF(avl*);
	avl* Delete(avl*,char*);
	avl* RR(avl*);
	avl*LL(avl*);
	avl*LR(avl*);
	avl*RL(avl*);
	avl* mirror(avl*);
	avl* update(avl*);
};

//Crea el arbol a nivel global para poderse usar
avl d,*root,*root1;
bool Salida=false;
	
avl* avl::create(avl *root)
{	int n_o,i;
	char index[4], w[20],m[20],n[20],o[20],p[20];
	root=insert(root,index,w,m,n,o,p);
	/*
	cout<<"\n Enter the number spanishs:\t";
	cin>>n_o;
	for(i=0;i<n_o;i++)
	{	cout<<"\n Enter the "<<i+1<<" spanish";
		cin>>w;
		cout<<"\n Enter the english:";
		cin>>m;
		cout<<"\n Enter the french:";
		cin>>n;
		cout<<"\n Enter the german:";
		cin>>o;
		cout<<"\n Enter the italian:";
		cin>>p;
		root=insert(root,w,m,n,o,p);
	}*/
	return root;
}

avl* avl::insert(avl *root,char index[] , char w[],char m[],char n[], char o[], char p[])
{	if(root==NULL)
	{	root=new avl;
		strcpy(root->index,index);
		strcpy(root->spanish,w);
		strcpy(root->english,m);
		strcpy(root->french,n);
		strcpy(root->german,o);
		strcpy(root->italian,p);
		root->left=NULL;
		root->right=NULL;
		return root;
	}
    else
    {
	  if(strcmp(w,root->spanish)>0)
	  {
		root->right=insert(root->right,index,w,m,n,o,p);
		if(BF(root)==2)
		{
			if(strcmp(w,root->spanish)>=0)
				root=RR(root);
			else
				root=RL(root);
		}

	  }
	  else
	  {
		  if(strcmp(w,root->spanish)<0)
		  {
		  		root->left=insert(root->left,index,w,m,n,o,p);
		  		if(BF(root)==-2)
		  		{
		  			if(strcmp(w,root->spanish)<=0)
		  				root=LL(root);
		  			else
		  				root=LR(root);
		  		}
		  }
	   }
	}
	root->ht=height(root);
	return root;
}

void avl::display(avl* root)
{	//cout<<"===========================================================\n"<<endl;
	//cout<<"=                           =                              \n"<<endl;
	if (root!=NULL)
	{	display(root->left);
		cout<<"\n"<<root->spanish<<" - "<<root->english<<" - "<<root->french <<" - "<<root->german<<" - "<<root->italian;
		display(root->right);
	}
}

int avl::height(avl *root)
{
	int lh,rh;
	if(root==NULL)
		return 0;
	if(root->left==NULL)
		lh=0;
	else
		lh=1+root->left->ht;

	if(root->right==NULL)
		rh=0;
	else
		rh=1+root->right->ht;

	if(lh>rh)
		return(lh);
	else
		return(rh);
}

avl* avl::rotateright(avl *x)
{
	avl *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}

avl* avl::rotateleft(avl *x)
{
	avl *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}

int avl::BF(avl *root)
{
	int lh,rh;
	if(root==NULL)
		return 0;

	if(root->left==NULL)
		lh=0;
	else
		lh=1+root->left->ht;

	if(root->right==NULL)
			rh=0;
		else
		rh=1+root->right->ht;
	int z=lh-rh;
	return(z);
}
avl* avl::Delete(avl* T,char* w)
{
	avl *p;
	if(T==NULL)
	{
		cout<<"\n Palabra no encontrada";
		return T;
	}
	if(strcmp(w,T->spanish)>0)
	{
		T->right=Delete(T->right,w);
		if(BF(T)==2)
		{
			if(BF(T->left)>=0)
				T=LL(T);
			else
				T=LR(T);
		}

	}
	else
		if(strcmp(w,T->spanish)<0)
		{
			T->left=Delete(T->left,w);
			if(BF(T)==-2)
			{
				if(BF(T->right)<=0)
					T=RR(T);
				else
					T=RL(T);
			}
		}
		else
		{
			if(T->right!=NULL)
			{
				p=T->right;
				while(p->left!=NULL)
					p=p->left;
				strcpy(T->spanish,p->spanish);
				strcpy(T->english,p->english);
				strcpy(T->french,p->french);
				strcpy(T->german,p->german);
				strcpy(T->italian,p->italian);
				T->right=Delete(T->right,p->spanish);
						if(BF(T)==2)
						{
							if(BF(T->left)>=0)
								T=LL(T);
							else
								T=LR(T);
						}
			}
			else
				return(T->left);
		}
	T->ht=height(T);
	return(T);
}
avl* avl::RR(avl*T)
{
	T=rotateleft(T);
	return(T);
}
avl* avl::LL(avl*T)
{
	T=rotateright(T);
	return(T);
}
avl* avl::LR(avl*T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);
	return(T);
}
avl* avl::RL(avl*T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}
avl* avl::mirror(avl* temp)
{
	avl*p;
	if(temp==NULL)
		return NULL;
	p=new avl;
	strcpy(p->spanish,temp->spanish);
	strcpy(p->english,temp->english);
	strcpy(p->french,temp->french);
	strcpy(p->german,temp->german);
	strcpy(p->italian,temp->italian);
	p->left=mirror(temp->right);
	p->right=mirror(temp->left);
	return p;
}

void agrega_perfil(string texto){
	//string texto;
    std::string archivo_str=user;
	archivo_str+=".pfl";
	//std::ofstream myfile("profile.txt", ios::app);
   	std::ofstream archivo(archivo_str.c_str(), ios::app); // Abre el archivo en modo de escritura y posiciona el puntero al final
   	if (archivo.is_open()) {
    	//cout << "Escriba el texto que desea agregar al archivo:" << endl;
      	//getline(cin, texto); // Leer el texto ingresado por el usuario
	      //archivo << texto << endl; // Escribir el texto en el archivo
	      //archivo.close(); // Cerrar el archivo
	      //cout<<"escribio al archivo la ultima palabra: "<<texto<<" cifrado "<<cifrado(texto)<<endl;
	      //system("pause");
	      boost::to_upper(texto);
	      ifstream archivo_lectura(archivo_str.c_str()); // Abrir el archivo en modo de lectura
	      if (archivo_lectura.is_open()) {
	         string contenido((istreambuf_iterator<char>(archivo_lectura)), istreambuf_iterator<char>()); // Leer todo el contenido del archivo
	         archivo_lectura.close(); // Cerrar el archivo
	         ofstream archivo_escritura(archivo_str.c_str()); // Abrir el archivo en modo de escritura
	         if (archivo_escritura.is_open()) {
	            //archivo_escritura<< cifrado(texto) << endl << contenido; // Escribir el texto al principio del archivo y luego el contenido leÌdo anteriormente
	            archivo_escritura<< texto << endl << contenido;
				archivo_escritura.close(); // Cerrar el archivo
	         } else {
	            cout << "Error al abrir el archivo en modo de escritura." << endl;
	         }
	      } else {
	         cout << "Error al abrir el archivo en modo de lectura." << endl;
	      }
	} else {
	   cout << "Error al abrir el archivo en modo de escritura." << endl;
	}
}
avl *avl::update(avl *root)
{
	avl *temp;
	char w[20],m[50];
	
	int idioma;
	bool encuentra=false;
	temp=root;
	int indice_idioma;
    int idioma_origen;
    Salida=false;
    string s; 
    std::string palabra;
    std::string palabra_original;
    std::string palabra_traducida;
	gotoxy(10,13);
	cout<<"Ultimas palabras buscadas"<<endl;
	//Carga las preferencias
	int x=14;
	string op;
	std::string archivo_str=user;
	archivo_str+=".pfl";
	std::ifstream archivo(archivo_str.c_str(), ios::in);
	if (archivo.is_open()) {
        std::string linea;
        
        while (getline(archivo, linea)) {
            //std::istringstream ss(linea);
            //convierto todo a mayusculas para comparar
            gotoxy(10,x);
            cout<<linea<<endl;
            x+=1;
            //Palabra palabra;
            //palabra=to_upper(palabra);
        }
        archivo.close();
    } else {
    }
    
    gotoxy(50,14);
	cout<<"Ingrese la palabra a buscar : ";
	cin>>palabra;
	palabra_original=palabra;
	boost::to_upper(palabra);
	
	//std::toupper(ch)
	//w = boost::to_upper(w);
	//for (int x=0; x<strlen(w); x++)
    //    putchar(toupper(w[x]));
    strcpy(w, palabra.c_str());
    //w=toupper(w);//(char)toupper( w);
    
        
	if(strcmp(w,"SALIR")!=0){
	
		gotoxy(50,16);
		std::cout << "Ingrese el idioma al que desea traducir: "<<endl;
		gotoxy(50,17);
		std::cout <<"[1] EspaÒol [2] InglÈs [3] FrancÈs [4] Alem·n [5] Italiano [0] Salir";
		gotoxy(50,18);
		cin>>idioma;
		
		//cout<<"el idioma es: "<<idioma<<endl;
		//cout<<"\n Enter the englishing(updated englishing): ";
		//cin>>m;
		while(temp!=NULL)
		{ //cout<<"entro al ciclo "<<temp->spanish<<endl;
			if((strcmp(w,temp->spanish)==0) or (strcmp(w,temp->english)==0) or (strcmp(w,temp->french)==0)  or (strcmp(w,temp->german)==0) or (strcmp(w,temp->italian)==0) )
			{   gotoxy(50,19);
				cout<<"Se escribe ->";
				encuentra=true;
				if(idioma==1) cout<<temp->spanish<<endl;
				if(idioma==2) cout<<temp->english<<endl;
				if(idioma==3) cout<<temp->french<<endl;
				if(idioma==4) cout<<temp->german<<endl;
				if(idioma==5) cout<<temp->italian<<endl;
				agrega_perfil(palabra_original);
				gotoxy(50,21);
				cout<<"Y se pronuncia..."<<endl;
				play(idioma-1, temp->index, w);
				gotoxy(50,23);
				system("pause");
				//strcpy(temp->spanish,w);
				//strcpy(temp->english,m);
				//////cout<<temp->english<<"-"<<temp->french<<"-"<<temp->german<<"-"<<temp->italian<<endl;
				break;
			} 
			if(strcmp(w,temp->spanish)<0)
			{
				temp=temp->left;
			}
			else
			{
				temp=temp->right;
			}
		}
		if(!encuentra){
			
				gotoxy(50,19);
				cout<<"Su palabra no existe en el diccionario pero la encontraremos en linea..."<<endl;
		   	 	gotoxy(50,20);
		   	 	cout << "Ingrese el idioma original de la palabra [1] EspaÒol [2] InglÈs [3] Alem·n [4] FrancÈs [5] Italiano";
		   	 	gotoxy(50,21);
		   	 	cin>>idioma_origen;
		   	 	string idioma_traducir;
		   	 	string idioma_destino;
		   	 	if(idioma_origen ==1) idioma_traducir="es";
		   	 	if(idioma_origen ==2) idioma_traducir="en";
		   	 	if(idioma_origen ==3) idioma_traducir="de";
		   	 	if(idioma_origen ==4) idioma_traducir="fr";
		   	 	if(idioma_origen ==5) idioma_traducir="it";
		   	 	
		   	 	if(idioma ==1) idioma_destino="es";
		   	 	if(idioma ==2) idioma_destino="en";
		   	 	if(idioma ==3) idioma_destino="de";
		   	 	if(idioma ==4) idioma_destino="fr";
		   	 	if(idioma ==5) idioma_destino="it";
		   	 	std::string comando; 
		   	 	agrega_perfil(palabra_original);
		   	 	comando="python translate.py --text ";
				comando+=w;
				comando+=" --target-language ";
				comando+=idioma_destino;
				comando+=" --api-key '123456asdfasdfaf' --src_lan ";
				comando+=idioma_traducir;
				comando+=" >output.txt";
				//cout<<"el comando es: "<<comando<<endl;
				//system("pause");
				
		   	 	const char * c1 = comando.c_str();
		   	 	gotoxy(50,23);
		   	 	palabra_traducida=system(c1);
		   	 	std::ifstream archivo("output.txt");
		   	 	std::getline(archivo, palabra_traducida);
		   	 	palabra=system(c1);
		   	 	cout<<"Su palabra se escribe: "<<palabra_traducida<<endl;
		   	 	play(idioma-1, "201", palabra_traducida);
		   	 	stringstream ss;
				ss<<correlativo;
				ss>>s; 
				gotoxy(50,24);
				cout<<"y se pronuncia..."<<endl;
				gotoxy(50,26);
				system("pause");
		   	 	
		}
	} else Salida=true;
	return root;
	//cout<<root;
}

void carga(){
	//Carga de palabras en automatico
	int ch;
	char z;
	//avl d,*root,*root1;
	//root=NULL;
	//std::vector<Palabra> palabras;
    std::ifstream archivo("palabras.txt");
    std::string palabra;
    std::string palabra_traducida;
	bool palabra_encontrada = false;
    int indice_idioma;
    int idioma_origen;
    std::string index;
	std::string paword1;
	std::string paword2;
	std::string paword3;
	std::string paword4;
	std::string paword5;
	
	string s;  
	
    // copying the contents of the
    // string to char array
   
	//root=d.create(root);
	//Apertura de archivo y lectura de datos
    if (archivo.is_open()) {
        std::string linea;
        
        while (std::getline(archivo, linea)) {
        	//cout<<linea<<endl;
            std::istringstream ss(linea);
            //convierto todo a mayusculas para comparar
            //
            //Palabra palabra;
            //palabra=to_upper(palabra);
			std::getline(ss, index, ',');
			std::getline(ss, paword1, ',');
            std::getline(ss, paword2, ',');
            std::getline(ss, paword3, ',');
            std::getline(ss, paword4, ',');
            std::getline(ss, paword5, ',');
            //Spanish
            boost::to_upper(paword1);
            boost::to_upper(paword2);
            boost::to_upper(paword3);
            boost::to_upper(paword4);
            boost::to_upper(paword5);
            const int length = paword1.length();
			char* char_array = new char[length + 1];
            strcpy(char_array, paword1.c_str());
            
            //english
            const int length2 = paword2.length();
			char* char_array2 = new char[length2 + 1];
  			strcpy(char_array2, paword2.c_str());
			
			//french
			const int length3 = paword3.length();
			char* char_array3 = new char[length3 + 1];
  			strcpy(char_array3, paword3.c_str());
			
			//german
			const int length4 = paword4.length();
			char* char_array4 = new char[length4 + 1];
			strcpy(char_array4, paword4.c_str());
			
			//italian
			const int length5 = paword5.length();
			char* char_array5 = new char[length5 + 1];
			strcpy(char_array5, paword5.c_str());
			
			const int length6 = index.length();
			char* index_x = new char[length6 + 1];
			strcpy(index_x, index.c_str());
			
			root=d.insert(root,index_x,char_array,char_array2, char_array3,char_array4,char_array5);
			
        }
        archivo.close();
        //d.display(root);
        //system("pause");
    }
	
	
	
}
/*
int mai2n()
{
	
	
	char w[20],m[20],n[20],o[20],p[20];
	int ch;
	char z;
	avl d,*root,*root1;
	root=NULL;
	root=d.create(root);
	//carga();

	
	//Carga de palabras en automatico
	///int ch;
	///char z;
	///avl d,*root,*root1;
	///root=NULL;
	//std::vector<Palabra> palabras;
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
	
    // copying the contents of the
    // string to char array
   
	//root=d.create(root);
	//Apertura de archivo y lectura de datos
    if (archivo.is_open()) {
        std::string linea;
        
        while (std::getline(archivo, linea)) {
        	//cout<<linea<<endl;
            std::istringstream ss(linea);
            //convierto todo a mayusculas para comparar
            //
            //Palabra palabra;
            //palabra=to_upper(palabra);
			std::getline(ss, paword1, ',');
            std::getline(ss, paword2, ',');
            std::getline(ss, paword3, ',');
            std::getline(ss, paword4, ',');
            std::getline(ss, paword5, ',');
            //Spanish
            const int length = paword1.length();
			char* char_array = new char[length + 1];
            strcpy(char_array, paword1.c_str());
            
            //english
            const int length2 = paword2.length();
			char* char_array2 = new char[length2 + 1];
  			strcpy(char_array2, paword2.c_str());
			
			//french
			const int length3 = paword3.length();
			char* char_array3 = new char[length3 + 1];
  			strcpy(char_array3, paword3.c_str());
			
			//german
			const int length4 = paword4.length();
			char* char_array4 = new char[length4 + 1];
			strcpy(char_array4, paword4.c_str());
			
			//italian
			const int length5 = paword5.length();
			char* char_array5 = new char[length5 + 1];
			strcpy(char_array5, paword5.c_str());
			
			//root=d.insert(root,char_array,char_array2, char_array3,char_array4,char_array5);
			
        }
        archivo.close();
        //d.display(root);
    }
	
	//root=d.insert(root,w,m);
	//char w[20],m[50];
	cout<<"*******************CREATION OF AVL*****************";
	do
	{
		cout<<"\n 1.Create \n 2. Insert \n 3.Delete \n 4.Display\n 5.Update\n 6.Descending order\n 7.Exit";
		cout<<"\n Enter your choice : ";
		cin>>ch;
		switch(ch)
		{
		//case 1:root=d.create(root);
	    //           break;

		case 2:cout<<"\n Enter the spanish :";
		       cin>>w;
		       cout<<"\n Enter the english :";
		       cin>>m;
		       cout<<"\n Enter the french :";
		       cin>>n;
		       cout<<"\n Enter the german :";
		       cin>>o;
		       cout<<"\n Enter the italian :";
		       cin>>p;
		       //root=d.insert(root,w,w,m,n,o,p);
		       break;

		case 3:cout<<"\n Enter spanish you want to delete : ";
		       cin>>w;
		       root=d.Delete(root,w);
		       break;

		case 4:cout<<"\n spanish in ascending order : ";
		       d.display(root);
		       break;

		case 5:d.update(root);
		       break;

		case 6:cout<<"\n spanish in decending order : ";
		       root1=d.mirror(root);
		       d.display(root1);
		       break;

		case 7:cout<<"\n EXIT!";
		}
		cout<<"\n Do you want to continue?"<<endl;
		cin>>z;
	}while(z=='Y'||z=='y');
	return 0;
}
*/
//// FIN DE LA AGREGACION DE ESTRUCTURA DE ARBOL AVL


//Se define estructura para cada idioma
struct Palabra {
    std::string espanol;
    std::string italiano;
    std::string frances;
    std::string aleman;
    std::string ingles;
};



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
	
	/* ESTA SECCION SE SUSTITUYE PARA USAR ARBOL AVL 10052023
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
    } */
    /////carga();
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
		cout<<"#############################################Para Salir escriba SALIR#"<<endl;
		gotoxy(50,13);
		cout<<""<<endl;
		gotoxy(50,14);
		d.update(root);
		/*
		system("pause");
		cout<<"salio de funcion del arbol... "<<endl;
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
		   	 	gotoxy(50,22);
		   	 	palabra_traducida=system(c1);
		   	 	std::ifstream archivo("output.txt");
		   	 	std::getline(archivo, palabra_traducida);
		   	 	palabra=system(c1);
		   	 	cout<<"Su palabra se escribe: "<<palabra_traducida<<endl;
		   	 	
		   	 	stringstream ss;
				ss<<correlativo;
				ss>>s; 
				
				
				
				} 
				gotoxy(50,24);
				cout<<"Y se pronuncia..."<<endl;
				//cout<<"veamos la palabra traducida antes del trim "<<palabra<<endl;
				boost::trim_left( palabra_traducida );
				//cout<<"veamos la palabra traducida"<<endl;
				//cout<<"el indice de la palabra es : "<<s<<"la palabra es: "<<palabra_traducida<<endl;
				//system("pause");
				play(indice_idioma-1, s, palabra_traducida);
		   gotoxy(50,26);
		   system("pause"); 
		   
			}*/
			if(Salida) indice_idioma=0;
	} while(indice_idioma > 0);
   //if(indice_idioma!=0) buscarpalabra();
   return 0;
   //menu();	
}

void intro(){
	system("cls");
	system("color 0a");
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
	root=NULL;
	root=d.create(root);
}

//Funcion para imprimir el diccionario
void Diccionario(){
	//se usa para poder utilizar los caracteres como Ò, tildes, etc.
	setlocale(LC_ALL, ""); 
	system("color 0a");
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
		    std::cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
		    icont=12;
		}
	} 
	system("pause");
}

//Funcion para agregar las nuevas palabras
void agrega(){
	
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
  char *m1 =strdup("entro al menu");
  char *m2 = strdup("Error");
  //MSGBOX(m1 ,m2 );
  //carga archivo en arbol AVL
  
  
  //carga el perfil del usuario
  
  //fullscreen();
  miMenu.Add_Items("1. Traducir  ",1);	
  miMenu.Add_Items("2. Consultar",2);	
  miMenu.Add_Items("3. Salir ",3);	
  //miMenu.Add_Items("4. Salir    ",4);	
  
  
  //miMenu.Set_Space(2);


do{
	TextColor(10);
	system("cls");
	gotoxy(10,70);
  cout<<"usuario en sesion: "<<user<<endl;
	Say(65,12,"TRADUCTOR");
	Say(61,13,"PROGRAMACION III");
		//ires=PlaySound(folder, NULL, SND_FILENAME);
			menu_sound=true;
		//}//
		Salir=false;
		opc=0;
	if(opc==0)
		{
			SetColorB(2,19);  
			Rectangle(50,17,40,12,"#"); 
			SetColorA(2,22);  
			Say(58,15,"*** MENU PRINCIPAL ***");
			//system("pause");
			Salir=false;
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
//cout<<"va a salir...salir: "<<Salir<<endl;
Salir=false;
//system("pause");
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

void login(){
	setlocale(LC_ALL, ""); 
	int iopt;
	bool continua=false;
	std::string temp_user;
	std::string temp_pass;
	do{
		temp_user="";
		temp_pass="";
		system("cls");
		system("color 0a");
		gotoxy(50,10);
		cout<<"#####################################################################"<<endl;
		gotoxy(50,11);
		cout<<"                                login                                "<<endl;
		gotoxy(50,12);
		cout<<"#####################################################################"<<endl;
		gotoxy(50,13);
		cout<<""<<endl;
		gotoxy(50,14);
		cout<<"                       [1] Iniciar sesion"<<endl;
		gotoxy(50,15);
		cout<<"                       [2] Cambia Password"<<endl;
		gotoxy(50,16);
		cout<<"                       [3] Ingresar como invitado"<<endl;
		gotoxy(50,17);
		cout<<"                       [4] Salir"<<endl;
		gotoxy(50,18);
		cout<<"                           [   ] "<<endl;
		
		
		gotoxy(79,18);
		cin>>iopt;
		
		
	
	//system("exit");
		//inicia sesion
		if(iopt==1){
			//se tendra en una variable de entorno el usuario logueado y los datos de loguin se encriptan en un archivo de configuracion
			system("cls");
			continua=false;
			//encontrado=false;
			gotoxy(50,10);
			cout<<"#####################################################################"<<endl;
			gotoxy(50,11);
			cout<<"               usuario: "<<endl;
			
			gotoxy(50,15);
			cout<<"#####################################################################"<<endl;
			//captura user
			gotoxy(75,11);
			cin>>temp_user;
			//captura pass
			gotoxy(50,13);
			cout<<"               ContraseÒa: ";
			gotoxy(79,13);
			//string pass ="";
		    char ch;
		    temp_pass="";
		    //cout << "Enter pass\n";
		    ch = _getch();
		    while(ch != 13){//character 13 is enter
		       temp_pass.push_back(ch);
		       cout << '*';
		       ch = _getch();
		    }
			//cin>>temp_pass;
			user=temp_user;
			//cout<<"usuario: "<<user<<" password: "<<temp_pass<<endl;
			//system("pause");
			//valida el pass
			std::ifstream archivo("users.txt");
			std::string usuario;
		    std::string contrasena;
			int icont=12;
			bool encontrado=false;
			//carga el diccionario
		  	//Apertura de archivo y lectura de datos
		    if (archivo.is_open()) {
		        std::string linea;
		        
		        while (std::getline(archivo, linea)) {
		            std::istringstream ss(linea);
		            //convierto todo a mayusculas para comparar
		            
		            //Palabra palabra;
		            //palabra=to_upper(palabra);
					std::getline(ss, usuario, ',');
		            std::getline(ss, contrasena, ',');
		            
		            if(usuario==user){
		            	encontrado=true;
		            	continua=false;
		            	if(cifrado(temp_pass)==contrasena) {
		            		//cout<<"encontro el usuario y pass"<<endl;
		            		char *m1 =strdup("Encontro el pass");
							char *m2 = strdup("Error");
							//MSGBOX(m1 ,m2 );
							continua=true;
		            	}
						if(!continua){
		            		gotoxy(50,17);
		            		cout<<"Usuario o contraseÒa incorrectos, intente de nuevo o cree un usuario";
		            		gotoxy(50,18);
		            		system("pause");
						}
					}
		        }
		        
		        archivo.close();
		        if(!encontrado){
		        	gotoxy(50,17);
		        	cout<<"Su usuario no existe, procederemos a crearlo y podra ingresar una proxima vez";
		        	system("pause");
		        	std::ofstream myfile("users.txt", ios::app);
		        	myfile <<user<<","<<cifrado(temp_pass)<<"\n";
  					myfile.close();
				}
		    } else {
		    	
		        std::cout << "No se pudo abrir el archivo del usuarios, \npor favor consulte con el administrador, \niniciara sesion como invitado" << std::endl;
		        //system("pause");
		        //return 1;
		    }
			if(continua) {
				char *m1 =strdup("Continua");
				char *m2 = strdup("Error");
				//MSGBOX(m1 ,m2 );
				menu();
			}
		} else {
			//crea usuario
			if(iopt==2){
				
				menu();
			} else {
			
				//invitado
				if(iopt==3){
					user="Invitado";
					menu();
				} else {
					char *m1 =strdup("Opcion no valida");
					char *m2 = strdup("Error");
					if(iopt!=4) MSGBOX(m1 ,m2 );
				}
			}
		
		}
		
	} while (iopt!=4);
	salida();
//	system("pause");
}
/*
void intento(){
	
	string texto="g4U2g9U3g2U3g3U1g3";
	string temp = "";
	string caracter[]="";
	string texto2;
	string k1;
	string k2;
	string k3;
	
	string nombreArchivo = "llave.txt";
	ifstream archivo(nombreArchivo.c_str());
	string linea;
	
	
	// Obtener l√≠nea de archivo, y almacenar contenido en "linea"
	getline(archivo, linea);
    //cout<<"Dato original: "<<palabra<<endl;
    k1=linea[0];
    k2=linea[1];
    k3=linea[2];
	//descifrado(texto);
	
	
	for(int i=1; i<=texto.length();;i++){
		//if((texto[i] ==char("g")) or (texto[i] == char("U")) or (texto[i] == char("m"))){
		caracter= texto[i];
		size_t found = k1.find(palabra[i]);
		if (found != string::npos){
		    res = 0;
			//cout<<palabra[i]<<" Es Vocal..."<<endl;
			letra = palabra[i];
			//convierte y guarda
			//es vocal
			if(temp[0]=="U"){
				if("U1") texto2+="a";
				if("U2") texto2+="e";
				if("U3") texto2+="i";
				if("U4") texto2+="o";
				if("U5") texto2+="u";
				if("U6") texto2+="A";
				if("U7") texto2+="E";
				if("U8") texto2+="I";
				if("U9") texto2+="O";
				if("U10") texto2+="U";
			}
			//es consonante minuscula
			if(temp[0]=="m"){
				if("m1") texto2+="b";
				if("m2") texto2+="c";
				if("m3") texto2+="d";
				if("m4") texto2+="f";
				if("m5") texto2+="g";
				if("m6") texto2+="h";
				if("m7") texto2+="j";
				if("m8") texto2+="k";
				if("m9") texto2+="l";
				if("m10") texto2+="m";
				if("m11") texto2+="n";
				if("m12") texto2+="Ò";
				if("m13") texto2+="p";
				if("m14") texto2+="q";
				if("m15") texto2+="r";
				if("m16") texto2+="s";
				if("m17") texto2+="t";
				if("m18") texto2+="v";
				if("m19") texto2+="w";
				if("m20") texto2+="x";
				if("m21") texto2+="y";
				if("m22") texto2+="z";
			}
			//es consonante mayuscula
			if(temp[0]=="g"){
				if("g1") texto2+="B";
				if("g2") texto2+="C";
				if("g3") texto2+="D";
				if("g4") texto2+="F";
				if("g5") texto2+="G";
				if("g6") texto2+="H";
				if("g7") texto2+="J";
				if("g8") texto2+="K";
				if("g9") texto2+="L";
				if("g10") texto2+="M";
				if("g11") texto2+="N";
				if("g12") texto2+="—";
				if("g13") texto2+="P";
				if("g14") texto2+="Q";
				if("g15") texto2+="R";
				if("g16") texto2+="S";
				if("g17") texto2+="T";
				if("g18") texto2+="V";
				if("g19") texto2+="W";
				if("g20") texto2+="X";
				if("g21") texto2+="Y";
				if("g22") texto2+="Z";
			}
			//limpia la temp
			temp=texto[i];
		} else {
			temp+=texto[i];
		}
	}
	cout<<"la palabra original era: "<<texto<<" y la descifrada es: "<<texto2<<endl;
}
*/
//Metodo principal para llamar las distintas funciones
int main() {
	//intento();
	//system("pause");
	//limpia archivos 2??.wav para evitar problemas
	system("del c:\\lib\\voices\\200.wav /s");
	system("del c:\\lib\\voices\\201.wav /s");
	system("del c:\\lib\\voices\\202.wav /s");
	system("del c:\\lib\\voices\\203.wav /s");
	system("del c:\\lib\\voices\\204.wav /s");
	system("del c:\\lib\\voices\\205.wav /s");
	system("cls");
	//carga();
	fullscreen();
	//defaults();
	//buscarpalabra();
	//system("pause");
	//fullscreen();
	intro();
	carga();
	//carga_diccionario();
	login();
	
	//string palabra;
	//cout<<"Por favor ingrese la palabra a cifrar"<<endl;
	//cin>>palabra;
	//cifrado(palabra);
	
	return 0;
}
