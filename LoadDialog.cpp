// LoadDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SpongeBob.h"
#include "LoadDialog.h"
#include "afxdialogex.h"


// LoadDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(LoadDialog, CDialog)

LoadDialog::LoadDialog(CWnd* pParent /*=NULL*/)
	: CDialog(331, pParent)
{

}

LoadDialog::~LoadDialog()
{
}

void LoadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}


BEGIN_MESSAGE_MAP(LoadDialog, CDialog)
END_MESSAGE_MAP()


// LoadDialog 메시지 처리기입니다.


void LoadDialog::OnOK()
{
	int nIndex = m_list.GetCurSel();
	m_list.GetText(nIndex, str);

	CDialog::OnOK();
}


BOOL LoadDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	for(POSITION p = tmp_list.GetHeadPosition(); p != NULL; tmp_list.GetNext(p)){
		filename tmp = tmp_list.GetAt(p);
		CString str = tmp.name;
		int i = str.Find(_T(".txt"));
		str.Delete(i + 4, 100);
		m_list.AddString(str);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
