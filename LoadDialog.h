#pragma once
#include "afxwin.h"


// LoadDialog ��ȭ �����Դϴ�.

typedef struct Filename
{
	int size;
	CString name;
}filename;


class LoadDialog : public CDialog
{
	DECLARE_DYNAMIC(LoadDialog)

public:
	LoadDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~LoadDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	CString str;
	CList<filename, filename> tmp_list;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};