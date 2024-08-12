
// DrawCircleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DrawCircle.h"
#include "DrawCircleDlg.h"
#include "afxdialogex.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string.h>
#include <string>
#include <vector>

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


// CDrawCircleDlg 대화 상자



CDrawCircleDlg::CDrawCircleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAWCIRCLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawCircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawCircleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_DRAW, &CDrawCircleDlg::OnBnClickedDraw)
	ON_BN_CLICKED(IDC_GETIMG, &CDrawCircleDlg::OnBnClickedGetimg)
	ON_BN_CLICKED(IDC_ACTION, &CDrawCircleDlg::OnBnClickedAction)
END_MESSAGE_MAP()


// CDrawCircleDlg 메시지 처리기

BOOL CDrawCircleDlg::OnInitDialog()
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

void CDrawCircleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDrawCircleDlg::OnPaint()
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
HCURSOR CDrawCircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CDrawCircleDlg::Radius()
{
	using namespace cv;
	srand(time(NULL));

	int radius = rand() % 150;
	int startx = 0;
	int starty = 0;
	CString csx1, csy1;
	GetDlgItemText(IDC_X1, csx1);
	GetDlgItemText(IDC_Y1, csy1);

	startx = _ttoi(csx1);
	starty = _ttoi(csy1);

	std::string sx1, sy1;
	sx1 = std::string(CT2CA(csx1));
	sy1 = std::string(CT2CA(csy1));

	std::string filepath = "./images/";
	int nWidth = 640;
	int nHieght = 480;
	double x1 = radius;
	double y1 = radius;

	Mat image(nHieght, nWidth, CV_8UC3, Scalar(0, 0, 0));

	x1 = x1 + (double)startx;
	y1 = y1 + (double)starty;
	circle(image, Point(x1, y1), radius, Scalar(255, 255, 255/*색깔*/), -1/*음수면 안에 채움*/);
	imshow("image", image);
	std::string fnx = std::to_string(x1);
	std::string fny = std::to_string(y1);
	std::string filename = filepath + fnx + ", " + fny + ".png";
	imwrite(filename, image);
	waitKey(0);
	destroyAllWindows;

	return radius;
}

void CDrawCircleDlg::OnBnClickedDraw()
{
	int radius = Radius();
}


void CDrawCircleDlg::OnBnClickedGetimg()
{
	using namespace cv;

	TCHAR path[256];
	GetModuleFileName(NULL, path, 256);
	CString str = _T("png files(*.png)|*.*|"); // 모든 파일 표시
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		std::string imgpath = std::string(CT2CA(strPathName));
		Mat img = imread(imgpath,IMREAD_GRAYSCALE);
		medianBlur(img, img, 5);

		Mat color_img;
		cvtColor(img, color_img, COLOR_GRAY2BGR);
		std::vector<Vec3f> circles;

		HoughCircles(img, circles,HOUGH_GRADIENT,1,30,100,20,1,150);
		double radius;
		for (size_t i = 0;i < circles.size();i++)
		{
			Vec3i c = circles[i];
			Point center(c[0], c[1]);
			radius = c[2];
			int font = FONT_ITALIC;
			std::string sradius = std::to_string(radius);
			circle(color_img, center, radius, Scalar(0, 255, 0), 2);
			putText(color_img, "X", center,font ,0.3, Scalar(0,0,0),1);
			putText(color_img, sradius, center, font, 0.5, Scalar(255, 0, 0), 2);
		}
		imshow("circle", color_img);
		waitKey(0);
		destroyAllWindows();
	}

}


void CDrawCircleDlg::OnBnClickedAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	using namespace cv;
	srand(time(NULL));

	int radius = Radius();
	int count = (rand() % 10)+1;
	int startx = 0;
	int starty = 0;
	int finishx = 0;
	int finishy = 0;
	//Text 가져오기
	CString csx1, csy1, csx2, csy2;
	GetDlgItemText(IDC_X1, csx1);
	GetDlgItemText(IDC_Y1, csy1);
	GetDlgItemText(IDC_X2, csx2);
	GetDlgItemText(IDC_Y2, csy2);
	//int로 변환
	startx = _ttoi(csx1);
	starty = _ttoi(csy1);
	finishx = _ttoi(csx2);
	finishy = _ttoi(csy2);

	int fixx = finishx - startx;//-와 -가 만나면 +
	int fixy = finishy - starty;

	double cfixx = (double)fixx / (double)count;
	double cfixy = (double)fixy / (double)count;
	std::string sx1, sy1, sx2, sy2;
	sx1 = std::string(CT2CA(csx1));
	sy1 = std::string(CT2CA(csy1));
	sx2 = std::string(CT2CA(csx2));
	sy2 = std::string(CT2CA(csy2));
	std::string filepath = "./images/";

	int nWidth = 640;
	int nHieght = 480;
	double x1 = startx+ radius;
	double y1 = starty+ radius;
	Mat image(nHieght, nWidth, CV_8UC3, Scalar(0, 0, 0));
	if(finishx<=480-radius &&finishy<=640-radius)
	{
		for (int i = 0; i < count-1; i++)
		{
			Mat image(nHieght, nWidth, CV_8UC3, Scalar(0, 0, 0));
			x1 = x1 + cfixx;
			y1 = y1 + cfixy;
			circle(image, Point(x1, y1), radius, Scalar(255, 255, 255/*색깔*/), -1/*음수면 안에 채움*/);
			imshow("image", image);
			std::string fnx = std::to_string(x1);
			std::string fny = std::to_string(y1);
			std::string filename = filepath + fnx + ", " + fny + ".png";
			imwrite(filename, image);
			waitKey(count);
			Sleep(300);
			destroyAllWindows();
		}
	}
}
