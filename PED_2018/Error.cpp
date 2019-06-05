#include "stdafx.h"

namespace Error
{ //	0   -  9   -  системные
	//	10  -  19  -  входных параметров
	//	20  -  29  -  открытия и чтения файлов
	//	30  -  49  -  ошибки лексического анализа
	//  50  -  79  -  ошибки синтаксического анализа
	//  80  -  99  -  ошибки семантического анализа
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"), // код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),

		ERROR_ENTRY(10, "Параметр -in должен быть задан"),
		ERROR_ENTRY(11, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(12), ERROR_ENTRY_NODEF(13), ERROR_ENTRY_NODEF(14), ERROR_ENTRY_NODEF(15),
		ERROR_ENTRY_NODEF(16), ERROR_ENTRY_NODEF(17), ERROR_ENTRY_NODEF(18), ERROR_ENTRY_NODEF(19),

		ERROR_ENTRY(20, "Ошибка при открытии файла с исходным кодом(-in)"),
		ERROR_ENTRY(21, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(22, "Ошибка при создании файла протокола(-log)"),
		ERROR_ENTRY(23, "Отсутствие закрывающей кавычки в строковом литерале"),
		ERROR_ENTRY(24, "Превышен максимальный размер строкового литерала"),
		ERROR_ENTRY_NODEF(25), ERROR_ENTRY_NODEF(26), 
		ERROR_ENTRY_NODEF(27), ERROR_ENTRY_NODEF(28), ERROR_ENTRY_NODEF(29),

		ERROR_ENTRY(30, "Превышен размер таблицы идентификаторов"),
		ERROR_ENTRY(31, "Превышен размер таблицы лексем"),
		ERROR_ENTRY(32, "Cлово не разобрано"),
		ERROR_ENTRY_NODEF(33), ERROR_ENTRY_NODEF(34), ERROR_ENTRY_NODEF(35), 
		ERROR_ENTRY_NODEF(36), ERROR_ENTRY_NODEF(37), ERROR_ENTRY_NODEF(38), 
		ERROR_ENTRY_NODEF(39), ERROR_ENTRY_NODEF10(40),

		ERROR_ENTRY(50, "Неверная структура программы"),
		ERROR_ENTRY(51, "Ошибка в параметрах функции "),
		ERROR_ENTRY(52, "Ошибочная конструкция"),
		ERROR_ENTRY(53, "Ошибка в выражении"),
		ERROR_ENTRY(54, "Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(55, "Ошибка в построении выражения"),
		ERROR_ENTRY(56, "Неправильное использование знаков арифметических операций или операции присваивания"), //на этапе лекс
		ERROR_ENTRY_NODEF(57), ERROR_ENTRY_NODEF(58), ERROR_ENTRY_NODEF(59),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70),

		ERROR_ENTRY(80, "Превышено максимальное количество параметров при вызове функции"),
		ERROR_ENTRY(81, "Попытка переопределения идентификатора"),
		ERROR_ENTRY(82, "Отсутствует объявление идентификатора"),
		ERROR_ENTRY(83, "Отсутствует точка входа main"),
		ERROR_ENTRY(84, "Точка входа main должна быть единственной"),
		ERROR_ENTRY(85, "Несоответствие типов"),
		ERROR_ENTRY(86, "Запрещено присваивать значение функции"),
		ERROR_ENTRY(87, "Запрещено делить на ноль"),
		ERROR_ENTRY(88, "Использование стандартных функций без подключения стандартной библиотеки"),
		ERROR_ENTRY(89, "Попытка подключить стандартную библиотеку более одного раза"),
		ERROR_ENTRY(90, "Попытка проведения операций со строковым типом данных"),
		ERROR_ENTRY(91, "Тип возвращаемого значения и тип функции не совпадают"),
		ERROR_ENTRY(92, "Неправильное количество параметров при вызове функции"),
		ERROR_ENTRY(93, "Неправильный тип параметров при вызове функции"),
		ERROR_ENTRY(94, "Превышено допустимое количество параметров функции"),
		ERROR_ENTRY(95, "Неправильный вызов функции"),
		ERROR_ENTRY_NODEF(96), ERROR_ENTRY_NODEF(97),
		ERROR_ENTRY_NODEF(98), ERROR_ENTRY_NODEF(99)
	};


	ERROR GetError(int id)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY)
			return errors[0];
		else
			return errors[id];
	}

	ERROR GetError(int id, int line, int col)
	{
		ERROR dopError = GetError(id);
		dopError.position.col = col;
		dopError.position.line = line;
		return dopError;
	}
}