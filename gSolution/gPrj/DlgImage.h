#pragma once

#define MAX_POINT	1000
// CDlgImage ��ȭ �����Դϴ�.

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgImage();

	CWnd* m_pParent;
	CImage m_image;
	int m_nDataCount = 0;
	CPoint m_ptData[MAX_POINT];
	int m_x = 0;
	int m_y = 0;
	int m_RSize = 0;
	int m_Cx = 0;
	int m_Cy = 0;
	void SetCData(int x, int y, int RSize);
	void SetCenterData(int x, int y);
	void GetdrawCircle();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGIMAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnUpParent();
	virtual BOOL OnInitDialog();

private:
	void InitImage();
	void drawData(CDC* pDC);
	void drawCircle(int x, int y, int nRadius);
	void drawCrossAndLine(CDC* pDC, int x, int y, int nRadius);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);

public:
	afx_msg void OnPaint();
};
