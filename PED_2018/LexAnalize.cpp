#include "stdafx.h"	


namespace LA
{
	Graph graph[N_GRAPHS] =  // графы для конечных автоматов
	{
		{ LEX_SEPARATORS, FST::FST(GRAPH_SEPARATORS) },
		{ LEX_TYPE, FST::FST(GRAPH_TYPE) },
		{ LEX_LITERAL, FST::FST(GRAPH_NUMBER_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STRING_LITERAL) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_OUTPUT, FST::FST(GRAPH_OUTPUT) },
		{ LEX_MAIN, FST::FST(GRAPH_MAIN) },
		{ LEX_LIB, FST::FST(GRAPH_EMatLib) },
		{ LEX_DIRSLASH, FST::FST(GRAPH_FORWARD_SLASH) },
		{ LEX_ROOT, FST::FST(GRAPH_ROOT) },
		{ LEX_POWER, FST::FST(GRAPH_POWER) },
		{ LEX_ID_TYPE_I, FST::FST(GRAPH_INT) },
		{ LEX_ID_TYPE_S, FST::FST(GRAPH_STRING) },
		{ LEX_ID, FST::FST(GRAPH_ID) },
	};
	
	LEX StartLexAnalyze(In::IN &InStruct, Log::LOG &log, Parm::PARM &parm) //начало Лексического анализа
	{
		LEX Tables;
		Tables.Lextable = LT::Create(LT_MAXSIZE);  // создание таблицы лексем
		Tables.IDtable = IT::Create(TI_MAXSIZE);  // создание таблицы идентификаторов

		bool FlagEx = false; //для разбора
		bool flag1 = false;  //при ошибках
		bool flag2 = false;  //при ошибках
		bool isParam = false;     //флаг на параметр	
		int kol = 0;				//для параметров
		int MainBody = 0;			//есть ли главная функция
		int MyFunc = 0;				//подключена ли библиотека при использовании стандартных функций
		int LibBody = 0;			//проверка подключения стандартной библиотеки
		char Buffer[255] = "";			//буфер для имени переменной, склеенной с функцией
		char PrefixFunc[255] = ""; //буфер для имени функции

		IT::IDDATATYPE funcType;   // тип функции
		IT::IDDATATYPE idType;   // тип идентификатора

		for (int i = 0; i < In::Words::amount; i++) // начинаем просмотр массива слов
		{
			FlagEx = false;
			for (int j = 0; j < N_GRAPHS; j++)    // ищем подходящий автомат для слова	
			{
				FST::FST fstex(InStruct.words[i].word, graph[j].graph);   // попытка разбора
				if (FST::execute(fstex)) // если разбор успешный то 
				{
					FlagEx = true;
					switch (graph[j].lexema)     // ищем подходящий кейз для лексемы
					{

					case LEX_MAIN:   // если главная ф-ция
					{
						MainBody++;   //увеличим с 0 до 1 , всё правильно , необходима ровно 1 гл ф-ция
						if (MainBody > 1)    // если найдено более 1-ой главной ф-ции
							Log::writeError(log.stream, Error::GetError(84, InStruct.words[i].line, NULL)); // делаем запись в журнал ошибок

						strcpy_s(PrefixFunc, "m");
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line);   // запись в таблицу, с фиксацией номера строки 
						LT::Add(Tables.Lextable, entrylt);    // добавление лексемы в таблицу 
						break; //выход
					}
					case LEX_LIB:   // если стандартная библиотека
					{
						LibBody++;
						if (LibBody > 1)    // если найдено более 1-ой библиотеки
							Log::writeError(log.stream, Error::GetError(89, InStruct.words[i].line, NULL)); // делаем запись в журнал ошибок

						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line);// запись в таблицу , с фиксацией номера строки 
						LT::Add(Tables.Lextable, entrylt);// добавление лексемы в таблицу 
						break; //выход
					}

					case LEX_ROOT:  // лексема функции корень
					{
						MyFunc++;

						IT::Entry entryit("root", i, IT::INT, IT::S); // создаём элемент ТИ с занесением всех собранных данных
						IT::Add(Tables.IDtable, entryit);						 // добавляем созданный элемент
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word)); // создание
																																		 // элемента таблицы лексем
						LT::Add(Tables.Lextable, entrylt); //занесение в таблицу лексем
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 1;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						break;
					}

					case LEX_POWER: // лексема функции степень 
					{
						MyFunc++;
						IT::Entry entryit("power", i, IT::INT, IT::S); // создаём элемент ТИ с занесением всех собранных данных
						IT::Add(Tables.IDtable, entryit);						 // добавляем созданный элемент
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word)); // создание
																																		 // элемента таблицы лексем
						LT::Add(Tables.Lextable, entrylt); //занесение в таблицу лексем
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm = 2;
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[0] = 'n';
						Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[1] = 'n';
						break;
					}

					case LEX_ID://идентификтор
					{
						if (Tables.Lextable.table[i - 1].lexema != LEX_FUNCTION && IT::IsId(Tables.IDtable, InStruct.words[i].word) == -1) //добавляем префикс для имени идентификатора
						{
							strncpy(Buffer, PrefixFunc, ID_MAXSIZE - 1);
							strcat_s(Buffer, InStruct.words[i].word);
							strncpy(InStruct.words[i].word, Buffer, ID_MAXSIZE - 1);
						}

						if (IT::IsId(Tables.IDtable, InStruct.words[i].word) == -1) // если данный идентификатор не найден повторно 
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // если предыдущей лексемой была лексема функциии
							{
								strncpy_s(PrefixFunc, InStruct.words[i].word, ID_MAXSIZE - 1);

								funcType = idType;     // указываем тип идентификатора
								IT::Entry entryit(PrefixFunc, i, idType, IT::F); // создаём элемент ТИ с занесением всех собранных данных
								IT::Add(Tables.IDtable, entryit); // добавляем созданный элемент
								LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word)); // создание элемента таблицы лексем (функция возвр номер в ТИ)																 
								LT::Add(Tables.Lextable, entrylt); //занесение в таблицу лексем
								if (InStruct.words[i + 2].word[0] == LEX_RIGHTTHESIS) // если лексема через одну - )  
									isParam = false; // если функция без параметров
								else isParam = true; // наличие параметров
								break;

							}
							else if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_I) //если предыдущая лесема была лексемой целого типа данных 
							{
								
								if (isParam == false) // если идентификатор типа переменная не является параметром
								{
									if (Tables.Lextable.table[i - 2].lexema != LEX_TYPE) //если не было предварительного определения словом type
									{
										Log::writeError(log.stream, Error::GetError(82, InStruct.words[i].line, NULL));
										flag1 = true;
									}
									IT::Entry entryit(InStruct.words[i].word, i, idType, IT::V); // создаём элемент ТИ
									IT::Add(Tables.IDtable, entryit); //заносим в ТИ
								}
								else if (isParam == true) // иначе если параметр
								{
									int curpos = Tables.IDtable.size;
									while (Tables.IDtable.table[curpos].idtype != IT::F)
										curpos--;
									if (kol > INT_MAXSIZE_PARM)
									{
										Log::writeError(log.stream, Error::GetError(94, InStruct.words[i].line, NULL));
										flag1 = true;
									}
									Tables.IDtable.table[curpos].parms[kol] = 'n';
									kol++;
									IT::Entry entryit(InStruct.words[i].word, i, idType, IT::P);// создаём элемент ТИ
									IT::Add(Tables.IDtable, entryit);//заносим в ТИ
																	 //
									if (InStruct.words[i + 1].word[0] == LEX_RIGHTTHESIS) // если следующая лексема - )
									{
										isParam = false; // параметры закончились
										int curpos = Tables.IDtable.size;
										while (Tables.IDtable.table[curpos].idtype != IT::F)
											curpos--;
										Tables.IDtable.table[curpos].count_parm = kol;
										kol = 0;
									}
								}

								LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word)); // создание элемента ТЛ
								LT::Add(Tables.Lextable, entrylt); // добавление в ТЛ
								break;
							}
							else if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_S) //если предыдущая лесема была лексемой стокового типа данных
							{
								if (isParam == false) // если идентификатор типа переменная не является параметром
								{
									if (Tables.Lextable.table[i - 2].lexema != LEX_TYPE) //если не было предварительного определения словом type
									{
										Log::writeError(log.stream, Error::GetError(82, InStruct.words[i].line, NULL));
										flag1 = true;
									}
									IT::Entry entryit(InStruct.words[i].word, i, idType, IT::V); // создаём элемент ТИ
									IT::Add(Tables.IDtable, entryit); //заносим в ТИ
								}
								else if (isParam == true) // иначе если параметр
								{
									int curpos = Tables.IDtable.size;																							//мейби лучше присвоить idtable.size?
									while (Tables.IDtable.table[curpos].idtype != IT::F)
										curpos--;
									Tables.IDtable.table[curpos].parms[kol] = 'w';
									kol++;
									if (kol == INT_MAXSIZE_PARM)
									{
										Log::writeError(log.stream, Error::GetError(80, InStruct.words[i].line, NULL));
										flag1 = true;
									}
									IT::Entry entryit(InStruct.words[i].word, i, idType, IT::P);// создаём элемент ТИ
									IT::Add(Tables.IDtable, entryit);//заносим в ТИ
																	 //
									if (InStruct.words[i + 1].word[0] == LEX_RIGHTTHESIS) // если следующая лексема - )
									{
										isParam = false; // параметры закончились
										int curpos = Tables.IDtable.size;
										while (Tables.IDtable.table[curpos].idtype != IT::F)
											curpos--;
										Tables.IDtable.table[curpos].count_parm = kol;
										kol = 0;
									}
								}

								LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word)); // создание элемента ТЛ
								LT::Add(Tables.Lextable, entrylt); // добавление в ТЛ
								break;
							}
							Log::writeError(log.stream, Error::GetError(82, InStruct.words[i].line, NULL)); // если пред лекс не была ни string, ни int
							flag1 = true;																		
						}
						// далее проверка на переопределение	
						else
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_I || Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE_S || Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // если предыдущим был тип данных или лексема функции
							{
								Log::writeError(log.stream, Error::GetError(81, InStruct.words[i].line, NULL)); //выдаём ошибку о попытке переопределения
								flag1 = true;
							}
							LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, IT::IsId(Tables.IDtable, InStruct.words[i].word)); //создание элемента табл лексем
							LT::Add(Tables.Lextable, entrylt); // занесение элемента в ТЛ
							break;
						}
						break;
					}
					case LEX_LITERAL: // лексема литерала
					{
						if (Tables.Lextable.table[i - 1].lexema == LEX_EQUAL) // проверим предыдущие лексемы
						{
							
							IT::Entry entryit(LTRL, i, graph[j].graph.type, IT::L); // создание элемента табл ид с пометкой литерал
							IT::Add(Tables.IDtable, entryit); //добавление в ТИ
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.words[i].word); // установление значения литерала
							LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, Tables.IDtable.size - 1); // создание элемента ТЛ
							LT::Add(Tables.Lextable, entrylt); // добавление элемента в ТЛ
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.words[i - 2].word)].idtype == IT::F) // если предыдущая была лекс ф-ции
							{
								Log::writeError(log.stream, Error::GetError(86, InStruct.words[i].line, NULL)); //нельзя присваивать значение ф-ции
								flag1 = true;
							}
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.words[i - 2].word)].idtype == IT::V ||    //если перед = была переменная или параметр
								Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.words[i - 2].word)].idtype == IT::P)
							{
								IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.words[i - 2].word), InStruct.words[i].word); // устанавливаем им их значение в поле табл идентификаторов
							}
							break;
						}

						else
						{	IT::Entry entryit(LTRL, i, graph[j].graph.type, IT::L); // создание элемента табл ид с пометкой литерал
							IT::Add(Tables.IDtable, entryit); //добавление в таблицу
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.words[i].word); // установление значения литерала
							LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line, Tables.IDtable.size - 1); // создание элемента ТЛ
							LT::Add(Tables.Lextable, entrylt); // добавление элемента в ТЛ
						}
						break;
					}

					case LEX_SEPARATORS: // лексема сепараторов
					{

						switch (InStruct.words[i].word[0])
						{
						case LEX_SEPARATOR:
						{
							if (Tables.Lextable.table[i - 2].lexema == LEX_RETURN) // если  вернуться на 2 лекс назад и будет лексема return
							{
								if (Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype != funcType) 
								{
									Log::writeError(log.stream, Error::GetError(91, InStruct.words[i].line, NULL));  // возвращаемое значение не совпадает с типом функции
									flag1 = true;
								}
								//kol = 0;																		
								IT::IDDATATYPE retType; // созданим воращаемое значение ф-ции
								if (Tables.Lextable.table[i - 1].lexema == LEX_LITERAL) // если предыдущая литерал
									retType = Tables.IDtable.table[Tables.IDtable.size - 1].iddatatype; // данный литерал и есть возвр ф-ции значение
							}

							LT::Entry entrylt(InStruct.words[i].word[0], InStruct.words[i].line); // создаём элемент ТЛ
							LT::Add(Tables.Lextable, entrylt); // занесение элемента в ТЛ
							break;

						}
						case LEX_PLUS:
						case LEX_EQUAL:
						case LEX_STAR:
						case LEX_MINUS:
						case LEX_DIRSLASH:
						{
							
							if (Tables.Lextable.table[i - 1].lexema != LEX_ID && Tables.Lextable.table[i - 1].lexema != LEX_RIGHTTHESIS && Tables.Lextable.table[i - 1].lexema != LEX_LEFTTHESIS && Tables.Lextable.table[i - 1].lexema != LEX_LITERAL)
							{ //если прошлым символом был не ID, не скобочки, не литерал
								Log::writeError(log.stream, Error::GetError(56, InStruct.words[i].line, NULL)); //два знака операции подряд
								flag1 = true;                           
							}
							LT::Entry entrylt(InStruct.words[i].word[0], InStruct.words[i].line); // создаём элемент ТЛ
							LT::Add(Tables.Lextable, entrylt); // занесение элемента в ТЛ
							break;
						}

						default:
						{
							LT::Entry entrylt(InStruct.words[i].word[0], InStruct.words[i].line); // создаём элемент ТЛ
							LT::Add(Tables.Lextable, entrylt); // занесение элемента в таблицу лексем
						}
						}
						break;
					}
					case LEX_ID_TYPE_S: // лексема типа данных
					case LEX_ID_TYPE_I: // лексема типа данных
						idType = graph[j].graph.type; // заполнение поля типа данных
					default:
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.words[i].line); // создание элемента ТЛ
						LT::Add(Tables.Lextable, entrylt); // занесение элемента в ТЛ
						break;
					}
					}
					break;
				}
				
			}
			if (FlagEx == false) {
				throw ERROR_THROW_IN(32, InStruct.words[i].line, NULL); //останавливаем работу программы
			}
		}
		if (Tables.Lextable.size == LT_MAXSIZE)
		{
			throw ERROR_THROW(31);
		}
		if (Tables.IDtable.size == TI_MAXSIZE)
		{
			throw ERROR_THROW(30);
		}
		if (!MainBody) // если небыло гл ф-ции
		{
			flag1 = true;
			Log::writeError(log.stream, Error::GetError(83)); // ошибка отсутствие главной ф-ции
		}
		if (LibBody == 0 && MyFunc>0)
			Log::writeError(log.stream, Error::GetError(88)); // не подключена библиотека
	

		if (flag1 == false && flag2 == false)
		{
			for (int i = 0; i < Tables.Lextable.size; i++) // проверка выражний и не стандратных функций
			{
				if (Tables.Lextable.table[i].lexema == LEX_ID)
				{
					if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == IT::F) //если после функции нет открывающейся скобки
					{
						if (Tables.Lextable.table[i + 1].lexema != LEX_LEFTTHESIS)
							Log::writeError(log.stream, Error::GetError(95, InStruct.words[i + 1].line, NULL));
					}
				}

				if (Tables.Lextable.table[i].lexema == LEX_STAR || Tables.Lextable.table[i].lexema == LEX_DIRSLASH || Tables.Lextable.table[i].lexema == LEX_MINUS || Tables.Lextable.table[i].lexema == LEX_PLUS)
				{//если вокруг знаков операций что-то помимо ID,литерала и скобок
					if (Tables.Lextable.table[i - 1].lexema != LEX_ID && Tables.Lextable.table[i - 1].lexema != LEX_LEFTTHESIS && Tables.Lextable.table[i - 1].lexema != LEX_RIGHTTHESIS && Tables.Lextable.table[i - 1].lexema != LEX_LITERAL)
						Log::writeError(log.stream, Error::GetError(605, InStruct.words[i + 1].line, NULL)); //ошибка в построении выражения
					if (Tables.Lextable.table[i + 1].lexema != LEX_ID && Tables.Lextable.table[i + 1].lexema != LEX_LEFTTHESIS && Tables.Lextable.table[i + 1].lexema != LEX_RIGHTTHESIS && Tables.Lextable.table[i + 1].lexema != LEX_LITERAL)
						Log::writeError(log.stream, Error::GetError(605, InStruct.words[i + 1].line, NULL)); //ошибка в построении выражения
				}
				if (Tables.Lextable.table[i].lexema == LEX_EQUAL) //проверка типов в выражении после знака =
				{
					bool FlagForFun = false; //для функций, вызываемых в main
					int pos = i+1;
					idType = Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype; //тип переменной до =
					if ((Tables.Lextable.table[pos].lexema == LEX_ID && Tables.IDtable.table[Tables.Lextable.table[pos].idxTI].idtype == IT::F) || ((Tables.Lextable.table[pos].lexema == LEX_POWER || Tables.Lextable.table[pos].lexema == LEX_ROOT)&& Tables.IDtable.table[Tables.Lextable.table[pos].idxTI].idtype == IT::S))
						FlagForFun = true; //чтобы проверка несоответствия типов не распространялась на вызов функции в main
					while (Tables.Lextable.table[pos].lexema != LEX_SEPARATOR)
					{
						if (idType == IT::STR && (Tables.Lextable.table[pos].lexema == LEX_STAR || Tables.Lextable.table[pos].lexema == LEX_DIRSLASH || Tables.Lextable.table[pos].lexema == LEX_MINUS || Tables.Lextable.table[pos].lexema == LEX_PLUS))
							Log::writeError(log.stream, Error::GetError(90, InStruct.words[i].line, NULL));//если переменная строкового типа и мы пытаемся делать с ней какие-то операции

						if (Tables.Lextable.table[pos].lexema == LEX_DIRSLASH && Tables.Lextable.table[pos + 1].lexema == LEX_LITERAL && Tables.IDtable.table[Tables.Lextable.table[pos + 1].idxTI].value.vNUM == 0)
							Log::writeError(log.stream, Error::GetError(87, InStruct.words[pos+1].line, NULL)); //попытка разделить на 0

						if ((Tables.Lextable.table[pos].lexema == LEX_ID || Tables.Lextable.table[pos].lexema == LEX_LITERAL) && Tables.IDtable.table[Tables.Lextable.table[pos].idxTI].iddatatype != idType && FlagForFun == false)
							Log::writeError(log.stream, Error::GetError(85, InStruct.words[pos].line, NULL)); //несоответствие типов в выражении (если перед и после знаков не скобочки)
						pos++;
					}
					FlagForFun = false;
				}
				
			}
			bool FlagForMain = false; int some_count = 0; char some_buffer[INT_MAXSIZE_PARM];
			for (int i = 0; i < Tables.Lextable.size; i++)
			{
				if (Tables.Lextable.table[i].lexema == LEX_MAIN)
					FlagForMain = true;

				if (FlagForMain == true)
				{//проверка параметров
					if ((Tables.Lextable.table[i].lexema == LEX_ID && Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == IT::F) || ((Tables.Lextable.table[i].lexema == LEX_POWER || Tables.Lextable.table[i].lexema == LEX_ROOT) && Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == IT::S))
					{	
							int param = 0;

							if (Tables.Lextable.table[i + 1].lexema == LEX_LEFTTHESIS)
							{
								int k = i + 1;
								while (Tables.Lextable.table[k].lexema != LEX_RIGHTTHESIS)
								{
									if (Tables.Lextable.table[k].lexema == LEX_ID || Tables.Lextable.table[k].lexema == LEX_LITERAL)
									{
										if (Tables.IDtable.table[Tables.Lextable.table[k].idxTI].iddatatype == IT::STR)
											some_buffer[some_count] = 'w';
										if (Tables.IDtable.table[Tables.Lextable.table[k].idxTI].iddatatype == IT::INT)
											some_buffer[some_count] = 'n';
										some_count++;
									}
									k++;
								}
								if (some_count != Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm)
								{
									Log::writeError(log.stream, Error::GetError(92, InStruct.words[i + 1].line, NULL));
								}
								for (int r = 0; r < some_count; r++)
									if (some_buffer[r] != Tables.IDtable.table[Tables.Lextable.table[i].idxTI].parms[r] && some_count <= Tables.IDtable.table[Tables.Lextable.table[i].idxTI].count_parm)
									{
										Log::writeError(log.stream, Error::GetError(93, InStruct.words[i + 1].line, NULL));
									}
								some_count = 0;
						}
					}
				}
			}
		}
		return Tables; // возвращаем ТИ ТЛ
	}
}