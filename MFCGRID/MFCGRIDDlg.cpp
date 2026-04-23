// MFCGRIDDlg.cpp: 구현 파일
#include "pch.h"
#include "framework.h"
#include "MFCGRID.h"
#include "MFCGRIDDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX) { CDialogEx::DoDataExchange(pDX); }
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCGRIDDlg 대화 상자
CMFCGRIDDlg::CMFCGRIDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCGRID_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGRIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_ctrlGrid);
	//  DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDX_Control(pDX, IDC_WIDTH, m_nWidth);
	DDX_Control(pDX, IDC_SLIDER_THRESHOLD, m_sldThreshold);
	DDX_Text(pDX, IDC_THRESHOLD, m_nThreshold);
	DDX_Control(pDX, IDC_HEIGHT, m_nHeight);
}

BEGIN_MESSAGE_MAP(CMFCGRIDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL() // 슬라이더 메시지 핸들러
	ON_BN_CLICKED(IDC_CREATE, &CMFCGRIDDlg::OnBnClickedCreate)
	ON_BN_CLICKED(IDC_RANDOM, &CMFCGRIDDlg::OnBnClickedRandom)
	ON_BN_CLICKED(IDC_ADD, &CMFCGRIDDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_HORIZ, &CMFCGRIDDlg::OnBnClickedHoriz)
	ON_BN_CLICKED(IDC_VERTI, &CMFCGRIDDlg::OnBnClickedVerti)
	ON_BN_CLICKED(IDC_FLIP, &CMFCGRIDDlg::OnBnClickedFlip)
	ON_BN_CLICKED(IDC_FLIPCCW, &CMFCGRIDDlg::OnBnClickedFlipCcw)
	ON_BN_CLICKED(IDC_SETTHRE, &CMFCGRIDDlg::OnBnClickedSetThre)
END_MESSAGE_MAP()

// CMFCGRIDDlg 메시지 처리기
BOOL CMFCGRIDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	MoveWindow(0, 0, 1280, 950);
	m_sldThreshold.SetRange(0, 255);

	return TRUE;
}

void CMFCGRIDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CMFCGRIDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMFCGRIDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// =======만들기 버튼 누를 때======
void CMFCGRIDDlg::OnBnClickedCreate()
{
	UpdateData(TRUE);
	m_ctrlGrid.DeleteAllItems();	//기존 적혀 있던 숫자들 삭제
	m_ctrlGrid.SetEditable(FALSE);	//셀 편집 비활성화
	int nInputHeight = GetDlgItemInt(IDC_HEIGHT);	//해당 에디트 박스에 적힌 int 가져오기
	int nInputWidth = GetDlgItemInt(IDC_WIDTH);

	if (nInputHeight > 20 || nInputWidth > 20) {
		AfxMessageBox(_T("최대 크기는 20*20 입니다."), (MB_OK | MB_ICONEXCLAMATION));
		if (nInputHeight > 20) {
			nInputHeight = 20;
			SetDlgItemInt(IDC_HEIGHT, nInputHeight);
		}
		if (nInputWidth > 20) {
			nInputWidth = 20;
			SetDlgItemInt(IDC_WIDTH, nInputWidth);
		}
	}
	ResizeGrid(nInputHeight, nInputWidth);
	m_arr2D_view.clear();
	m_arr2D_ori.clear(); // 배열 초기화
	UpdateData(FALSE);
}

// =======난수 버튼 누를 때======
void CMFCGRIDDlg::OnBnClickedRandom()
{
	UpdateData(TRUE);
	int nInputHeight = m_ctrlGrid.GetRowCount();
	int nInputWidth = m_ctrlGrid.GetColumnCount();
	for (int col = 0; col < nInputWidth; col++) {
		for (int row = 0; row < nInputHeight; row++) {
			int x = rand() % 256;	//랜덤 함수 0~255
			m_ctrlGrid.SetItemTextFmt(row, col, _T("%d"), x);
		}
	}
	m_ctrlGrid.Invalidate();	//그리드 화면 새로 고침 필수
	UpdateData(FALSE);
}

// =======저장(더하기) 버튼 누를 때======
void CMFCGRIDDlg::OnBnClickedAdd()
{
	int nInputHeight = m_ctrlGrid.GetRowCount();
	int nInputWidth = m_ctrlGrid.GetColumnCount();

	m_arr2D_ori.assign(nInputHeight, std::vector<int>(nInputWidth, 0));
	for (int row = 0; row < nInputHeight; row++) {
		for (int col = 0; col < nInputWidth; col++) {
			CString strText = m_ctrlGrid.GetItemText(row, col);	//텍스트를 뽑아와라
			m_arr2D_ori[row][col] = _ttoi(strText);	//text to int 해서 저장
		}
	}
	m_arr2D_view = m_arr2D_ori; // 초기 배열 동기화
	AfxMessageBox(_T("데이터가 저장되었습니다."),(MB_OK|MB_ICONINFORMATION));
}

// ======Horizon 버튼 클릭할 때======
void CMFCGRIDDlg::OnBnClickedHoriz()
{
	if (m_arr2D_ori.empty()) {
		AfxMessageBox(_T("배열을 저장하세요."), (MB_OK | MB_ICONEXCLAMATION)); 
		return; 
	}

	int H = (int)m_arr2D_ori.size();
	int W = (int)m_arr2D_ori[0].size();
	std::vector<std::vector<int>> temp(H, std::vector<int>(W, 0));	//임시 배열을 생성

	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			temp[row][col] = m_arr2D_ori[H - 1 - row][col];	//배열의 행을 거꾸로 만들기
		}
	}

	m_arr2D_ori = temp;	//임시 배열을 본 배열에 넣기
	ApplyThresholdLogic(m_sldThreshold.GetPos()); // 현재 슬라이더 값에 맞춰 그리드 갱신
}

