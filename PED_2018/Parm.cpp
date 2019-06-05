#include "stdafx.h" 

namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])//argc � ���������� ���������� (int), argv � ������ ���������� �� ������ (_TCHAR* -��������� ������ wchar_t)
	{
		PARM param = { L"", L"", L"", false, L"", false};
		bool fl_in = false, fl_log = false;
		if (argc == 1) //��������� in,log,out �� ������                  
				throw ERROR_THROW(10);
		for (int i = 1; i < argc; i++)
		{
			
			if (wcslen(argv[i]) > PARM_MAX_SIZE)//�������� ��������� �� ����� �������� ��������� � 100
				throw ERROR_THROW(11)
			else
			{
				if (wcsstr(argv[i], PARM_IN) && (wcslen(argv[i]) >= wcslen(PARM_IN))) //��������� ������ � ����������
				{
					wcscpy_s(param.in, argv[i] + wcslen(PARM_IN)); //������ ���������� ����� ���������
					fl_in = true;
				}
				if (wcsstr(argv[i], PARM_LOG) && (wcslen(argv[i]) >= wcslen(PARM_LOG))) //���� �������� log � ����� ��������� ��������
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

		if (fl_in == false)//�������� ����� �� �������� -in ����
			throw ERROR_THROW(10);//���������� ������  "�������� -in ������ ���� �����"


		if (fl_log == false)
		{
			wcscpy_s(param.log, param.in);//��������
			wcsncat_s(param.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));//����������� sizeof �������� PARM_LOG_DEFAULT_EXT � parm.log
		};

		return param;
	};
}
