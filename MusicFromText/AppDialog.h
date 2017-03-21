
// AppDialog.h : header file
//

#pragma once

#include "MFT_Parser.h"
#include "MFT_Player.h"
#include "afxwin.h"

// AppDialog dialog
class AppDialog : public CDialogEx
{
// Construction
public:
	AppDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUSICFROMTEXT_DIALOG };
#endif

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
	int volumeText;
	int bpmText;
	int octaveText;
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonRecord();
	CString playText;
	CComboBox instrumentCombo;
	CButton playButton;
	CButton pauseButton;
	CButton stopButton;
	CButton openButton;
	CButton saveButton;
	CButton recordButton;
private:
	Parser _parser;
	Player *_player = nullptr;
	CWinThread *_t_player = nullptr;
};
