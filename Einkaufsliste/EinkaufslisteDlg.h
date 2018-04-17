
// EinkaufslisteDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CEinkaufslisteDlg dialog
class CEinkaufslisteDlg : public CDialogEx
{
// Construction
public:
	CEinkaufslisteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EINKAUFSLISTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddItem();
	CEdit ceItem2Buy;
	CListBox lbItemList;
	afx_msg void OnLbnSelchangeBuyingList();
	CButton btDelete;
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnEinkaufslisteSpeichern32773();
	afx_msg void OnEinkaufslisteLaden32774();
private:
	CString savePath;
public:
	afx_msg void OnEinkaufslisteSaveas();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
