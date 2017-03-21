
// AppDialog.cpp : implementation file
//

#include "stdafx.h"
#include "AppMain.h"
#include "AppDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// AppDialog dialog



AppDialog::AppDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MUSICFROMTEXT_DIALOG, pParent)
	, playText(_T(""))
	, volumeText(0)
	, bpmText(0)
	, octaveText(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void AppDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, playText);
	DDX_Text(pDX, IDC_EDIT4, volumeText);
	DDX_Text(pDX, IDC_EDIT3, bpmText);
	DDX_Text(pDX, IDC_EDIT2, octaveText);
	DDX_Control(pDX, IDC_COMBO1, instrumentCombo);
	DDX_Control(pDX, IDC_BUTTON1, playButton);
	DDX_Control(pDX, IDC_BUTTON5, pauseButton);
	DDX_Control(pDX, IDC_BUTTON4, stopButton);
	DDX_Control(pDX, IDC_BUTTON2, openButton);
	DDX_Control(pDX, IDC_BUTTON3, saveButton);
	DDX_Control(pDX, IDC_BUTTON6, recordButton);
}

BEGIN_MESSAGE_MAP(AppDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &AppDialog::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON2, &AppDialog::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON3, &AppDialog::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON4, &AppDialog::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON5, &AppDialog::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON6, &AppDialog::OnBnClickedButtonRecord)
END_MESSAGE_MAP()

// Async routine
UINT PlayAsync(LPVOID pParam);

// AppDialog message handlers

BOOL AppDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CFont SFont;
	SFont.CreateFont(15, 7, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, _T("Times New Roman"));
	playButton.SetFont(&SFont);
	pauseButton.SetFont(&SFont);
	stopButton.SetFont(&SFont);
	openButton.SetFont(&SFont);
	saveButton.SetFont(&SFont);
	recordButton.SetFont(&SFont);


	instrumentCombo.SetCurSel(0);

	_player = new Player();
	_t_player = AfxBeginThread(PlayAsync, _player, 0, 0, CREATE_SUSPENDED);
	_t_player->ResumeThread();

	UpdateData();

	volumeText = 100;
	bpmText = 120;
	octaveText = 5;

	UpdateData(FALSE);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void AppDialog::OnPaint()
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
HCURSOR AppDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Async routine

UINT PlayAsync(LPVOID pParam)
{
	Player *player = static_cast<Player *>(pParam);

	while (true)
	{
		if (player->shouldPlay())
		{
			if (player->isPaused())
				player->resume();
			else
				player->playMusic();
		}
	}

	return 0;
}

// Buttons

void AppDialog::OnBnClickedButtonStop() 
{
	UpdateData();
	_player->stop();
	UpdateData(FALSE);
}

void AppDialog::OnBnClickedButtonPause() 
{
	UpdateData();
	_player->pause();
	UpdateData(FALSE);
}

void AppDialog::OnBnClickedButtonPlay()
{
	UpdateData();

	CString fileContent = playText.GetString();
	CT2CA pszConvertedAnsiString(fileContent); // convert CString to std::string
	std::string strStd(pszConvertedAnsiString);
	_parser.setMusicString(strStd);
	
	int volume = volumeText;
	int bpm = bpmText;
	int octave = octaveText;
	int instrument = instrumentCombo.GetCurSel();

	Music *music = _parser.musicFromText(volume, bpm, octave, instrument);

	_player->setMusic(music);
	_player->start();

	UpdateData(FALSE);
}

void AppDialog::OnBnClickedButtonOpen() 
{
	UpdateData();

	CFileDialog dlg(TRUE, _T(".txt"));
	TCHAR buf[MAX_PATH] = { _T('\0') };
	dlg.m_ofn.nMaxFileTitle = MAX_PATH;
	dlg.m_ofn.lpstrFileTitle = buf;
	CString filepath, filename;
	if (dlg.DoModal() == IDOK)
	{
		filepath = dlg.GetFolderPath();
		filename = dlg.GetFileName();
	}
	
	if (!filename.IsEmpty())
	{
		CStdioFile myFile;

		filepath = filepath + "\\" + filename;

		myFile.Open(filepath, CFile::modeRead);
		CString chReadString, chLine;

		while (myFile.ReadString(chLine))
		{
			chReadString += chLine;
			chReadString += "\r\n";
		}

		myFile.Close();
		playText = chReadString;
	}

	UpdateData(FALSE);
}

void AppDialog::OnBnClickedButtonSave()  
{
	TCHAR szFilters[] = _T("MyType Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("txt"), _T("*.txt"),NULL, szFilters);

	UpdateData();

	CString strFilePath;

	if (dlg.DoModal() == IDOK)
		strFilePath = dlg.GetPathName();
	
	if (!strFilePath.IsEmpty())
	{
		CStdioFile file;
		CString textContent = playText.GetString();
		file.Open(strFilePath, CStdioFile::modeReadWrite | CStdioFile::modeCreate);
		file.WriteString(textContent);
		file.Close();
	}

	UpdateData(FALSE);
}


void AppDialog::OnBnClickedButtonRecord()
{

	UpdateData();


	CString fileContent = playText.GetString();
	CT2CA pszConvertedAnsiString(fileContent); // convert CString to std::string
	std::string strStd(pszConvertedAnsiString);

	_parser.setMusicString(strStd);

	int volume = volumeText;
	int bpm = bpmText;
	int octave = octaveText;
	int instrument = instrumentCombo.GetCurSel();

	Music *music = _parser.musicFromText(volume, bpm, octave, instrument);


	TCHAR szFilters[] = _T("MyType Files (*.midi)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("midi"), _T("*.midi"), NULL, szFilters);

	CString strFilePath;

	if (dlg.DoModal() == IDOK)
		strFilePath = dlg.GetPathName();


	if (!strFilePath.IsEmpty())
	{

		CT2CA pszConvertedAnsiStringPath(strFilePath); // convert CString to std::string
		std::string strStdPath(pszConvertedAnsiStringPath);

		CFugue::SaveAsMidiFile(CFugue::MString(music->toString().c_str()), strStdPath.c_str());
	}
	UpdateData(FALSE);
}
