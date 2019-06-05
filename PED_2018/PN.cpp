#include "stdafx.h"

int PN::priority(char znak)
{
	switch (znak)
	{
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	default:
		return 0;
	}
}

int PN::search(int index, LA::LEX *tables) //����� ���������
{
	for (int i = index; i < tables->Lextable.size; i++) //������� ������
	{
		if (tables->Lextable.table[i].lexema == LEX_PLUS || tables->Lextable.table[i].lexema == LEX_MINUS
			|| tables->Lextable.table[i].lexema == LEX_STAR || tables->Lextable.table[i].lexema == LEX_DIRSLASH) //������� ��������
		{
			for (; ; i--) //���������� ������� �������
			{
				if (tables->Lextable.table[i].lexema == LEX_EQUAL || tables->Lextable.table[i].lexema == LEX_RIGHTTHESIS)
					return i + 1;
			}
		}
	}
	return -1; //���� �� ����� ���������� ����� 1
}

bool PN::CreatePolishNotation(LA::LEX *tables)
{
	std::stack <LT::Entry> stack_operators;// �������� ���������
	bool build = false;

	int i = 0;
	int j = 0;
	int k = 0;

	while (search(i, tables) != -1)
	{
		j = i = search(i, tables);//������ ������� ������� ����� �����
		for (; tables->Lextable.table[i].lexema != LEX_SEPARATOR; i++, k++) //������ �� ������� ����� ������, ���������� ������� �
		{
			if (tables->Lextable.table[i].lexema == LEX_LEFTTHESIS || tables->Lextable.table[i].lexema == LEX_RIGHTTHESIS) //���� ����� ( ��� )
			{
				switch (tables->Lextable.table[i].lexema) //������� ����� �������
				{
				case LEX_LEFTTHESIS:
				{
					if ((tables->Lextable.table[i - 1].idxTI != -1 && tables->IDtable.table[tables->Lextable.table[i - 1].idxTI].idtype == IT::F)
						|| tables->Lextable.table[i - 1].lexema == 'k' || tables->Lextable.table[i - 1].lexema == 'b')  // ����� -1 ���� ��� �� ����� ������� ����������
					{
						while (tables->Lextable.table[i - 1].lexema != LEX_RIGHTTHESIS)
						{
							i++;
						}
						break;
					}
					stack_operators.push(tables->Lextable.table[i]);// ( ��������� � ���� ���������� ������� ������� ������
					break;
				}
				case LEX_RIGHTTHESIS:
					while (stack_operators.top().lexema != LEX_LEFTTHESIS) // ) ���������� ������ ������� �� �����
					{
						result[size++] = stack_operators.top();
						stack_operators.pop(); //��������� ������� ����� ����������
					}
					stack_operators.pop(); //��������� ������� ����� ����������
					break;
				}
			}
			else
			{
				switch (tables->Lextable.table[i].lexema) //���� ��� �� ������()
				{
				case LEX_STAR:
				case LEX_DIRSLASH:
				{
					stack_operators.push(tables->Lextable.table[i]);//��������� � ���� ���������� ������� ������� ������
					break;
				}
				case LEX_PLUS:
				case LEX_MINUS:
					if (stack_operators.empty() || priority(tables->Lextable.table[i].lexema) == priority(stack_operators.top().lexema))//����
						stack_operators.push(tables->Lextable.table[i]);//��������� � ���� ���������� ������� ������� ������ 
					else //���� ���������� �� ������
					{
						while (!stack_operators.empty() && stack_operators.top().lexema != LEX_LEFTTHESIS &&
							priority(tables->Lextable.table[i].lexema) < priority(stack_operators.top().lexema)) //���� ������� � ����� �� (, � ��������� �������� ������ ���� ����� ���������� �������� � ������ �����, ��..
						{
							result[size++] = stack_operators.top(); //������� �������� ����� � ���������
							stack_operators.pop();//��������� �������� �����
						}
						if (!stack_operators.empty() && stack_operators.top().lexema == LEX_LEFTTHESIS)// ��������� �������� �����
						{
							stack_operators.push(tables->Lextable.table[i]);//�������� � ���� ���������� ������� ������� ������
						}
						if (stack_operators.empty())// ��������� �������� �����
						{
							stack_operators.push(tables->Lextable.table[i]);//�������� � ���� ���������� ������� ������� ������
						}
					}
					break;
				default:
					result[size++] = tables->Lextable.table[i];//������� ������� ������ � ���������
					break;
				}
			}
		}
		for (; !stack_operators.empty(); i++)	//������ ��� ��������� � �������� ����
		{
			result[size++] = stack_operators.top(); //������� ��� ��������� � ���������
			stack_operators.pop();// �������� �������� �����
		}
		for (int i = 0; i < size; j++, i++, k--) //���������� ������� ������, ��� ������� ���������
		{
			tables->Lextable.table[j].lexema = result[i].lexema;
			tables->Lextable.table[j].idxTI = result[i].idxTI;
			tables->Lextable.table[j].sn = result[i].sn; //������ ��� � ���� ����
			tables->IDtable.table[result[i].idxTI].idxfirstLE;
		}
		for (; k > 0; k--, j++)	//��������� ��� ��������, "�������� � �������� �������� ��������"
		{
			tables->Lextable.table[j].lexema = NULL;
			tables->Lextable.table[j].idxTI = NULL;
		}
		size = 0;
		build = true;
	}
	return build;
}