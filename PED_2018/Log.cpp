#include "stdafx.h"


namespace Log
{

	LOG getlog(wchar_t  logfile[])
	{
		LOG prot;
		prot.stream = new std::ofstream;
		(*prot.stream).open(logfile);
		if (!(*prot.stream).is_open())
			throw ERROR_THROW(22);          
		wcscpy_s(prot.logfile, logfile);
		return prot;
	}

	void writeLog(LOG &log)
	{
		*(log.stream) << "\n---- Протокол ------ Дата: ";
		time_t rawtime;
		char buffer[80];                                // строка, в которой будет храниться текущее время
		time(&rawtime);
		tm *k = localtime(&rawtime);
		strftime(buffer, 80, "%d.%m.%Y %X", k);
		*(log.stream) << buffer << "------------------";
	}

	void writeParm(LOG &log, Parm::PARM &parm)//параметры
	{
		char inTxt[PARM_MAX_SIZE],
			logTxt[PARM_MAX_SIZE],
			lexTxt[PARM_MAX_SIZE],
			sintTxt[PARM_MAX_SIZE];
		wcstombs(inTxt, parm.in, wcslen(parm.in) + 1);
		wcstombs(logTxt, parm.log, wcslen(parm.log) + 1);
		wcstombs(lexTxt, parm.lex, wcslen(parm.in) + 1);
		wcstombs(sintTxt, parm.sint, wcslen(parm.in) + 1);
		*log.stream << "\n----- Параметры --------" << "\n-in: " << inTxt << "\n-log: " << logTxt << "\n-lex: " << lexTxt << "\n-sint: " << sintTxt << "\n";
	}

	void writeIn(LOG &log, In::IN &in) {//исходные данные
		*log.stream << "\n---- Исходные данные ------" << endl;
		*log.stream << "Количество символов: " << in.size << endl;
		*log.stream << "Проигнорировано    : " << in.ignor << endl;
		*log.stream << "Количество строк   : " << in.lines << endl;
	}

	void writeError(std::ofstream *stream, Error::ERROR &e)//ошибки
	{
		Error = true;

			if (e.position.col == -1 || e.position.line == -1)
				std::cout << std::endl << "Номер ошибки: " << e.id << " Сообщение ошибки: " << e.message << std::endl;
			else if (e.position.col == NULL)
				std::cout << std::endl << "Номер ошибки: " << e.id << " Сообщение ошибки: " << e.message
				<< " Строка: " << e.position.line << std::endl;
			else
				std::cout << std::endl << "Номер ошибки: " << e.id << " Сообщение ошибки: " << e.message
				<< " Строка: " << e.position.line
				<< " Позиция в строке: " << e.position.col << std::endl;
			if (stream != NULL)
			{
				if (e.position.col == -1 || e.position.line == -1)
					*stream << std::endl << "Номер ошибки: " << e.id << " Сообщение ошибки: " << e.message;
				else if (e.position.col == NULL)
					*stream << std::endl << "Номер ошибки: " << e.id << " Сообщение ошибки: " << e.message
					<< " Строка: " << e.position.line;
				else
					*stream << std::endl << "Номер ошибки: " << e.id << " Сообщение ошибки: " << e.message
					<< " Строка: " << e.position.line
					<< " Позиция в строке: " << e.position.col;
			}
	}

	void writeLexTable(LOG &log, LT::LexTable &Lextable)//Таблица лексем
	{

		*log.stream << "\n------------Таблица лексем------------\n" <<
			std::setw(8) << std::left << "№ " <<
			std::setw(11) << std::left << "Лексема " <<
			std::setw(11) << std::left << "№ строки " <<
			std::setw(9) << std::left << "№ в ТИ " << std::endl;

		for (int i = 0; i < Lextable.size; i++)
		{
			*log.stream << std::setw(8) << std::left << i << std::setw(11) << std::left << Lextable.table[i].lexema <<
				std::setw(11) << std::left << Lextable.table[i].sn;
			*log.stream << std::setw(9) << std::left;
			if (Lextable.table[i].idxTI != -1)
				*log.stream << Lextable.table[i].idxTI;
			else
				*log.stream << '-';
			*log.stream << std::endl;
		}
		*log.stream << "\n\n";
	}

	void writeIDtable(LOG &log, IT::IdTable &IDtable)//Таблица идентификаторов
	{
		*log.stream << "\n-----------------------------------------Таблица идентификаторов-----------------------------------------\n" <<
			std::setw(8) << std::left << "№ " <<
			std::setw(15) << std::left << "Имя " <<
			std::setw(14) << std::left << "Тип данных " <<
			std::setw(20) << std::left << "Тип " <<
			std::setw(9) << std::left << "№ в ТЛ " <<
			std::setw(16) << std::left << "Значение " <<
			std::setw(16) << std::left << "К-во параметров " <<
			std::setw(16) << std::left << "Типы параметров " <<
			std::endl;

		for (int i = 0; i < IDtable.size; i++)
		{

			*log.stream << std::setw(8) << std::left << i << std::setw(15) << std::left << IDtable.table[i].id << std::setw(14) << std::left;

			if (IDtable.table[i].iddatatype == IT::INT)
				*log.stream << INTEGER;
			else
				*log.stream << STRING;

			*log.stream << std::setw(20) << std::left;
			switch (IDtable.table[i].idtype)
			{
			case IT::F:
				*log.stream << "Функция"; break;
			case IT::V:
				*log.stream << "Переменная"; break;
			case IT::P:
				*log.stream << "Параметр"; break;
			case IT::L:
				*log.stream << "Литерал"; break;
			case IT::S:
				*log.stream << "Стандартная функция"; break;
			}
			*log.stream << std::setw(9) << std::left << IDtable.table[i].idxfirstLE << std::setw(16) << std::left;
			if (IDtable.table[i].iddatatype == IT::INT)
			{
				*log.stream << IDtable.table[i].value.vNUM;
			}
			else
			{
				if (IDtable.table[i].value.vSTR.len != 0)
					*log.stream << IDtable.table[i].value.vSTR.str;
				else
					*log.stream << "NULL";
			}
			if (IDtable.table[i].idtype == IT::F || IDtable.table[i].idtype == IT::S)
			{
				*log.stream << std::setw(16) << std::left << IDtable.table[i].count_parm;
				for (int j = 0; j < IDtable.table[i].count_parm; j++)
				{
					if (IDtable.table[i].parms[j] == 'n')
						*log.stream << std::setw(4) << std::left << "int" ;
	
					if (IDtable.table[i].parms[j] == 'w')
						*log.stream << std::setw(4) << std::left << "string";
				}
			}
			*log.stream << std::endl;
		}
		*log.stream << "\n\n";
	}

