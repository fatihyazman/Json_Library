#include "json_deserialize.h"
/*
  ******************************************************************************
  * File           		: json_deserialize.c
  * Brief description   : json_deserialize.h dosyasýndaki tanýmlamalarýn içeriðini içerir
  ******************************************************************************
  *
  * Author				: Fatih YAZMAN
  *	Web					: www.fatihyazman.com
  * Contact				: iletisim@fatihyazman.com - fatihyazman16@gmail.com
  *
  ******************************************************************************
  */
  
char JsonBuffer[JsonBufferSize];

enum D_JsonResult_t JsonState(void)
{	
	     if(JsonBuffer[0] != '{') return BadJson;
	else if(JsonBuffer[strlen(JsonBuffer) - 1]  != '}') return BadJson;
	else if(strchr(JsonBuffer, '"') == '\0') return BadJson;
	else if(strchr(JsonBuffer, ':') == '\0') return BadJson;
	
	return JsonSuccess;
}

int KelimeArama(const char* Cumle, const char* Aranan)
{
	if(JsonState() == BadJson)
		return BadJson;
		
	int ArananSayac = 0;
	uint8_t State = 1;
	uint32_t Index = -1;
	for (int i = 0; i < strlen(Cumle); i++)
	{
		if (Cumle[i] == Aranan[ArananSayac])
		{
			ArananSayac++;
			for (int x = 1; x < strlen(Aranan); x++)
			{
				if (Cumle[i + ArananSayac] != Aranan[ArananSayac])
				{
					ArananSayac = 0;
					State = 0;
					break;
				}
				else
				{
					ArananSayac++;
					State = 1;
				}
			}
			if (State == 1)
			{
				Index = i;
				break;
			}
		}
	}
	if (State == 1)
	{
		return (Index += strlen(Aranan)) - 1;
	}
	else
		return -1;
}


enum D_JsonResult_t JsonGetInt(int *Return, const char* ValueName)
{
	if(JsonState() == BadJson)
		return BadJson;
		
	int Index = KelimeArama(JsonBuffer, ValueName);
	char CharValue[NumberMaxSize];
	if (Index == -1)
		return NotFound;
	else
	{
		Index += 3;
		int i = 0;
		while (1)
		{
			if (i == 0)
			{
				if (JsonBuffer[Index + i] == '-'
						|| (((int) JsonBuffer[Index + i]) <= 57
								&& ((int) JsonBuffer[Index + i]) >= 48))
					CharValue[i] = JsonBuffer[Index + i];
				else
					return BadParamater;
			}
			else
			{
				if ((((int) JsonBuffer[Index + i]) <= 57
						&& ((int) JsonBuffer[Index + i]) >= 48))
				{
					CharValue[i] = JsonBuffer[Index + i];
				}
				else
				{
					break;
				}
			}

			i++;
		}
	}
	*Return = atoi(CharValue);
	return JsonSuccess;
}

enum D_JsonResult_t JsonGetDouble(double *Return, const char* ValueName)
{
	if(JsonState() == BadJson)
		return BadJson;
	
	int Index = KelimeArama(JsonBuffer, ValueName);
	char CharValue[NumberMaxSize];
	if (Index == -1)
		return NotFound;
	else
	{
		Index += 3;
		int i = 0;
		while (1)
		{
			if (i == 0)
			{
				if (JsonBuffer[Index + i] == '-'
						|| (((int) JsonBuffer[Index + i]) <= 57
								&& ((int) JsonBuffer[Index + i]) >= 48))
					CharValue[i] = JsonBuffer[Index + i];
				else
					return BadParamater;
			}
			else
			{
				if (JsonBuffer[Index + i] == '.' || JsonBuffer[Index + i] == ','
						|| (((int) JsonBuffer[Index + i]) <= 57
								&& ((int) JsonBuffer[Index + i]) >= 48))
				{
					CharValue[i] = JsonBuffer[Index + i];
				}
				else
				{
					break;
				}
			}

			i++;
		}
	}
	*Return = strtod(CharValue, NULL);
	return JsonSuccess;
}

enum D_JsonResult_t JsonGetFloat(float *Return, const char* ValueName)
{
	if(JsonState() == BadJson)
		return BadJson;
		
	int Index = KelimeArama(JsonBuffer, ValueName);
	char CharValue[NumberMaxSize];
	if (Index == -1)
		return NotFound;
	else
	{
		Index += 3;
		int i = 0;
		while (1)
		{
			if (i == 0)
			{
				if (JsonBuffer[Index + i] == '-'
						|| (((int) JsonBuffer[Index + i]) <= 57
								&& ((int) JsonBuffer[Index + i]) >= 48))
					CharValue[i] = JsonBuffer[Index + i];
				else
					return BadParamater;
			}
			else
			{
				if (JsonBuffer[Index + i] == '.' || JsonBuffer[Index + i] == ','
						|| (((int) JsonBuffer[Index + i]) <= 57
								&& ((int) JsonBuffer[Index + i]) >= 48))
				{
					CharValue[i] = JsonBuffer[Index + i];
				}
				else
				{
					break;
				}
			}

			i++;
		}
	}
	*Return = atof(CharValue);
	return JsonSuccess;
}

enum D_JsonResult_t JsonGetString(char *Return, const char* ValueName)
{
	if(JsonState() == BadJson)
		return BadJson;
		
