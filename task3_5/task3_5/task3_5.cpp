/*
* @file			task3_5.cpp
* @brief		Program finds combination of characters in sentences and delete words with them.

* Copyright 2014 by Yuliia Lyubchik Inc.,
*
* This software is the confidential and proprietary information
* of Yuliia Lyubchik. ("Confidential Information").  You
* shall not disclose such Confidential Information and shall use
* it only with permission from Yuliia.
*
*/

#include "stdafx.h"
#include "task3_5.h"	/*defines prototypes of used in this file functions*/
#include <stdlib.h>



int main( )
{
	Interface();

#ifdef USE_MY_DLL
	if (Check_Loading_Library() == FAIL)
	{
		puts("Can't load library.");
		return (int)FAIL;
	}
#endif

	char* riadok = NULL;
	char* combination = NULL;
	unsigned char retCode;
	char* result = NULL;


	retCode = Input(&riadok, &combination);

	if (retCode == FAIL)
	{
		puts("Error occurs while trying to input string.\n");
		return (int)FAIL;
	}
	puts("String after deleted words with defined combination: \n");

	result = Delete_words(riadok, combination );
	if (result == NULL)
	{
		puts("Error occurs while trying to find combinations.\n");
		free(riadok);
		return (int)FAIL;
	}

	puts(".");
	free(riadok);
	system("pause");
	return MAIN_SUCCESS;
}
