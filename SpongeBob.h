
// SpongeBob.h : SpongeBob ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CSpongeBobApp:
// �� Ŭ������ ������ ���ؼ��� SpongeBob.cpp�� �����Ͻʽÿ�.
//

class CSpongeBobApp : public CWinApp
{
public:
	CSpongeBobApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSpongeBobApp theApp;
