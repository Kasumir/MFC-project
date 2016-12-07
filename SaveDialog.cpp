// SaveDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SpongeBob.h"
#include "SaveDialog.h"
#include "afxdialogex.h"


// SaveDialog 대화 상자입니다.

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


// SaveDialog 메시지 처리기입니다.


void SaveDialog::OnOK()
{
	GetDlgItemText(IDC_STR1, str);
	CDialog::OnOK();
}
