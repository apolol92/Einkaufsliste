
// EinkaufslisteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Einkaufsliste.h"
#include "EinkaufslisteDlg.h"
#include "afxdialogex.h"
#include <bitset>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif






// CEinkaufslisteDlg dialog
CEinkaufslisteDlg::CEinkaufslisteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEinkaufslisteDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEinkaufslisteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_NITEM_EDIT_CONTROL, ceItem2Buy);
	DDX_Control(pDX, IDC_BUYING_LIST, lbItemList);
	DDX_Control(pDX, IDC_BUTTON_DELETE, btDelete);
}

BEGIN_MESSAGE_MAP(CEinkaufslisteDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD_ITEM, &CEinkaufslisteDlg::OnBnClickedButtonAddItem)

	ON_LBN_SELCHANGE(IDC_BUYING_LIST, &CEinkaufslisteDlg::OnLbnSelchangeBuyingList)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CEinkaufslisteDlg::OnBnClickedButtonDelete)
	ON_COMMAND(ID_EINKAUFSLISTE_SPEICHERN32773, &CEinkaufslisteDlg::OnEinkaufslisteSpeichern32773)
	ON_COMMAND(ID_EINKAUFSLISTE_LADEN32774, &CEinkaufslisteDlg::OnEinkaufslisteLaden32774)
	ON_COMMAND(ID_EINKAUFSLISTE_SAVEAS, &CEinkaufslisteDlg::OnEinkaufslisteSaveas)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CEinkaufslisteDlg message handlers

BOOL CEinkaufslisteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEinkaufslisteDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEinkaufslisteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEinkaufslisteDlg::OnBnClickedButtonAddItem()
{

	// TODO: Add your control notification handler code here
	CString strItem2Buy;
	ceItem2Buy.GetWindowText(strItem2Buy);
	if(strItem2Buy.TrimRight().TrimLeft().GetLength()>0)
	{
		lbItemList.AddString(strItem2Buy);	
		ceItem2Buy.SetWindowTextW(_T(""));
	}
	else
	{
		int i = AfxMessageBox(_T("Geben Sie bitte das zukaufende Produkt an"), MB_OK|MB_ICONSTOP);
	}
	ceItem2Buy.SetFocus();

}





void CEinkaufslisteDlg::OnLbnSelchangeBuyingList()
{
	// TODO: Add your control notification handler code here
	btDelete.EnableWindow(true);
}




void CEinkaufslisteDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	int index = lbItemList.GetCurSel();
	lbItemList.DeleteString(index);
	btDelete.EnableWindow(false);
}


void CEinkaufslisteDlg::OnEinkaufslisteSpeichern32773()
{
	// TODO: Add your command handler code here
	CFileDialog FileDlg(FALSE, CString(".rpr"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT);
	UpdateData(TRUE);
	if(savePath.Compare(_T(""))==0){
		if (FileDlg.DoModal() == IDOK)  
		{
			savePath = FileDlg.GetPathName();
			//AfxMessageBox(FileDlg.GetPathName(), MB_OK|MB_ICONSTOP);

		}
	}
	UpdateData(TRUE);
	CString m_strEdit("");

	for(int i = 0; i < lbItemList.GetCount(); i++)
	{
		CString itemText;
		lbItemList.GetText(i,itemText);
		m_strEdit.Append(itemText + "\n");
	}
	CFile file;
	savePath = FileDlg.GetPathName();
	file.Open(savePath, CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	ar << m_strEdit;

	ar.Close();
	file.Close();
}


void CEinkaufslisteDlg::OnEinkaufslisteLaden32774()
{
	// TODO: Add your command handler code here
	CFileDialog FileDlg(TRUE, CString(".rpr"), NULL, OFN_HIDEREADONLY);
	CString m_strEdit;
	if (FileDlg.DoModal() == IDOK)  
	{  
		CFile file;
		savePath = FileDlg.GetPathName();
		file.Open(savePath, CFile::modeRead);
		if(file) {
			CArchive ar(&file, CArchive::load);

			ar >> m_strEdit;

			ar.Close();
			file.Close();
		}

		UpdateData(FALSE);
		lbItemList.ResetContent();
		int nTokenPos = 0;
		CString strToken = m_strEdit.Tokenize(_T("\n"), nTokenPos);
		lbItemList.AddString(strToken);
		while (!strToken.IsEmpty())
		{
			strToken = m_strEdit.Tokenize(_T("\n"), nTokenPos);
			if(strToken.Trim().GetLength()!=0){
				lbItemList.AddString(strToken);
			}
		}

	}
}


void CEinkaufslisteDlg::OnEinkaufslisteSaveas()
{
	// TODO: Add your command handler code here
	CFileDialog FileDlg(FALSE, CString(".rpr"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT);
	UpdateData(TRUE);

	if (FileDlg.DoModal() == IDOK)  
	{  
		//AfxMessageBox(FileDlg.GetPathName(), MB_OK|MB_ICONSTOP);
		UpdateData(TRUE);
		CString m_strEdit("");

		for(int i = 0; i < lbItemList.GetCount(); i++)
		{
			CString itemText;
			lbItemList.GetText(i,itemText);
			m_strEdit.Append(itemText + "\n");
		}
		CFile file;
		savePath = FileDlg.GetPathName();
		file.Open(savePath, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		ar << m_strEdit;

		ar.Close();
		file.Close();
	}
}


void CEinkaufslisteDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.
	lpMMI->ptMinTrackSize.x = 577;
	lpMMI->ptMinTrackSize.y = 470;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
