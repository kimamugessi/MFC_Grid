
// MFCGRIDDlg.h: 헤더 파일
//

#pragma once
#include "GridCtrl.h"
#include <vector>

// CMFCGRIDDlg 대화 상자
class CMFCGRIDDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCGRIDDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCGRID_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	// 두 함수에서 모두 쓸 수 있도록 여기에 멤버 변수를 선언합니다.
	std::vector<std::vector<int>> m_arr2D;
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_ctrlGrid;
//	CInt m_nWidth;
//	CInt m_nHeight;
	afx_msg void OnBnClickedCreate();
	CString m_nHeight;
	CEdit m_nWidth;
	afx_msg void OnBnClickedRandom();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedHoriz();
	afx_msg void OnBnClickedVerti();
};
