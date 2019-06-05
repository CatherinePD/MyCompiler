#pragma once
#define PARM_IN  L"-in:"
#define PARM_LOG L"-log:"
#define PARM_LEX L"-lex:"
#define PARM_SINT L"-sint:"
#define PARM_GEN L"-gen:"
#define PARM_MAX_SIZE 100
#define PARM_LOG_DEFAULT_EXT L".log"

namespace Parm
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE]; //входной файл
		wchar_t log[PARM_MAX_SIZE]; //протокол
		wchar_t lex[PARM_MAX_SIZE]; //протокол для таблицы лексем и таблицы идентификаторов
		bool blex = false;
		wchar_t sint[PARM_MAX_SIZE]; //протокол для синтаксического разбора и правил
		bool bsint = false;
	};

	PARM getparm(int argc, wchar_t* argv[]);
}