// ======Vertical 버튼 클릭할 때======
void CMFCGRIDDlg::OnBnClickedVerti()
{
	if (m_arr2D_ori.empty()) {
		AfxMessageBox(_T("배열을 저장하세요."), (MB_OK | MB_ICONEXCLAMATION)); 
		return; 
	}

	int H = (int)m_arr2D_ori.size();
	int W = (int)m_arr2D_ori[0].size();
	std::vector<std::vector<int>> temp(H, std::vector<int>(W, 0));	//가로 칸이 W개고 모두 0으로 채워 만들어라

	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			temp[row][col] = m_arr2D_ori[row][W - 1 - col]; // 배열의 열을 거꾸로 만들기
		}
	}

	m_arr2D_ori = temp;	
	ApplyThresholdLogic(m_sldThreshold.GetPos());
}

// ======Flip(+90°) 버튼 누를 때======
void CMFCGRIDDlg::OnBnClickedFlip()
{
	if (m_arr2D_ori.empty()) {
		AfxMessageBox(_T("배열을 저장하세요."), (MB_OK | MB_ICONEXCLAMATION)); 
		return; 
	}

	int H = (int)m_arr2D_ori.size();
	int W = (int)m_arr2D_ori[0].size();
	std::vector<std::vector<int>> temp(W, std::vector<int>(H, 0));

	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			temp[col][H - 1 - row] = m_arr2D_ori[row][col];
		}
	}

	m_arr2D_ori = temp;
	ResizeGrid(W, H); // 가로세로 크기 교체
	SetDlgItemInt(IDC_HEIGHT, W);
	SetDlgItemInt(IDC_WIDTH, H); // UI상 숫자 동기화
	ApplyThresholdLogic(m_sldThreshold.GetPos());	//데이터와 UI 동기화(화면 갱신)
}

// ======Flip(-90°) 버튼 누를 때======
void CMFCGRIDDlg::OnBnClickedFlipCcw()
{
	if (m_arr2D_ori.empty()) { 
		AfxMessageBox(_T("배열을 저장하세요."), (MB_OK | MB_ICONEXCLAMATION)); 
		return; 
	}

	int H = (int)m_arr2D_ori.size();
	int W = (int)m_arr2D_ori[0].size();
	std::vector<std::vector<int>> temp(W, std::vector<int>(H, 0));

	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			temp[W - 1 - col][row] = m_arr2D_ori[row][col]; 
		}
	}

	m_arr2D_ori = temp;
	ResizeGrid(W, H);
	SetDlgItemInt(IDC_HEIGHT, W);
	SetDlgItemInt(IDC_WIDTH, H);
	ApplyThresholdLogic(m_sldThreshold.GetPos());
}

// ======슬라이더 조작 시======
void CMFCGRIDDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar*)&m_sldThreshold) {
		ApplyThresholdLogic(m_sldThreshold.GetPos());
	}
	else {
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

// ======임계값 버튼 클릭 시======
void CMFCGRIDDlg::OnBnClickedSetThre()
{
	int nThrSet = GetDlgItemInt(IDC_THRESHOLD);
	if (nThrSet > 255) {
		AfxMessageBox(_T("최대는 255 입니다."));
		nThrSet = 255; 
	}

	m_sldThreshold.SetPos(nThrSet);
	ApplyThresholdLogic(nThrSet);
}

// ======그리드 UI 크기 동기화======
void CMFCGRIDDlg::ResizeGrid(int nRows, int nCols)
{
	m_ctrlGrid.MoveWindow(0, 0, nCols * 45 + 4, nRows * 45 + 4);
	m_ctrlGrid.SetRowCount(nRows);
	m_ctrlGrid.SetColumnCount(nCols);
	for (int col = 0; col < nCols; col++) {
		m_ctrlGrid.SetColumnWidth(col, 45);
	}
	for (int row = 0; row < nRows; row++) {
		m_ctrlGrid.SetRowHeight(row, 45);
	}
}

// ======임계값 처리 및 화면 갱신======
void CMFCGRIDDlg::ApplyThresholdLogic(int nThr)
{
	if (m_arr2D_ori.empty()) return;

	int H = (int)m_arr2D_ori.size();
	int W = (int)m_arr2D_ori[0].size();

	m_arr2D_view.assign(H, std::vector<int>(W, 0));
	m_ctrlGrid.SetRedraw(FALSE); // 깜빡임 방지래요

	for (int row = 0; row < H; row++) {
		for (int col = 0; col < W; col++) {
			// 원본(ori)은 유지 작업용(m_arr2D)만 0으로 변환
			if (m_arr2D_ori[row][col] <= nThr) {
				m_arr2D_view[row][col] = 0;
			}
			else {
				m_arr2D_view[row][col] = m_arr2D_ori[row][col];
			}
			m_ctrlGrid.SetItemTextFmt(row, col, _T("%d"), m_arr2D_view[row][col]);
		}
	}

	m_nThreshold.Format(_T("%d"), nThr);
	UpdateData(FALSE);
	m_ctrlGrid.SetRedraw(TRUE);
	m_ctrlGrid.Invalidate();
}