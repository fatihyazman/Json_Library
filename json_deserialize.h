/*
  ******************************************************************************
  * File           		: json_deserialize.h
  * Brief description   : json_deserialize.c dosyasýnýn headeri, Bu dosya tanmlamalarý içerir.
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

#define StringMaxSize 100	//String deðiþken içeriðinin maksimum karakter uzunluðu.
#define ArrayMaxSize 100	//Json dizilerinin maksimum eleman sayýsý.	
#define NumberMaxSize 20	//Maksimum sayý uzunluðu. (64 bit sisteme göre hesaplanmýþtýr.)
#define JsonBufferSize 400	//Json'un maksimum karakter uuznluðu

extern char JsonBuffer[JsonBufferSize]; //çözümlenecek json formatý bu diziye kopyalanýr.

enum D_JsonResult_t	
{
	JsonSuccess = 0,	//Json çözümleme iþlemi baþarýlý.
	NotFound,			//Aradýðýnýz parametre(deðiþken) bulunamadý.
	BadJson,			//Json Formatý hatalý.
	BadParamater		//Aradýðýnýz parametrenin(deðiþkenin) içeriði hatalý.
};



//Fonksiyonlar D_JsonResult_t enum tipinde geri dönüþ yapar.
enum D_JsonResult_t JsonState(void);	//Json formatýnýn doðruluðunu kontrol eder.

//ValueName parametresine json içerisinde aranan deðiþken gönderilir.
enum D_JsonResult_t JsonGetInt(int *Return, const char* ValueName); 		//Json ValueName parametresine verilen deðiþkenin içeriðindeki deðeri integer olarak pointer ile döndürür.
enum D_JsonResult_t JsonGetDouble(double *Return, const char* ValueName);	//Json ValueName parametresine verilen deðiþkenin içeriðindeki deðeri double olarak pointer ile döndürür.
enum D_JsonResult_t JsonGetFloat(float *Return, const char* ValueName);		//Json ValueName parametresine verilen deðiþkenin içeriðindeki deðeri float olarak pointer ile döndürür.
enum D_JsonResult_t JsonGetString(char *Return, const char* ValueName); 	//Json ValueName parametresine verilen deðiþkenin içeriðindeki deðeri char dizisi olarak pointer ile döndürür, Return parametresine dizinin ilk elemanýnýn adresi gönderilir

//Arrays
//len Parametreleri dizideki eleman sayýsýný döndürür.
//Return parametreleri elemanlarý dizi olarak döndürür.
//Return parametresine dizinin ilk elemanýnýn adresi gönderilir.
enum D_JsonResult_t JsonGetIntArray(int *Return, int *len, const char* ValueName); 		//Integer türünde json dizileri için kullanýlýr
enum D_JsonResult_t JsonGetDoubleArray(double *Return, int *len, const char* ValueName);//Double türünde json dizileri için kullanýlýr
enum D_JsonResult_t JsonGetFloatArray(float *Return, int *len, const char* ValueName);	//Float türünde json dizileri için kullanýlýr

extern unsigned char StringArray[ArrayMaxSize][StringMaxSize];				//String dizilerinde "JsonGetStringArray" fonksiyonu çaðýrýldýktan sonra  veriler "StringArray" dizisinden okunur.
enum D_JsonResult_t JsonGetStringArray(int *len, const char* ValueName);	//String türünde json dizileri için kullanýlýr

#endif

