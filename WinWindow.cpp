#include <windows.h>
#include <stdio.h>

HANDLE g_hOutPut = 0;//接受标准输出句柄
void OnCreate(HWND hWnd, LPARAM lParam)
{
	CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
	char* pszText = (char*)pcs->lpCreateParams;
	MessageBox(NULL, pszText, "Info", MB_OK|MB_ICONINFORMATION);

	CreateWindowEx(NULL, "EDIT", "EDITWINDOW", WS_CHILD|WS_VISIBLE|WS_BORDER, 0, 0, 200, 200, hWnd, NULL, NULL, NULL);
}

void OnSize(HWND hWnd, LPARAM lParam)
{
	short nWidth = LOWORD(lParam);
	short nHight = HIWORD(lParam);
	char szText[256]={0};
	system("213");
	sprintf(szText, "WMSIZE: 宽: %d, 高:%d\n", nWidth, nHight);
	WriteConsole(g_hOutPut, szText, strlen(szText), NULL, NULL);
}

//窗口处理函数(自定义，处理消息)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch(msgID){
	case WM_SIZE:
		OnSize(hWnd, lParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd, lParam);
		break;
	case WM_SYSCOMMAND:
		//MessageBox(hWnd, "WM_SYSCOMMAND", "Info", MB_OK|MB_ICONINFORMATION);
		if(wParam == SC_CLOSE)
		{
			int nRet = MessageBox(hWnd, "是否退出？", "警告", MB_YESNO|MB_ICONWARNING);
			if(nRet == IDYES)
			{
				//空
			}
			else
			{
				return 0;
			}
		}
		break;
	case WM_DESTROY:
		MessageBox(NULL, "WM_DESTROY", "Info", MB_OK|MB_ICONINFORMATION);
		PostQuitMessage(0);//可以使GetMessage函数返回0
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);//给各种消息默认处理
}

//入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();//增加DOS窗口
	g_hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);

	//注册窗口类
	WNDCLASS wc = {0};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;/**                                 **/
	wc.lpfnWndProc = WndProc;/**      **/
	wc.lpszClassName = "MainProgram";/**                                **/
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	RegisterClass(&wc);		//将以上所有赋值全部写入操作系统

	//在内存中创建窗口
	char* pszText = "114514 1919810";
	HWND hWnd = CreateWindowEx(0, "MainProgram", "ProgramTest", WS_OVERLAPPEDWINDOW,
								100, 100, 500, 500, NULL, NULL, hIns, pszText);

	//注册窗口类
	/**
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;////////////////////////////
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = "ChildWnd";/////////////////////
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	RegisterClass(&wc);		//将以上所有赋值全部写入操作系统
	**/

	//创建子窗口
	//HWND hChild1 = CreateWindowEx(0, "ChildWnd", "c1", WS_CHILD|WS_VISIBLE|WS_OVERLAPPEDWINDOW,
	//								0, 0, 200, 200, hWnd, NULL, hIns, NULL);

	//HWND hChild2 = CreateWindowEx(0, "ChildWnd", "c2", WS_CHILD|WS_VISIBLE|WS_OVERLAPPEDWINDOW,
	//								200, 0, 200, 200, hWnd, NULL, hIns, NULL);
	
	//显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//消息循环
	MSG nMsg = {0};
	while(GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);		//将消息交给处理窗口处理函数来处理
	}
	return 0;
}