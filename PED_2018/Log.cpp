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
		*(log.stream) << "\n---- �������� ------ ����: ";
		time_t rawtime;
		char buffer[80];                                // ������, � ������� ����� ��������� ������� �����
		time(&rawtime);
		tm *k = localtime(&rawtime);
		strftime(buffer, 80, "%d.%m.%Y %X", k);
		*(log.stream) << buffer << "------------------";
	}

	void writeParm(LOG &log, Parm::PARM &parm)//���������
	{
		char inTxt[PARM_MAX_SIZE],
			logTxt[PARM_MAX_SIZE],
			lexTxt[PARM_MAX_SIZE],
			sintTxt[PARM_MAX_SIZE];
		wcstombs(inTxt, parm.in, wcslen(parm.in) + 1);
		wcstombs(logTxt, parm.log, wcslen(parm.log) + 1);
		wcstombs(lexTxt, parm.lex, wcslen(parm.in) + 1);
		wcstombs(sintTxt, parm.sint, wcslen(parm.in) + 1);
		*log.stream << "\n----- ��������� --------" << "\n-in: " << inTxt << "\n-log: " << logTxt << "\n-lex: " << lexTxt << "\n-sint: " << sintTxt << "\n";
	}

	void writeIn(LOG &log, In::IN &in) {//�������� ������
		*log.stream << "\n---- �������� ������ ------" << endl;
		*log.stream << "���������� ��������: " << in.size << endl;
		*log.stream << "���������������    : " << in.ignor << endl;
		*log.stream << "���������� �����   : " << in.lines << endl;
	}

	void writeError(std::ofstream *stream, Error::ERROR &e)//������
	{
		Error = true;

			if (e.position.col == -1 || e.position.line == -1)
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message << std::endl;
			else if (e.position.col == NULL)
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line << std::endl;
			else
				std::cout << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
				<< " ������: " << e.position.line
				<< " ������� � ������: " << e.position.col << std::endl;
			if (stream != NULL)
			{
				if (e.position.col == -1 || e.position.line == -1)
					*stream << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message;
				else if (e.position.col == NULL)
					*stream << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
					<< " ������: " << e.position.line;
				else
					*stream << std::endl << "����� ������: " << e.id << " ��������� ������: " << e.message
					<< " ������: " << e.position.line
					<< " ������� � ������: " << e.position.col;
			}
	}

	void writeLexTable(LOG &log, LT::LexTable &Lextable)//������� ������
	{

		*log.stream << "\n------------������� ������------------\n" <<
			std::setw(8) << std::left << "� " <<
			std::setw(11) << std::left << "������� " <<
			std::setw(11) << std::left << "� ������ " <<
			std::setw(9) << std::left << "� � �� " << std::endl;

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

	void writeIDtable(LOG &log, IT::IdTable &IDtable)//������� ���������������
	{
		*log.stream << "\n-----------------------------------------������� ���������������-----------------------------------------\n" <<
			std::setw(8) << std::left << "� " <<
			std::setw(15) << std::left << "��� " <<
			std::setw(14) << std::left << "��� ������ " <<
			std::setw(20) << std::left << "��� " <<
			std::setw(9) << std::left << "� � �� " <<
			std::setw(16) << std::left << "�������� " <<
			std::setw(16) << std::left << "�-�� ���������� " <<
			std::setw(16) << std::left << "���� ���������� " <<
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
				*log.stream << "�������"; break;
			case IT::V:
				*log.stream << "����������"; break;
			case IT::P:
				*log.stream << "��������"; break;
			case IT::L:
				*log.stream << "�������"; break;
			case IT::S:
				*log.stream << "����������� �������"; break;
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

	void writeIDTableConsole(LOG &log, IT::IdTable &IDtable)//������� ��������������� � �������
	{
		std::cout << "\n---------------������� ���������������-------------------------------\n" <<
			std::setw(8) << std::left << "� " <<
			std::setw(15) << std::left << "��� " <<
			std::setw(14) << std::left << "��� ������ " <<
			std::setw(20) << std::left << "��� " <<
			std::setw(8) << std::left << "� � �� " <<
			std::setw(16) << std::left << "��������" <<
			std::setw(16) << std::left << "�-�� ���������� " <<
			std::setw(16) << std::left << "���� ���������� " <<
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
				std::cout << "�������"; break;
			case IT::V:
				std::cout << "����������"; break;
			case IT::P:
				std::cout << "��������"; break;
			case IT::L:
				std::cout << "�������"; break;
			case IT::S:
				std::cout << "����������� �������"; break;
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

	void writeLexTableConsole(LOG &log, LT::LexTable &Lextable)//������� ������
	{

		std::cout << "\n---------------������� ������--------------------------------\n" <<
			std::setw(8) << std::left << "������� " <<
			std::setw(9) << std::left << "� ������ " <<
			std::setw(15) << std::left << "� ����. ������ " <<
			std::setw(15) << std::left << "� ����. �����. " << std::endl;

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

	void WriteCode(LOG &log, LT::LexTable &Lextable)//������ �������
	{
		int pb = NULL;
		char*Buffer = new char[1024];
		*log.stream << "\n-------------------������������� ���--------------------\n";
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