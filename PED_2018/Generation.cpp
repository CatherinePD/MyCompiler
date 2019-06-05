#include "stdafx.h"

ofstream fout("Code.js");

void Generation(LT::LexTable &Lextable, IT::IdTable & IDtable, In::Words *words)
{
	for (int i = 0; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_PLUS:
		case LEX_STAR:
		case LEX_MINUS:
		case LEX_DIRSLASH:
		case  LEX_EQUAL:
		{
			fout << " " << Lextable.table[i].lexema << " ";
			break;
		}
		case LEX_COMMA:
		case SPACE:
		{
			fout << Lextable.table[i].lexema << " ";
			break;
		}

		case LEX_RIGHTTHESIS:
		case LEX_LEFTTHESIS:
		{
			fout << Lextable.table[i].lexema;
			break;
		}
		case LEX_LEFTBRACE:
		{

			fout << endl << Lextable.table[i].lexema << endl;
			break;
		}
		case LEX_BRACELET:
		{

			fout << Lextable.table[i].lexema << endl << endl;
			break;
		}
		case LEX_SEPARATOR:
		{
			fout << Lextable.table[i].lexema << endl;
			break;
		}
		case  LEX_TYPE:
		{
			fout << "var ";
			break;
		}

		case LEX_LITERAL:
		{
			if (IDtable.table[Lextable.table[i].idxTI].iddatatype == IT::INT)
			fout << IDtable.table[Lextable.table[i].idxTI].value.vNUM;
			else fout << IDtable.table[Lextable.table[i].idxTI].value.vSTR.str;
			break;
		}
		case LEX_ID:
		{
			fout << IDtable.table[Lextable.table[i].idxTI].id;
			break;
		}
		case LEX_OUTPUT:
		{
			fout << "document.write('<br>');" << endl;
			fout << "document.write";
			break;
		}
		case LEX_FUNCTION:
		{
			fout << words[i].word << " ";
			break;
		}
		case LEX_RETURN:
		{
			fout << words[i].word << " ";
			break;
		}
		case LEX_LIB:
		{
			fout << "document.write('Now you can use Math functions')";
			break;
		}
		case LEX_ROOT:
		{
			fout << "Math.sqrt";
			for (++i; Lextable.table[i].lexema != LEX_RIGHTTHESIS; i++)
				fout << words[i].word;
			fout << words[i].word;
			break;
		}
		case LEX_POWER:
		{
			fout << "Math.pow";
			for (++i; Lextable.table[i].lexema != LEX_RIGHTTHESIS; i++)
				fout << words[i].word;
			fout << words[i].word;
			break;
		}
		}
	}
	fout.close();
}
