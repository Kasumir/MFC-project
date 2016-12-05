#pragma once
#include "afxwin.h"


// SaveDialog 대화 상자입니다.

class SaveDialog : public CDialog
{
	DECLARE_DYNAMIC(SaveDialog)

public:
	SaveDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SaveDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_str;
	CString str;
	virtual void OnOK();
};
