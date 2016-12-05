// LoadDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SpongeBob.h"
#include "LoadDialog.h"
#include "afxdialogex.h"


// LoadDialog ��ȭ �����Դϴ�.

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


// LoadDialog �޽��� ó�����Դϴ�.


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
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
