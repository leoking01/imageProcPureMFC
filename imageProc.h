
// imageProc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CimageProcApp:
// �йش����ʵ�֣������ imageProc.cpp
//

class CimageProcApp : public CWinApp
{
public:
	CimageProcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CimageProcApp theApp;
