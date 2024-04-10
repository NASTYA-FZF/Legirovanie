
// LegirovanieDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Legirovanie.h"
#include "LegirovanieDlg.h"
#include "afxdialogex.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CLegirovanieDlg



CLegirovanieDlg::CLegirovanieDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LEGIROVANIE_DIALOG, pParent)
	, L(2)
	, Nd(1e21)
	, e(12)
	, V(2)
	, delta(1e-8)
	, number_point(500)
	, nd(1e-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLegirovanieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAPH, graphic);
	DDX_Text(pDX, IDC_EDIT1, L);
	DDX_Text(pDX, IDC_EDIT7, Nd);
	DDX_Text(pDX, IDC_EDIT4, e);
	DDX_Text(pDX, IDC_EDIT3, V);
	DDX_Text(pDX, IDC_EDIT5, delta);
	DDX_Text(pDX, IDC_EDIT6, number_point);
	//  DDX_Text(pDX, IDC_EDIT7, Nd);
	DDX_Text(pDX, IDC_EDIT2, nd);
}

BEGIN_MESSAGE_MAP(CLegirovanieDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLegirovanieDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CLegirovanieDlg

BOOL CLegirovanieDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	srand(time(NULL));
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CLegirovanieDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CLegirovanieDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLegirovanieDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();

	graphic.my_func.clear();
	graphic.my_x.clear();
	double step = 0.1;
	examp = my_decision(Nd, V, 0., 0., L * 1e-6, e, nd, delta, number_point);
	vector<double> x, y;
	examp.control(x, y);
	graphic.my_func.push_back(y);
	graphic.my_x.push_back(x);

	graphic.osX = L"x, мкм";
	graphic.osY = L"V, В";
	graphic.nameGraph = L"Распределение потенциала по толщине пластины";
	Invalidate(FALSE);
}
