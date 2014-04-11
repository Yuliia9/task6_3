/*
*@file		functions.cpp
*@brief		implements functions used in file task3_5.cpp
			uses developed dll and lib library for working with C string
*/
#include "stdafx.h"
#include "task3_5.h"
#include <stdlib.h>


typedef int(*STRLEN_PRINT) (const char*);
typedef char* (*STRTOK_CPY_CAT) (char*, const char*);
typedef char* (*STRSTR) (const char*, const char*);


#ifdef USE_STRING_H
#include <string.h>
#define STREND '\0'
STRLEN_PRINT mystrlen = (STRLEN_PRINT)strlen;
STRLEN_PRINT myprintf = puts;
STRTOK_CPY_CAT mystrtok = (STRTOK_CPY_CAT)strtok;
STRTOK_CPY_CAT mystrcpy = (STRTOK_CPY_CAT)strcpy;
STRSTR mystrstr = (STRSTR)strstr;
STRTOK_CPY_CAT mystrcat = (STRTOK_CPY_CAT)strcat;


#elif defined (USE_MY_LIB)
#include "my_string.h"
STRLEN_PRINT mystrlen = (STRLEN_PRINT)my_strlen;
STRLEN_PRINT myprintf = (STRLEN_PRINT)my_strprintf;
STRTOK_CPY_CAT mystrtok = (STRTOK_CPY_CAT)my_strtok;
STRTOK_CPY_CAT mystrcpy = (STRTOK_CPY_CAT)my_strcpy;
STRSTR mystrstr = (STRSTR)my_strstr;
STRTOK_CPY_CAT mystrcat = (STRTOK_CPY_CAT)my_strcat;


#elif defined (USE_MY_DLL) 
#include <windows.h> 
HINSTANCE stringdll = LoadLibrary(TEXT("stringdll.dll"));
char* end = (char*)GetProcAddress(stringdll, LPCSTR("STREND"));
const char STREND = *end;
STRLEN_PRINT mystrlen = (STRLEN_PRINT)GetProcAddress(stringdll, LPCSTR("my_strlen"));
STRLEN_PRINT myprintf = (STRLEN_PRINT)GetProcAddress(stringdll, LPCSTR("my_strprintf"));
STRTOK_CPY_CAT mystrtok = (STRTOK_CPY_CAT)GetProcAddress(stringdll, LPCSTR("my_strtok"));
STRTOK_CPY_CAT mystrcpy = (STRTOK_CPY_CAT)GetProcAddress(stringdll, LPCSTR("my_strcpy"));
STRTOK_CPY_CAT mystrcat = (STRTOK_CPY_CAT)GetProcAddress(stringdll, LPCSTR("my_strcat"));
STRSTR mystrstr = (STRSTR)GetProcAddress(stringdll, LPCSTR("my_strstr"));

unsigned int Check_Loading_Library(void)
{
	if (stringdll == NULL)
	{
		return FAIL;
	}
	else if (end == NULL || mystrlen == NULL || myprintf == NULL || mystrtok == NULL)
	{
		return FAIL;
	}
	else if (mystrcpy == NULL || mystrcat == NULL || mystrstr == NULL)
	{
		return FAIL;
	}
}
#endif


void Interface(void)
{
	puts("------------------------------------------------------------------");
	puts("Hi! Welcome to the genius characters finder.");
	puts("Enter sentences and combination of characters ");
	puts("and program will delete for you words that include that combination. ");
	puts("Program made by Yuliia Lyubchik.");
	puts("------------------------------------------------------------------\n");
}


unsigned char Input(char** riadok, char** combination)
{
	unsigned char retCode;
	unsigned int count;
	do
	{
		char temp;
		count = 0;
		printf("Please enter sentence: ");
		do
		{
			scanf("%c", &temp);
			++count;
			*riadok = (char*)realloc(*riadok, count * sizeof(char));

			if (*riadok != NULL)
			{
				*(*riadok + count - 1) = temp;
			}
			else
			{
				free(riadok);
				return FAIL;
			}

		} 
		while (temp != '\n' && temp != EOF);
		fflush(stdin);
		*(*riadok + count - 1) = STREND;
	} 
	while (riadok == NULL || mystrlen(*riadok) == 0);

	count = 0;
	retCode = FAIL;
	do
	{
		char temp;
		printf("Please enter combination of characters that you want to find: ");
		do
		{
			scanf("%c", &temp);
			if (temp >= 'A' && temp <= 'Z')
			{
				retCode = SUCCESS;
			}
			else if (temp >= 'a' && temp <= 'z')
			{
				retCode = SUCCESS;
			}
			++count;
			*combination = (char*)realloc(*combination, count * sizeof(char));

			if (*combination != NULL)
			{
				*(*combination + count - 1) = temp;
			}
			else
			{
				free(combination);
				return FAIL;
			}

		} 
		while (temp != '\n' && temp != EOF && retCode != FAIL);
		fflush(stdin);
		*(*combination + count - 1) = STREND;
	} 
	while (retCode == FAIL || combination == NULL || mystrlen(*combination) == 0);

	return SUCCESS;
}



char* Delete_words(const char* riadok, const char* combination)
{
	if (*riadok == NULL || combination == NULL)
	{
		return FAIL;
	}

	char* temp;
	char* token;
	char* finder;
	int len = mystrlen(riadok);
	char* copy = (char*)malloc(len * sizeof(char));
	copy = mystrcpy(copy, riadok);
	const char delimiters[] = { ' ', ',', '-', '.', ':', ';', '(', ')', '[', ']', '!', '?', STREND };
	const char newdelim[] = { ' ', STREND };


	temp = (char*)calloc(len, sizeof(char));
	*temp = STREND;
	if (temp == NULL)
	{
		return FAIL;
	}
	token = mystrtok(copy, delimiters);
	while (token != NULL)
	{
		finder = mystrstr(token, combination);
		if (finder == NULL)
		{
			temp = mystrcat(temp, token);
			temp = mystrcat(temp, newdelim);
		}
		token = mystrtok(NULL, delimiters);
	}

	copy = mystrcpy(copy, temp);
	if (copy != NULL)
	{
		myprintf(copy);
	}
#ifdef USE_MY_DLL
	FreeLibrary(stringdll);
#endif
	return copy;
}


