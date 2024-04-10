
// Legirovanie.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CLegirovanieApp:
// Сведения о реализации этого класса: Legirovanie.cpp
//

class CLegirovanieApp : public CWinApp
{
public:
	CLegirovanieApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CLegirovanieApp theApp;
