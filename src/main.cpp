#include <windows.h>
#include <shellapi.h>
#include "cleanup_dialog.h"
#include "driver_updater.h"

// Global variables for window and buttons
HINSTANCE g_hInst;
HWND g_hMainWnd;

// Control IDs
#define ID_BTN_SCAN_DRIVERS 101
#define ID_BTN_CLEAN_SYSTEM 102
#define ID_BTN_GET_HELP     103
#define ID_LINK_PHISHING    104

// Forward declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OpenPhishingQuiz();
void StartSupportCall();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    g_hInst = hInstance;

    // Register window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"CybersecuredMainWnd";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc))
        return FALSE;

    // Create main window
    g_hMainWnd = CreateWindow(wc.lpszClassName, L"Cybersecured",
                              WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                              CW_USEDEFAULT, 0, 400, 300, NULL, NULL, hInstance, NULL);
    if (!g_hMainWnd)
        return FALSE;

    ShowWindow(g_hMainWnd, nCmdShow);
    UpdateWindow(g_hMainWnd);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

void CreateMainControls(HWND hwnd)
{
    // Create buttons with large fonts
    HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

    HWND hBtnDrivers = CreateWindow(L"BUTTON", L"Scan Drivers",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 50, 300, 40, hwnd, (HMENU)ID_BTN_SCAN_DRIVERS, g_hInst, NULL);
    SendMessage(hBtnDrivers, WM_SETFONT, (WPARAM)hFont, TRUE);

    HWND hBtnClean = CreateWindow(L"BUTTON", L"Clean System",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 100, 300, 40, hwnd, (HMENU)ID_BTN_CLEAN_SYSTEM, g_hInst, NULL);
    SendMessage(hBtnClean, WM_SETFONT, (WPARAM)hFont, TRUE);

    HWND hBtnHelp = CreateWindow(L"BUTTON", L"Get Help",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 150, 300, 40, hwnd, (HMENU)ID_BTN_GET_HELP, g_hInst, NULL);
    SendMessage(hBtnHelp, WM_SETFONT, (WPARAM)hFont, TRUE);

    HWND hLink = CreateWindow(L"STATIC", L"Protect Yourself – Free Quiz!",
        WS_VISIBLE | WS_CHILD | SS_NOTIFY,
        50, 210, 300, 20, hwnd, (HMENU)ID_LINK_PHISHING, g_hInst, NULL);
    SendMessage(hLink, WM_SETFONT, (WPARAM)hFont, TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateMainControls(hwnd);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_BTN_SCAN_DRIVERS:
            ScanAndUpdateDrivers(hwnd);
            break;
        case ID_BTN_CLEAN_SYSTEM:
            ShowCleanupDialog(hwnd);
            break;
        case ID_BTN_GET_HELP:
            StartSupportCall();
            break;
        case ID_LINK_PHISHING:
            OpenPhishingQuiz();
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void OpenPhishingQuiz()
{
    ShellExecute(NULL, L"open", L"https://phishingquiz.withgoogle.com/", NULL, NULL, SW_SHOWNORMAL);
}

void StartSupportCall()
{
    ShellExecute(NULL, L"open", L"tel:8552020211", NULL, NULL, SW_SHOWNORMAL);
}

