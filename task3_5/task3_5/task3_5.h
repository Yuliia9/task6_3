#ifndef TASK3_5_H_
#define TASK3_5_H_
/*
*@file		task3_5.h
*@brief		header file that defines prototypes of functions used in file task3_5.cpp
*/

#include "stdafx.h"

/*for choosing what library to use*/
//#define USE_STRING_H
//#define USE_MY_LIB
#define USE_MY_DLL

const unsigned char FAIL = 0;
const unsigned char SUCCESS = 1;
const unsigned int MAIN_SUCCESS = 0;


/**
* @brief				This function displays general information about program to users
* @param	void
* @return	void
*/
void Interface(void);

/**
* @brief				This function checks if string dll library was loaded
* @param	void
* @return	void
*/
unsigned int Check_Loading_Library(void);

/*
* @brief					Function for inputing string (sentences)
* @param	[in/out]		char** riadok - a pointer to null pointer to string for sentences
			[in/out]		char** combination - a pointer to null pointer to combination of characters needed to be find
*
*@return	unsigned char	Return ERROR if error occurs while trying to allocate memory for string
							Return SUCCESS if strings were inputed
*/
unsigned char Input(char** riadok, char** combination);


/*
* @brief					Function for delete words with defined combination of characters
* @param	[in/out]		char** copy - a pointer to pointer to new string contained sentence after deleting words
			[in]			const char** combination - a pointer to combination of characters needed to be find
*
*@return	unsigned char	Return ERROR if error occurs while trying to get access to data
							Return SUCCESS if words were deleted
*/
char* Delete_words(const char* riadok, const char* combination);


#endif