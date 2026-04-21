
// MFCGRIDDlg.cpp: 구현 파일
//

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
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCGRIDDlg 대화 상자



CMFCGRIDDlg::CMFCGRIDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCGRID_DIALOG, pParent)
	, m_nHeight(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGRIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_ctrlGrid);
	//  DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	//  DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDX_Control(pDX, IDC_WIDTH, m_nWidth);
}

BEGIN_MESSAGE_MAP(CMFCGRIDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE, &CMFCGRIDDlg::OnBnClickedCreate)
	ON_BN_CLICKED(IDC_RANDOM, &CMFCGRIDDlg::OnBnClickedRandom)
	ON_BN_CLICKED(IDC_ADD, &CMFCGRIDDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_HORIZ, &CMFCGRIDDlg::OnBnClickedHoriz)
	ON_BN_CLICKED(IDC_VERTI, &CMFCGRIDDlg::OnBnClickedVerti)
	ON_BN_CLICKED(IDC_FLIP, &CMFCGRIDDlg::OnBnClickedFlip)
END_MESSAGE_MAP()


// CMFCGRIDDlg 메시지 처리기

BOOL CMFCGRIDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCGRIDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCGRIDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//=======만들기 버튼 누를 때======
void CMFCGRIDDlg::OnBnClickedCreate()
{
	UpdateData(TRUE);
	m_ctrlGrid.DeleteAllItems();	//기존 적혀 있던 숫자들 삭제
	m_ctrlGrid.SetEditable(FALSE);
	int nInputHeight = GetDlgItemInt(IDC_HEIGHT);	//해당 에디트 박스에 적힌 int 가져오기
	int nInputWidth = GetDlgItemInt(IDC_WIDTH);		

	if (nInputHeight > 20 || nInputWidth > 20) {
		AfxMessageBox(_T("최대 크기는 20*20 입니다."), (MB_OK | MB_ICONEXCLAMATION));	//메세지 박스 OK 버튼만 아이콘은 세모에 느낌표
		if (IDOK) {
			return;
		}
	}
	int nx = nInputWidth * 40+4;
	int ny = nInputHeight * 40+4;
	m_ctrlGrid.MoveWindow(0, 0, nx,ny);
	m_ctrlGrid.SetRowCount(nInputHeight);	//행(가로)의 크기 설정
	m_ctrlGrid.SetColumnCount(nInputWidth);	//열(세로)의 크기 설정
	
	for (int col = 0; col < nInputWidth; col++) {	//반복해라 작성한만큼
		m_ctrlGrid.SetColumnWidth(col,40);	//40*40 크기로 행을 갯수만큼 생성
	}
	for (int row=0; row < nInputHeight; row++) {	
		m_ctrlGrid.SetRowHeight(row, 40);
	}

	UpdateData(FALSE);
}

//=======난수 버튼 누를 때======
void CMFCGRIDDlg::OnBnClickedRandom()
{
	UpdateData(TRUE);
	int nInputHeight = GetDlgItemInt(IDC_HEIGHT);
	int nInputWidth = GetDlgItemInt(IDC_WIDTH);
	for (int col = 0; col < nInputWidth; col++) {
		for (int row = 0; row < nInputHeight; row++) {
			int x = rand() % 256;	//랜덤 함수 0~255까지 
			//COLORREF randomGray = RGB(x, x, x);	//흑백으로 변경
			m_ctrlGrid.SetItemTextFmt(row, col, _T("% d"), x);	//랜덤 함수를 칸에 작성하는 것을 행열만큼 반복
			//m_ctrlGrid.SetItemBkColour(row, col, randomGray);		//값을 흑백으로 색상 칠하기
		}
	}
	m_ctrlGrid.Invalidate();	//그리드 화면 새로 고침 필수
	UpdateData(FALSE);
}

