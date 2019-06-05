#pragma once
#include "stdafx.h"
//спецификаци€ таблицы лексем
#define	LEXEMA_FIXSIZE   1	        //размер лексемы
#define	LT_MAXSIZE		 4096	    //максимальное количество строк в таблице лексем
#define	LT_TI_NULLDX	 0xffffffff	//нет элемента таблицы идентификаторов
#define LEX_SEPARATORS	 'S'
#define	LEX_ID_TYPE_I    'n'
#define	LEX_ID_TYPE_S    's'
#define	LEX_ID			 'i'			
#define	LEX_LITERAL		 'l'	
#define LEX_LIB			 'b'
#define	LEX_FUNCTION     'f'			
#define	LEX_MAIN		 'm'			
#define	LEX_RETURN		 'r'			
#define	LEX_OUTPUT		 'o'	
#define LEX_TYPE		 't'
#define	LEX_SEPARATOR	 ';'			
#define	LEX_COMMA		 ','			
#define	LEX_LEFTBRACE	 '{'			
#define	LEX_BRACELET	 '}'			
#define	LEX_LEFTTHESIS	 '('			
#define	LEX_RIGHTTHESIS	 ')'			
#define	LEX_PLUS		 '+'	
#define	LEX_MINUS		 '-'
#define LEX_ROOT		 'k'
#define LEX_POWER		 'p'
#define	LEX_STAR		 '*'			
#define	LEX_DIRSLASH	 '/'			
#define	LEX_EQUAL		 '='			
#define	LEX_OPERATION	 'v'
#define	INTEGER			 "int"		
#define	STRING			 "string"
#define	LTRL			 "ltrl"
#define SPACE  ' '
#define DOT '.'
namespace LT	//таблица лексем
{
	struct Entry                       //структура дл€ содержимого табл.лексем
	{
		char lexema;					//лексема
		int sn;							//номер строки в исходном тексте
		int idxTI;						//индекс в таблице идентификаторов или LT_TI_NULLIDX

		Entry();
		Entry(char lexema, int snn, int idxti = LT_TI_NULLDX);
	};

	struct LexTable						//экземпл€р таблицы лексем
	{
		int maxsize;					//Ємкость таблицы лексем
		int size;						//текущий размер таблицы лексем
		Entry* table;					//массив (Entity)строк таблицы лексем
	};

	LexTable Create(int size);		            //Ємкость < LT_MAXSIZE
	void Add(LexTable &lextable, Entry entry);	//экземпл€р таблицы лексем, строка таблицы лексем
}