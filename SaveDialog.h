#pragma once
#include "afxwin.h"


// SaveDialog ��ȭ �����Դϴ�.

class SaveDialog : public CDialog
{
	DECLARE_DYNAMIC(SaveDialog)

public:
	SaveDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SaveDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_str;
	CString str;
	virtual void OnOK();
};
