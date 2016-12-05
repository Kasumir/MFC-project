#pragma once
#include "afxwin.h"


// LoadDialog 대화 상자입니다.

typedef struct Filename
{
	int size;
	CString name;
}filename;


class LoadDialog : public CDialog
{
	DECLARE_DYNAMIC(LoadDialog)

public:
	LoadDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~LoadDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	CString str;
	CList<filename, filename> tmp_list;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};