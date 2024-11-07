#include "framework.h"
#include "Mini-Game-Hub.h"

#define MAX_LOADSTRING 100

// Button IDs
#define ID_BUTTON_MENU 1
#define ID_BUTTON_QUIT 2
#define ID_BUTTON_X 3
#define ID_BUTTON_Y 4
#define ID_BUTTON_Z 5
#define ID_BUTTON_PLAY 6

// Timer ID
#define ID_TIMER_LAUNCH_GAME 101

// Global Variables:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
HWND hButtonMenu, hButtonQuit, hButtonX, hButtonY, hButtonZ, hButtonPlay;
bool isMenuScreen = true;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void switchScreen(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MINIGAMEHUB, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINIGAMEHUB));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIGAMEHUB));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MINIGAMEHUB);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 400, 300, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

void switchScreen(HWND hWnd)
{
    isMenuScreen = !isMenuScreen;

    ShowWindow(hButtonMenu, isMenuScreen ? SW_SHOW : SW_HIDE);
    ShowWindow(hButtonQuit, isMenuScreen ? SW_SHOW : SW_HIDE);

    ShowWindow(hButtonX, !isMenuScreen ? SW_SHOW : SW_HIDE);
    ShowWindow(hButtonY, !isMenuScreen ? SW_SHOW : SW_HIDE);
    ShowWindow(hButtonZ, !isMenuScreen ? SW_SHOW : SW_HIDE);
}

void CreatePlayWindow(HWND hWnd)
{
    hButtonPlay = CreateWindowW(L"BUTTON", L"Play", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        150, 100, 100, 50, hWnd, (HMENU)ID_BUTTON_PLAY, hInst, nullptr);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hButtonMenu = CreateWindowW(L"BUTTON", L"Menu", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            150, 100, 100, 50, hWnd, (HMENU)ID_BUTTON_MENU, hInst, nullptr);

        hButtonQuit = CreateWindowW(L"BUTTON", L"Quit", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            175, 160, 50, 30, hWnd, (HMENU)ID_BUTTON_QUIT, hInst, nullptr);

        hButtonX = CreateWindowW(L"BUTTON", L"Snake", WS_TABSTOP | WS_CHILD | BS_PUSHBUTTON,
            50, 100, 50, 30, hWnd, (HMENU)ID_BUTTON_X, hInst, nullptr);

        hButtonY = CreateWindowW(L"BUTTON", L"Tic Tac Toe", WS_TABSTOP | WS_CHILD | BS_PUSHBUTTON,
            110, 100, 90, 30, hWnd, (HMENU)ID_BUTTON_Y, hInst, nullptr);

        hButtonZ = CreateWindowW(L"BUTTON", L"Number Guessing", WS_TABSTOP | WS_CHILD | BS_PUSHBUTTON,
            210, 100, 130, 30, hWnd, (HMENU)ID_BUTTON_Z, hInst, nullptr);

        ShowWindow(hButtonX, SW_HIDE);
        ShowWindow(hButtonY, SW_HIDE);
        ShowWindow(hButtonZ, SW_HIDE);
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ID_BUTTON_MENU:
            switchScreen(hWnd);
            break;
        case ID_BUTTON_QUIT:
            PostQuitMessage(0);
            break;
        case ID_BUTTON_X:
            MessageBox(hWnd, L"You have chosen the Snake game!\n\n   Your Game Will Start Soon!\n\nClick { ok }", L"Info", MB_OK);
            SetTimer(hWnd, ID_TIMER_LAUNCH_GAME, 3000, NULL); // Start a 3-second timer
            break;

        case ID_BUTTON_Y:
            MessageBox(hWnd, L"You have chosen the Tic Tac Toe Game!\n\n   Your Game Will Start Soon!\n\nClick { ok }", L"Info", MB_OK);
            break;

        case ID_BUTTON_Z:
            MessageBox(hWnd, L"You have chosen the Number Guessing Game!\n\n   Your Game Will Start Soon!\n\nClick { ok }", L"Info", MB_OK);
            break;

        case ID_BUTTON_PLAY:
            MessageBox(hWnd, L"Starting the game!", L"Info", MB_OK);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_TIMER:
        if (wParam == ID_TIMER_LAUNCH_GAME)
        {
            KillTimer(hWnd, ID_TIMER_LAUNCH_GAME); // Stop the timer
            CreatePlayWindow(hWnd); // Create the Play button window
            ShowWindow(hButtonX, SW_HIDE);
            ShowWindow(hButtonY, SW_HIDE);
            ShowWindow(hButtonZ, SW_HIDE);
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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
