
// LegirovanieDlg.h: файл заголовка
//

#pragma once
#include "MyGraph.h"
#include "Work.h"

// Диалоговое окно CLegirovanieDlg
class CLegirovanieDlg : public CDialogEx
{
// Создание
public:
	CLegirovanieDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEGIROVANIE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MyGraph graphic;
	afx_msg void OnBnClickedButton1();
	my_decision examp;
	double L;
//	double Nd;
	double e;
	double V;
	double delta;
	int number_point;
	CEdit status;
	double Nd;
	double nd;
};
