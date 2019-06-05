// PED_2018.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, wchar_t *argv[])
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log;//оператор разрешения области видимости
	Log::LOG lex;
	Log::LOG sint;
	try
	{

		Parm::PARM parm = Parm::getparm(argc, argv); // параметры
		log = Log::getlog(parm.log); // открытие потока
		Log::writeLog(log); // заполнение журнала дата время
		Log::writeParm(log, parm); // печать в журнал используемых параметров 
		In::IN in = In::getin(log.stream, parm.in);  // запуск контроля входных символов
		in.words = In::split(in.words, in.text, in.code);   // формирование из считанного файла слов для лекс анализа.
		LA::LEX tables = LA::StartLexAnalyze(in, log, parm);  // запуск лексического анализа
		MFST::Mfst mfst(tables, GRB::getGreibach()); //инициализация для синтаксического анализатора

			Log::writeIn(log, in); //  печать  информации о считывании из файла
			Log::writeLexTable(log, tables.Lextable);  // печать таблицы лексем
			Log::writeIDtable(log, tables.IDtable); // печать таблицы идентификаторов
			if (parm.blex == true)
			{
				lex = Log::getlog(parm.lex);
				Log::writeLexTable(lex, tables.Lextable); // печать таблицы лексем в файл
				Log::writeIDtable(lex, tables.IDtable);  // печать таблицы лексем в консоль
			}
			else
			{
				Log::writeLexTableConsole(lex, tables.Lextable);
				Log::writeIDTableConsole(log, tables.IDtable);
			}
			Log::WriteCode(log, tables.Lextable);
			MFST_TRACE_START(log); // шапка
			mfst.start(log); //старт синтаксического aнализа
			mfst.savededucation(); //сохранить правила вывода
			mfst.printrules(log); // печать дерева разбора
			if (parm.bsint == true) //синтаксический анализ в файл
			{
				sint = Log::getlog(parm.sint);
				MFST::Mfst mfst(tables, GRB::getGreibach());
				MFST_TRACE_START(sint); // шапка
				mfst.start(sint); //старт синтаксического aнализа
				mfst.savededucation(); //сохранить правила вывода
				mfst.printrules(sint); // печать дерева разбора
			}
		if (!Log::Error)
		{
			Generation(tables.Lextable, tables.IDtable, in.words);// запуск генерации и формирование файла с кодом JS
			std::cout << "Генерация кода прошла успешно, смотрите Сode.html " << endl;
			PN polishNotation;
			if (polishNotation.CreatePolishNotation(&tables))
			{
				*log.stream << endl << endl << "Polish Notation";
				Log::WriteCode(log, tables.Lextable);
			}
		}
			

		
		Log::Close(log); // закрытие потока
	/*	char* HTML = "Code.html";
		system(HTML);
		char* logfile = "test.txt.log";
		system(logfile);
*/
	}

	catch (Error::ERROR e)
	{
		Log::writeError(log.stream, e); // ошибки

	}
}
