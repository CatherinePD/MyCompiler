#pragma once
#include "stdafx.h"
#define MAX_STRING 255
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_MAX_STRING_CODE 1024
#define IN_CODE_ENDL '\n'
#define IN_CODE_SPACE ' '
#define IN_CODE_NULL '\0'

/*
SEP - ( ) * + - = , / { } ;
PR - пробел и TAB
NS - новая строка
F - запрещённый
T - разрешённый
I - игнорируемый
L - '
*/

#define IN_CODE_TABLE {\
		/*0*/	/*1*/  /*2*/  /*3*/  /*4*/  /*5*/  /*6*/  /*7*/  /*8*/     /*9*/    /*A*/    /*B*/    /*C*/     /*D*/   /*E*/  /*F*/\
/*0*/	IN::F,  IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,   IN::PR,  IN::NS,   IN::F,   IN::F,   IN::I,   IN::F, IN::F,\
/*1*/	IN::F,  IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,   IN::F,   IN::F,    IN::F,   IN::F,   IN::F,   IN::F, IN::F,\
/*2*/	IN::PR, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::L, IN::SEP, IN::SEP, IN::SEP,  IN::SEP, IN::SEP, IN::SEP, IN::T, IN::SEP,\
/*3*/	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::SEP, IN::F,   IN::SEP, IN::F, IN::T,\
/*4*/	IN::F,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::T,   IN::T,   IN::T,   IN::T, IN::T,\
/*5*/	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::F,   IN::F,   IN::F,   IN::F, IN::F,\
/*6*/	IN::F,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::T,   IN::T,   IN::T,   IN::T, IN::T,\
/*7*/	IN::T,  IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::SEP, IN::F,   IN::SEP, IN::F, IN::F,\
		 /*0*/	/*1*/  /*2*/  /*3*/  /*4*/  /*5*/  /*6*/  /*7*/  /*8*/  /*9*/  /*A*/  /*B*/  /*C*/  /*D*/  /*E*/  /*F*/\
/*8*/	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
/*9*/	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
/*A*/	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
/*B*/	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
/*C*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*D*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*E*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
/*F*/	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,\
}  

namespace In
{
	struct Words
	{
		char word[1024];
		int line; // строка в которой находится слово
		static int amount;  // количество слов
	};

	struct IN
	{
		enum { T = 1, F, I, NS, SEP, L, PR };
		int code[256] = IN_CODE_TABLE;
		int size = NULL;
		int lines = NULL; //сделать нумерацию с 1?
		int ignor = NULL;
		bool flag = 0;
		unsigned char *text;
		Words *words;
	};

	IN getin(std::ofstream *stream, wchar_t Infile[]);
	Words* split(Words *words, unsigned char *text, int *code); //разбиваем исходный код на слова
	void newWord(Words *words, char* &Buffer, int &posbuf, int line);
}