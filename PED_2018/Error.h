#pragma once
#define ERROR_MAXSIZE_MESSAGE 200	
#define ERROR_MAX_ENTRY 100		
#define ERROR_THROW(id) Error::GetError(id);				
#define ERROR_THROW_IN(id, line, col) Error::GetError(id, line, col);	//throw	ERROR_THROW(id, строка, колонка)
#define ERROR_ENTRY(id, message) {id, message}	//элемент таблицы ошибок
#define ERROR_ENTRY_NODEF(id)		ERROR_ENTRY(id, "Неопределенная ошибка")

#define ERROR_ENTRY_NODEF10(id)		ERROR_ENTRY_NODEF(id+0),ERROR_ENTRY_NODEF(id+1),ERROR_ENTRY_NODEF(id+2),ERROR_ENTRY_NODEF(id+3), \
									ERROR_ENTRY_NODEF(id + 4), ERROR_ENTRY_NODEF(id + 5), ERROR_ENTRY_NODEF(id + 6), ERROR_ENTRY_NODEF(id + 7), \
									ERROR_ENTRY_NODEF(id + 8), ERROR_ENTRY_NODEF(id + 9)


namespace Error
{
	struct ERROR								//тип исключения для throw ERROR_THROW | ERROR_THROW_IN в catch(ERROR)
	{
		int id;									//код ошибки
		char message[ERROR_MAXSIZE_MESSAGE];	//сообщение об ошибке
		struct IN								//расширение для ошибок при обработке входных данных
		{
			short line = -1;								//номер строки (0, 1, 2, ...)
			short col = -1;							//номер позиции в строке(0, 1, 2, ...)
		} position;
	};

	ERROR GetError(int id);							//сформировать ERROR для ERROR_THROW
	ERROR GetError(int id, int line, int col);	//сформировать ERROR для ERROR_THROW_IN
}