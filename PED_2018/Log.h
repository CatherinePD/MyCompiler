#pragma once
#include "stdafx.h"
#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "LT.h"
#include "IT.h"

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE] = L" ";
		ofstream *stream = NULL;
	};
	bool static Error = false;
	LOG getlog(wchar_t logfile[]);							//сформировать структуру LOG
	void writeLog(LOG &log);								//вывести в протокол заголовок
	void writeParm(LOG &log, Parm::PARM &parm);				//вывести в протокол информацию о входных параметрах
	void writeIn(LOG &log, In::IN &in);						//исходные данные
	void writeError(ofstream *stream, Error::ERROR &error);	//ошибки
	void writeLexTable(LOG &log, LT::LexTable &lextable);	//таблица лексем
	void writeIDtable(LOG &log, IT::IdTable &IDtable);		//таблица идентификаторов
	void writeLexTableConsole(LOG &log, LT::LexTable &Lextable);//таблица лексем
	void writeIDTableConsole(LOG &log, IT::IdTable &IDtable);//таблица идентификаторов
	void WriteCode(LOG &log, LT::LexTable &lextable);//польская нотация
	void Close(LOG &log);
}