#pragma once
#include "stdafx.h"
#include "LexAnalize.h"
#include "FST.h"

struct PN
{
	LT::Entry result[LT_MAXSIZE]; // преобразованное выражение в польской нотации
	enum { LH = '(', RH = ')', PLUS = '+', MINUS = '-', MULT = '*', DEV = '/', EQUAL = '=' };
	int size = 0;

	int priority(char operation); 
	int search(int number, LA::LEX *tables); // Поиск начала выражения в таблице лексем
	bool CreatePolishNotation(LA::LEX *tables);
};
