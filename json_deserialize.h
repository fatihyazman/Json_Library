/*
  ******************************************************************************
  * File           		: json_deserialize.h
  * Brief description   : json_deserialize.c dosyas�n�n headeri, Bu dosya tanmlamalar� i�erir.
  ******************************************************************************
  *	
  * Author				: Fatih YAZMAN
  * Web					: www.fatihyazman.com
  * Contact				: iletisim@fatihyazman.com - fatihyazman16@gmail.com
  *
  ******************************************************************************
  */


#ifndef _JSON_DESERIALIZE
#define _JSON_DESERIALIZE

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define StringMaxSize 100	//String de�i�ken i�eri�inin maksimum karakter uzunlu�u.
#define ArrayMaxSize 100	//Json dizilerinin maksimum eleman say�s�.	
#define NumberMaxSize 20	//Maksimum say� uzunlu�u. (64 bit sisteme g�re hesaplanm��t�r.)
#define JsonBufferSize 400	//Json'un maksimum karakter uuznlu�u

extern char JsonBuffer[JsonBufferSize]; //��z�mlenecek json format� bu diziye kopyalan�r.

enum D_JsonResult_t	
{
	JsonSuccess = 0,	//Json ��z�mleme i�lemi ba�ar�l�.
	NotFound,			//Arad���n�z parametre(de�i�ken) bulunamad�.
	BadJson,			//Json Format� hatal�.
	BadParamater		//Arad���n�z parametrenin(de�i�kenin) i�eri�i hatal�.
};



//Fonksiyonlar D_JsonResult_t enum tipinde geri d�n�� yapar.
enum D_JsonResult_t JsonState(void);	//Json format�n�n do�rulu�unu kontrol eder.

//ValueName parametresine json i�erisinde aranan de�i�ken g�nderilir.
enum D_JsonResult_t JsonGetInt(int *Return, const char* ValueName); 		//Json ValueName parametresine verilen de�i�kenin i�eri�indeki de�eri integer olarak pointer ile d�nd�r�r.
enum D_JsonResult_t JsonGetDouble(double *Return, const char* ValueName);	//Json ValueName parametresine verilen de�i�kenin i�eri�indeki de�eri double olarak pointer ile d�nd�r�r.
enum D_JsonResult_t JsonGetFloat(float *Return, const char* ValueName);		//Json ValueName parametresine verilen de�i�kenin i�eri�indeki de�eri float olarak pointer ile d�nd�r�r.
enum D_JsonResult_t JsonGetString(char *Return, const char* ValueName); 	//Json ValueName parametresine verilen de�i�kenin i�eri�indeki de�eri char dizisi olarak pointer ile d�nd�r�r, Return parametresine dizinin ilk eleman�n�n adresi g�nderilir

//Arrays
//len Parametreleri dizideki eleman say�s�n� d�nd�r�r.
//Return parametreleri elemanlar� dizi olarak d�nd�r�r.
//Return parametresine dizinin ilk eleman�n�n adresi g�nderilir.
enum D_JsonResult_t JsonGetIntArray(int *Return, int *len, const char* ValueName); 		//Integer t�r�nde json dizileri i�in kullan�l�r
enum D_JsonResult_t JsonGetDoubleArray(double *Return, int *len, const char* ValueName);//Double t�r�nde json dizileri i�in kullan�l�r
enum D_JsonResult_t JsonGetFloatArray(float *Return, int *len, const char* ValueName);	//Float t�r�nde json dizileri i�in kullan�l�r

extern unsigned char StringArray[ArrayMaxSize][StringMaxSize];				//String dizilerinde "JsonGetStringArray" fonksiyonu �a��r�ld�ktan sonra  veriler "StringArray" dizisinden okunur.
enum D_JsonResult_t JsonGetStringArray(int *len, const char* ValueName);	//String t�r�nde json dizileri i�in kullan�l�r

#endif

