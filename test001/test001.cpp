// test001.cpp : �w�q���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "test001.h"

#define MAX_LOADSTRING 100

// �����ܼ�:
HINSTANCE hInst;								// �ثe�������
TCHAR szTitle[MAX_LOADSTRING];					// ���D�C��r
TCHAR szWindowClass[MAX_LOADSTRING];			// �D�������O�W��

// �o�ӵ{���X�Ҳդ��ҥ]�t���禡���V�e�ŧi:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �b���m�J�{���X�C
	MSG msg;
	HACCEL hAccelTable;

	// ��l�ƥ���r��
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEST001, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �������ε{����l�]�w:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST001));

	// �D�T���j��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �禡: MyRegisterClass()
//
//  �γ~: ���U�������O�C
//
//  ����:
//
//    �u����z�Ʊ榹�{���X��ۮe�� Windows 95 �� 
//    'RegisterClassEx' �禡�󦭪� Win32 �t�ήɡA
//    �~�|�ݭn�[�J�Ψϥγo�Ө禡�C
//    �z�����I�s�o�Ө禡�A�����ε{�����o�P�������� 
//    �u�榡���T�v���ϥܡC
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST001));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST001);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �禡: InitInstance(HINSTANCE, int)
//
//   �γ~: �x�s������鱱��N�X�åB�إߥD����
//
//   ����:
//
//        �b�o�Ө禡���A�ڭ̷|�N������鱱��N�X�x�s�b�����ܼƤ��A
//        �åB�إߩM��ܥD�{�������C
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �N������鱱��N�X�x�s�b�����ܼƤ�

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �禡: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �γ~:  �B�z�D�������T���C
//
//  WM_COMMAND	- �B�z���ε{���\���
//  WM_PAINT	- ø�s�D����
//  WM_DESTROY	- ��ܵ����T���M���^
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ��R�\���������:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �b���[�J����ø�ϵ{���X...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// [����] ������T���B�z�`���C
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
