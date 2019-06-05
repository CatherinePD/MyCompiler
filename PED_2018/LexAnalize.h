#pragma once

#include "stdafx.h"
#include "IT.h"
#include "LT.h"
#include "In.h"
#include "Log.h"
#include "FST.h"


namespace LA
{
	struct Graph
	{
		char lexema;
		FST::FST graph;
	};
	
	struct LEX
	{
		LT::LexTable Lextable;
		IT::IdTable	IDtable;
	};
	LEX StartLexAnalyze(In::IN &InStruct, Log::LOG &log, Parm::PARM &parm);
}
