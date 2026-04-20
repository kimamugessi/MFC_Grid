#if !defined(AFX_GRIDCELLCHECK2_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_)
#define AFX_GRIDCELLCHECK2_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef NSYS_GRIDCTRLDEF_EXPORTS
#define NSYS_GRIDCTRLDEF_API __declspec(dllexport)
#else
#define NSYS_GRIDCTRLDEF_API __declspec(dllimport)
#endif

#include "GridCellCheck.h"

class CGridCellCheck2 : public CGridCellCheck
{
    friend class CGridCtrl;
    DECLARE_DYNCREATE(CGridCellCheck2)

public:
    CGridCellCheck2();

public:
    virtual BOOL Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
    virtual void EndEdit();

	BOOL Enable(BOOL bEnable = TRUE);
	BOOL GetEnabled();
    virtual void OnClick( CPoint PointCellRelative);

protected:
	//CRect GetCheckPlacement();
    virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

    LRESULT SendMessageToParent(int nRow, int nCol, int nMessage);

protected:
    BOOL  m_bEnabled;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCELLCHECK2_H__ECD42822_16DF_11D1_992F_895E185F9C72__INCLUDED_)