	void writeIDTableConsole(LOG &log, IT::IdTable &IDtable)//таблица идентификаторов в консоль
	{
		std::cout << "\n---------------Таблица идентификаторов-------------------------------\n" <<
			std::setw(8) << std::left << "№ " <<
			std::setw(15) << std::left << "Имя " <<
			std::setw(14) << std::left << "Тип данных " <<
			std::setw(20) << std::left << "Тип " <<
			std::setw(8) << std::left << "№ в ТЛ " <<
			std::setw(16) << std::left << "Значение" <<
			std::setw(16) << std::left << "К-во параметров " <<
			std::setw(16) << std::left << "Типы параметров " <<
			std::endl;

		for (int i = 0; i < IDtable.size; i++)
		{
			std::cout << std::setw(8) << std::left << i << std::setw(15) << std::left << IDtable.table[i].id << std::setw(14) << std::left;

			if (IDtable.table[i].iddatatype == IT::INT)
				std::cout << INTEGER;
			else
				std::cout << STRING;

			std::cout << std::setw(20) << std::left;
			switch (IDtable.table[i].idtype)
			{
			case IT::F:
				std::cout << "Функция"; break;
			case IT::V:
				std::cout << "Переменная"; break;
			case IT::P:
				std::cout << "Параметр"; break;
			case IT::L:
				std::cout << "Литерал"; break;
			case IT::S:
				std::cout << "Стандартная функция"; break;
			}
			std::cout << std::setw(9) << std::left << IDtable.table[i].idxfirstLE << std::setw(16) << std::left;
			if (IDtable.table[i].iddatatype == IT::INT)
				std::cout << IDtable.table[i].value.vNUM;
			else
			{
				if (IDtable.table[i].value.vSTR.len != 0)
					std::cout << IDtable.table[i].value.vSTR.str;
				else
					std::cout << "NULL";
			}
			if (IDtable.table[i].idtype == IT::F || IDtable.table[i].idtype == IT::S)
			{
				std::cout << std::setw(16) << std::left << IDtable.table[i].count_parm;
				for (int j = 0; j < IDtable.table[i].count_parm; j++)
				{
					if (IDtable.table[i].parms[j] == 'n')
						std::cout << std::setw(4) << std::left << "int";

					if (IDtable.table[i].parms[j] == 'w')
						std::cout << std::setw(4) << std::left << "string";
				}
			}
			std::cout << std::endl;
		}
		std::cout << "\n\n";
	}

	void writeLexTableConsole(LOG &log, LT::LexTable &Lextable)//таблица лексем
	{

		std::cout << "\n---------------Таблица лексем--------------------------------\n" <<
			std::setw(8) << std::left << "Лексема " <<
			std::setw(9) << std::left << "№ строки " <<
			std::setw(15) << std::left << "№ табл. лексем " <<
			std::setw(15) << std::left << "№ табл. идент. " << std::endl;

		for (int i = 0; i < Lextable.size; i++)
		{
			std::cout << std::setw(8) << std::left << Lextable.table[i].lexema <<
				std::setw(9) << std::left << Lextable.table[i].sn;
			std::cout << std::setw(15) << std::left << i;
			std::cout << std::setw(15) << std::left;
			if (Lextable.table[i].idxTI != -1)
				std::cout << Lextable.table[i].idxTI;
			else
				std::cout << '-';
			std::cout << std::setw(8) << std::left;
			std::cout << std::endl;
		}
		std::cout << "\n\n";
	}

	void WriteCode(LOG &log, LT::LexTable &Lextable)//польск нотация
	{
		int pb = NULL;
		char*Buffer = new char[1024];
		*log.stream << "\n-------------------Промежуточный код--------------------\n";
		for (int i = 0; i < Lextable.size; i++)
		{
			Buffer[pb] = Lextable.table[i].lexema;
			pb++;
			if (Lextable.table[i + 1].sn != Lextable.table[i].sn)
			{
				Buffer[pb] = '\0';
				if (Lextable.table[i].sn < 10)
				{
					*log.stream << '0';
				}

				*log.stream << Lextable.table[i].sn << ' ';
				*log.stream << Buffer << std::endl;
				pb = NULL;
			}
		}
	}

	void Close(LOG &log)
	{
		(*log.stream).close();
	};
}