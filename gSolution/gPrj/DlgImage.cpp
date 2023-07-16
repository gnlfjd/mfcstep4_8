// DlgImage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "gPrj.h"
#include "DlgImage.h"
#include "afxdialogex.h"


// CDlgImage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGIMAGE, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_UP_PARENT, &CDlgImage::OnBnClickedBtnUpParent)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage �޽��� ó�����Դϴ�.

#include "gPrjDlg.h"
void CDlgImage::OnBnClickedBtnUpParent()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	static int n = 100;
	CgPrjDlg *pDlg = (CgPrjDlg*)m_pParent;
	pDlg->callFunc(n++);
}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("Origin Image"));
	MoveWindow(0, 0, 640, 480);
	InitImage();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDlgImage::InitImage()
{
	//int nWidth = 4096 * 8;
	//int nHeight = 4096 * 8;
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth*nHeight);
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	if (m_image)
		m_image.Draw(dc, 0, 0);

	
	//drawData(&dc);
	drawCrossAndLine(&dc, m_Cx, m_Cy, m_RSize);
}

void CDlgImage::drawData(CDC* pDC)
{
	CRect rect;
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, COLOR_RED);
	CPen* pOldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < m_nDataCount; i++) {
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(2, 2);
		pDC->Ellipse(rect);
	}

	pDC->SelectObject(pOldPen);
}

void CDlgImage::SetCData(int x, int y, int RSize)
{
	m_x = x;
	m_y = y;
	m_RSize = RSize;
}

void CDlgImage::GetdrawCircle()
{
	drawCircle(m_x, m_y, m_RSize);
}


void CDlgImage::drawCircle(int x, int y, int nRadius)
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nPitch = m_image.GetPitch();

	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;

	for (int j = y; j < y + nRadius * 2; j++)
	{
		for (int i = x; i < x + nRadius * 2; i++)
		{
			if(isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = rand() % 0xff;
		}
	}

}

bool CDlgImage::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;
	
	if (dDist < nRadius * nRadius)
	{
		bRet = true;
	}

	return bRet;
}

void CDlgImage::SetCenterData(int x, int y)
{
	m_Cx = x;
	m_Cy = y;
}

void CDlgImage::drawCrossAndLine(CDC* pDC, int Centerx, int Centery, int nRadius)
{
	CRect rect;
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, COLOR_YELLOW);
	CPen* pOldPen = pDC->SelectObject(&pen);

	rect.SetRect(Centerx, Centery, Centerx, Centery);
	rect.InflateRect(nRadius, nRadius);
	pDC->Ellipse(rect);

	pen.DeleteObject();      
	pen.CreatePen(PS_SOLID, 2, COLOR_RED);
	pDC->SelectObject(&pen);

	pDC->MoveTo(Centerx - nRadius / 3, Centery);
	pDC->LineTo(Centerx + nRadius / 3, Centery);

	pDC->MoveTo(Centerx, Centery - nRadius / 3);
	pDC->LineTo(Centerx, Centery + nRadius / 3);

	pDC->SelectObject(pOldPen);
}