	int StartIndex = KelimeArama(JsonBuffer, ValueName);
	char CharValue[StringMaxSize];
	if (StartIndex == -1)
		return NotFound;
	else
	{
		StartIndex += 3;
		if (JsonBuffer[StartIndex] != '"')
			return BadJson;
		else
			StartIndex++;

		int EndIndex = 0;
		while (1)
		{
			if (JsonBuffer[StartIndex + EndIndex] == '"')
			{

				//if(JsonBuffer[(StartIndex + EndIndex) - 1] != '\\')
				break;
			}
			EndIndex++;
		}
		EndIndex += StartIndex;

		int y = 0;
		for (int i = StartIndex; i < sizeof(JsonBuffer); i++)
		{
			if (i < EndIndex)
				CharValue[y] = JsonBuffer[i];
			else
				CharValue[y] = '\0';
			y++;
		}
	}
	int x;
	for (x = 0; x < strlen(JsonBuffer); x++)
		Return[x] = CharValue[x];
	Return[x] = '\0';

	return JsonSuccess;
}
//arrays
enum D_JsonResult_t JsonGetIntArray(int *Return, int *len,
		const char* ValueName)
{
	if(JsonState() == BadJson)
		return BadJson;
		
	int StartIndex = KelimeArama(JsonBuffer, ValueName);
	char CharValue[StringMaxSize];
	if (StartIndex == -1)
		return NotFound;
	else
	{
		StartIndex += 3;
		if (JsonBuffer[StartIndex] != '[')
			return BadJson;
		else
			StartIndex++;

		int EndIndex = 0;
		while (1)
		{
			if (JsonBuffer[StartIndex + EndIndex] == ']')
				break;

			EndIndex++;
		}
		EndIndex += StartIndex;

		int y = 0;
		for (int i = StartIndex; i < sizeof(JsonBuffer); i++)
		{
			if (i < EndIndex)
				CharValue[y] = JsonBuffer[i];
			else
				CharValue[y] = '\0';
			y++;
		}

		const char s[2] = ",";
		char *token;
		/* get the first token */
		token = strtok((char*) CharValue, s);
		int x = 0;
		while (token != NULL)
		{
			Return[x] = atoi(token);
			x++;
			token = strtok(NULL, s);
		}
		*len = x;
		return JsonSuccess;
	}
}

enum D_JsonResult_t JsonGetDoubleArray(double *Return, int *len,
		const char* ValueName)
{
	if(JsonState() == BadJson)
		return BadJson;
		
	int StartIndex = KelimeArama(JsonBuffer, ValueName);
	char CharValue[StringMaxSize];
	if (StartIndex == -1)
		return NotFound;
	else
	{
		StartIndex += 3;
		if (JsonBuffer[StartIndex] != '[')
			return BadJson;
		else
			StartIndex++;

		int EndIndex = 0;
		while (1)
		{
			if (JsonBuffer[StartIndex + EndIndex] == ']')
				break;

			EndIndex++;
		}
		EndIndex += StartIndex;

		int y = 0;
		for (int i = StartIndex; i < sizeof(JsonBuffer); i++)
		{
			if (i < EndIndex)
				CharValue[y] = JsonBuffer[i];
			else
				CharValue[y] = '\0';
			y++;
		}

		const char s[2] = ",";
		char *token;
		/* get the first token */
		token = strtok((char*) CharValue, s);
		int x = 0;
		while (token != NULL)
		{
			Return[x] = strtod(token, NULL);
			x++;
			token = strtok(NULL, s);
		}
		*len = x;
		return JsonSuccess;
	}
}

enum D_JsonResult_t JsonGetFloatArray(float *Return, int *len,
		const char* ValueName)
{
	if(JsonState() == BadJson)
		return BadJson;
		
	int StartIndex = KelimeArama(JsonBuffer, ValueName);
	char CharValue[StringMaxSize];
	if (StartIndex == -1)
		return NotFound;
	else
	{
		StartIndex += 3;
		if (JsonBuffer[StartIndex] != '[')
			return BadJson;
		else
			StartIndex++;

		int EndIndex = 0;
		while (1)
		{
			if (JsonBuffer[StartIndex + EndIndex] == ']')
				break;

			EndIndex++;
		}
		EndIndex += StartIndex;

		int y = 0;
		for (int i = StartIndex; i < sizeof(JsonBuffer); i++)
		{
			if (i < EndIndex)
				CharValue[y] = JsonBuffer[i];
			else
				CharValue[y] = '\0';
			y++;
		}

		const char s[2] = ",";
		char *token;
		/* get the first token */
		token = strtok((char*) CharValue, s);
		int x = 0;
		while (token != NULL)
		{
			Return[x] = atof(token);
			x++;
			token = strtok(NULL, s);
		}
		*len = x;
		return JsonSuccess;
	}
}

unsigned char StringArray[ArrayMaxSize][StringMaxSize];
enum D_JsonResult_t JsonGetStringArray(int *len, const char* ValueName)
{
	if(JsonState() == BadJson)
		return BadJson;
		
	int StartIndex = KelimeArama(JsonBuffer, ValueName);
	char CharValue[StringMaxSize];
	if (StartIndex == -1)
		return NotFound;
	else
	{
		StartIndex += 3;
		if (JsonBuffer[StartIndex] != '[')
			return BadJson;
		else
			StartIndex++;

		int EndIndex = 0;
		while (1)
		{
			if (JsonBuffer[StartIndex + EndIndex] == ']')
				break;

			EndIndex++;
		}
		EndIndex += StartIndex;

		int y = 0;
		for (int i = StartIndex; i < sizeof(JsonBuffer); i++)
		{
			if (i < EndIndex)
				CharValue[y] = JsonBuffer[i];
			else
				CharValue[y] = '\0';
			y++;
		}

		for (int i = 0, y = 0; i < EndIndex; i++)
		{
			if (CharValue[i] == '"')
			{
				i++;
				for (int x = i, z = 0; CharValue[i] != '"'; i++, x++, z++)
				{
					StringArray[y][z] = CharValue[x];
				}
				y++;
				*len = y;
			}

		}
		return JsonSuccess;
	}
}