//=======더하기 버튼 누를 때======
void CMFCGRIDDlg::OnBnClickedAdd()
{
	int nInputHeight = GetDlgItemInt(IDC_HEIGHT);
	int nInputWidth = GetDlgItemInt(IDC_WIDTH);

	m_arr2D.assign(nInputHeight, std::vector<int>(nInputWidth, 0));
	for (int row = 0; row < nInputHeight; row++) {
		for (int col = 0; col < nInputWidth; col++) {
			CString strText=m_ctrlGrid.GetItemText(row, col);	//텍스트를 뽑아와라
			m_arr2D[row][col] = _ttoi(strText);	//text to int 해서 저장
			TRACE(_T("arr2D[%d][%d]의 값: %d\n"),row,col, m_arr2D[row][col]);	//확인을 위한 것 추후 제거 요망
		}
	}
}

//======horizon 버튼 클릭할 때======
void CMFCGRIDDlg::OnBnClickedHoriz()
{
	UpdateData(TRUE);
	int nInputHeight = GetDlgItemInt(IDC_HEIGHT);
	int nInputWidth = GetDlgItemInt(IDC_WIDTH);
	OnBnClickedAdd();	//배열을 활용해서 하기 위한 배열 형성 코드(중요)

	for (int row = 0; row < nInputHeight; row++) {
		for (int col = 0; col < nInputWidth; col++) {
			int x = m_arr2D[nInputHeight - 1 - row][col];	//배열의 행을 거꾸로 만들기(입력값은 3일 떄 0 1 2로 형성되기에 -1을 해줌)	
			//COLORREF Gray = RGB(x, x, x);	//흑백으로 변경
			m_ctrlGrid.SetItemTextFmt(row, col, _T("% d"), x);	// 작성하는 것을 행열만큼 반복
			//m_ctrlGrid.SetItemBkColour(row, col, Gray);		//값을 흑백으로 색상 칠하기
		}
	}
	m_ctrlGrid.Invalidate();	//그리드 화면 새로 고침 필수
	UpdateData(FALSE);
}

//======Vertical버튼 클릭할 때======
void CMFCGRIDDlg::OnBnClickedVerti()
{
	UpdateData(TRUE);
	int nInputHeight = GetDlgItemInt(IDC_HEIGHT);
	int nInputWidth = GetDlgItemInt(IDC_WIDTH);
	OnBnClickedAdd();//배열을 활용해서 하기 위한 배열 형성 코드(중요)
	for (int row = 0; row < nInputHeight; row++) {
		for (int col = 0; col < nInputWidth; col++) {
			int x = m_arr2D[row][nInputWidth - 1 - col];	//배열의 열을 거꾸로 만들기(입력값은 3일 떄 0 1 2로 형성되기에 -1을 해줌)
			//COLORREF Gray = RGB(x, x, x);	//흑백으로 변경
			m_ctrlGrid.SetItemTextFmt(row, col, _T("% d"), x);	// 작성하는 것을 행열만큼 반복
			//m_ctrlGrid.SetItemBkColour(row, col, Gray);		//값을 흑백으로 색상 칠하기
		}
	}
	m_ctrlGrid.Invalidate();	//그리드 화면 새로 고침 필수
	UpdateData(FALSE);
} 


void CMFCGRIDDlg::OnBnClickedFlip()
{
	UpdateData(TRUE);
	int nInputHeight = GetDlgItemInt(IDC_HEIGHT);
	int nInputWidth = GetDlgItemInt(IDC_WIDTH);
	OnBnClickedAdd();//배열을 활용해서 하기 위한 배열 형성 코드(중요)
	for (int row = 0; row < nInputHeight; row++) {
		for (int col = 0; col < nInputWidth; col++) {
			int x = m_arr2D[col][nInputHeight-1-row];	//배열의 뒤집어 기(입력값은 3일 떄 0 1 2로 형성되기에 -1을 해줌)
			//COLORREF Gray = RGB(x, x, x);	//흑백으로 변경
			m_ctrlGrid.SetItemTextFmt(row, col, _T("% d"), x);	// 작성하는 것을 행열만큼 반복
			//m_ctrlGrid.SetItemBkColour(row, col, Gray);		//값을 흑백으로 색상 칠하기
		}
	}
	m_ctrlGrid.Invalidate();	//그리드 화면 새로 고침 필수
	UpdateData(FALSE);
}
