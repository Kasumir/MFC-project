// SaveDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SpongeBob.h"
#include "SaveDialog.h"
#include "afxdialogex.h"


// SaveDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(SaveDialog, CDialog)

SaveDialog::SaveDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SAVEDIALOG, pParent)
{

}

SaveDialog::~SaveDialog()
{
}

void SaveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_str);
}


BEGIN_MESSAGE_MAP(SaveDialog, CDialog)
END_MESSAGE_MAP()


// SaveDialog �޽��� ó�����Դϴ�.


void SaveDialog::OnOK()
{
	GetDlgItemText(IDC_STR1, str);
	CDialog::OnOK();
}
