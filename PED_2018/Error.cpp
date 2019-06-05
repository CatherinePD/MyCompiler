#include "stdafx.h"

namespace Error
{ //	0   -  9   -  ���������
	//	10  -  19  -  ������� ����������
	//	20  -  29  -  �������� � ������ ������
	//	30  -  49  -  ������ ������������ �������
	//  50  -  79  -  ������ ��������������� �������
	//  80  -  99  -  ������ �������������� �������
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "������������ ��� ������"), // ��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),

		ERROR_ENTRY(10, "�������� -in ������ ���� �����"),
		ERROR_ENTRY(11, "��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(12), ERROR_ENTRY_NODEF(13), ERROR_ENTRY_NODEF(14), ERROR_ENTRY_NODEF(15),
		ERROR_ENTRY_NODEF(16), ERROR_ENTRY_NODEF(17), ERROR_ENTRY_NODEF(18), ERROR_ENTRY_NODEF(19),

		ERROR_ENTRY(20, "������ ��� �������� ����� � �������� �����(-in)"),
		ERROR_ENTRY(21, "������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(22, "������ ��� �������� ����� ���������(-log)"),
		ERROR_ENTRY(23, "���������� ����������� ������� � ��������� ��������"),
		ERROR_ENTRY(24, "�������� ������������ ������ ���������� ��������"),
		ERROR_ENTRY_NODEF(25), ERROR_ENTRY_NODEF(26), 
		ERROR_ENTRY_NODEF(27), ERROR_ENTRY_NODEF(28), ERROR_ENTRY_NODEF(29),

		ERROR_ENTRY(30, "�������� ������ ������� ���������������"),
		ERROR_ENTRY(31, "�������� ������ ������� ������"),
		ERROR_ENTRY(32, "C���� �� ���������"),
		ERROR_ENTRY_NODEF(33), ERROR_ENTRY_NODEF(34), ERROR_ENTRY_NODEF(35), 
		ERROR_ENTRY_NODEF(36), ERROR_ENTRY_NODEF(37), ERROR_ENTRY_NODEF(38), 
		ERROR_ENTRY_NODEF(39), ERROR_ENTRY_NODEF10(40),

		ERROR_ENTRY(50, "�������� ��������� ���������"),
		ERROR_ENTRY(51, "������ � ���������� ������� "),
		ERROR_ENTRY(52, "��������� �����������"),
		ERROR_ENTRY(53, "������ � ���������"),
		ERROR_ENTRY(54, "������ � ���������� ���������� �������"),
		ERROR_ENTRY(55, "������ � ���������� ���������"),
		ERROR_ENTRY(56, "������������ ������������� ������ �������������� �������� ��� �������� ������������"), //�� ����� ����
		ERROR_ENTRY_NODEF(57), ERROR_ENTRY_NODEF(58), ERROR_ENTRY_NODEF(59),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70),

		ERROR_ENTRY(80, "��������� ������������ ���������� ���������� ��� ������ �������"),
		ERROR_ENTRY(81, "������� ��������������� ��������������"),
		ERROR_ENTRY(82, "����������� ���������� ��������������"),
		ERROR_ENTRY(83, "����������� ����� ����� main"),
		ERROR_ENTRY(84, "����� ����� main ������ ���� ������������"),
		ERROR_ENTRY(85, "�������������� �����"),
		ERROR_ENTRY(86, "��������� ����������� �������� �������"),
		ERROR_ENTRY(87, "��������� ������ �� ����"),
		ERROR_ENTRY(88, "������������� ����������� ������� ��� ����������� ����������� ����������"),
		ERROR_ENTRY(89, "������� ���������� ����������� ���������� ����� ������ ����"),
		ERROR_ENTRY(90, "������� ���������� �������� �� ��������� ����� ������"),
		ERROR_ENTRY(91, "��� ������������� �������� � ��� ������� �� ���������"),
		ERROR_ENTRY(92, "������������ ���������� ���������� ��� ������ �������"),
		ERROR_ENTRY(93, "������������ ��� ���������� ��� ������ �������"),
		ERROR_ENTRY(94, "��������� ���������� ���������� ���������� �������"),
		ERROR_ENTRY(95, "������������ ����� �������"),
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