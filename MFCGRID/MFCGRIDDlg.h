
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
//	CString m_nHeight;
	CEdit m_nWidth;
	afx_msg void OnBnClickedRandom();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedHoriz();
	afx_msg void OnBnClickedVerti();
	afx_msg void OnBnClickedFlip();
	afx_msg void OnBnClickedFlipCcw();

	// MFCGRIDDlg.h 에 추가
private:
	std::vector<std::vector<int>> m_arr2D_view;
	std::vector<std::vector<int>> m_arr2D_ori;
	CString      m_nThreshold;
	CSliderCtrl  m_sldThreshold;

	void ResizeGrid(int nRows, int nCols);
	void FlushToGrid(const std::vector<std::vector<int>>& arr);
	void ApplyRotation(std::vector<std::vector<int>>& newArr, int oriH, int oriW);
	void ApplyThresholdLogic(int nThr);

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedSetThre();
public:
	CEdit m_nHeight;
};
