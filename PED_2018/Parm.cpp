#include "stdafx.h" 

namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])//argc – количество параметров (int), argv – массив указателей на строки (_TCHAR* -указатель строку wchar_t)
	{
		PARM param = { L"", L"", L"", false, L"", false};
		bool fl_in = false, fl_log = false;
		if (argc == 1) //аргументы in,log,out не заданы                  
				throw ERROR_THROW(10);
		for (int i = 1; i < argc; i++)
		{
			
			if (wcslen(argv[i]) > PARM_MAX_SIZE)//проверка превышена ли длина входного параметра в 100
				throw ERROR_THROW(11)
			else
			{
				if (wcsstr(argv[i], PARM_IN) && (wcslen(argv[i]) >= wcslen(PARM_IN))) //сравнение строки с подстрокой
				{
					wcscpy_s(param.in, argv[i] + wcslen(PARM_IN)); //начнет копировать после двоеточия
					fl_in = true;
				}
				if (wcsstr(argv[i], PARM_LOG) && (wcslen(argv[i]) >= wcslen(PARM_LOG))) //если аргумент log и после двоеточия прописан
				{
					wcscpy_s(param.log, argv[i] + wcslen(PARM_LOG));
					fl_log = true;
				}
				if (wcsstr(argv[i], PARM_LEX) && (wcslen(argv[i]) >= wcslen(PARM_LEX)))
				{
					wcscpy_s(param.lex, argv[i] + wcslen(PARM_LEX));
					param.blex = true;
				}
				if (wcsstr(argv[i], PARM_SINT) && (wcslen(argv[i]) >= wcslen(PARM_SINT)))
				{
					wcscpy_s(param.sint, argv[i] + wcslen(PARM_SINT));
					param.bsint = true;
				}
				
			}
		}

		if (fl_in == false)//проверка задан ли параметр -in файл
			throw ERROR_THROW(10);//генерирует ошибку  "Параметр -in должен быть задан"


		if (fl_log == false)
		{
			wcscpy_s(param.log, param.in);//копирует
			wcsncat_s(param.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));//приписывает sizeof символов PARM_LOG_DEFAULT_EXT в parm.log
		};

		return param;
	};
}
