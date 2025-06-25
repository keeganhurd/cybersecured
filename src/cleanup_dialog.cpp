#include "cleanup_dialog.h"
#include <string>

// IDs for dialog controls
#define ID_PROGRESS 201
#define ID_TEXT     202
#define ID_BUTTON   203

// Simple state machine phases
enum CleanupPhase {
    PhaseScan,
    PhaseResults,
    PhaseCleanup,
    PhaseComplete
};

INT_PTR CALLBACK CleanupDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void ShowCleanupDialog(HWND parent)
{
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(1), parent, CleanupDlgProc);
}

// Template dialog resource using raw dialog box template in memory
// This creates a simple dialog without a resource file.
static DLGTEMPLATE* CreateDialogTemplate()
{
    static WORD tmpl[64];
    DLGTEMPLATE* dlg = (DLGTEMPLATE*)tmpl;
    ZeroMemory(dlg, sizeof(tmpl));
    dlg->style = WS_POPUP | WS_BORDER | WS_CAPTION | WS_SYSMENU | DS_MODALFRAME;
    dlg->cx = 200;
    dlg->cy = 100;
    return dlg;
}

INT_PTR CALLBACK CleanupDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static CleanupPhase phase = PhaseScan;

    switch (message)
    {
    case WM_INITDIALOG:
        SetWindowText(hDlg, L"System Cleanup");
        // Create controls dynamically
        CreateWindow(L"STATIC", L"Scanning...", WS_VISIBLE | WS_CHILD,
            10, 10, 180, 20, hDlg, (HMENU)ID_TEXT, GetModuleHandle(NULL), NULL);
        CreateWindow(PROGRESS_CLASS, NULL, WS_VISIBLE | WS_CHILD,
            10, 40, 180, 20, hDlg, (HMENU)ID_PROGRESS, GetModuleHandle(NULL), NULL);
        CreateWindow(L"BUTTON", L"Cancel", WS_VISIBLE | WS_CHILD,
            60, 70, 80, 20, hDlg, (HMENU)ID_BUTTON, GetModuleHandle(NULL), NULL);
        phase = PhaseScan;
        // Simulate progress using a timer
        SetTimer(hDlg, 1, 1000, NULL);
        return TRUE;
    case WM_TIMER:
        if (phase == PhaseScan)
        {
            SetDlgItemText(hDlg, ID_TEXT, L"10 GB junk files, 5 registry errors");
            SetDlgItemText(hDlg, ID_BUTTON, L"Clean Now");
            phase = PhaseResults;
        }
        else if (phase == PhaseCleanup)
        {
            SetDlgItemText(hDlg, ID_TEXT, L"Cleanup complete! 10 GB freed!");
            SetDlgItemText(hDlg, ID_BUTTON, L"Done");
            phase = PhaseComplete;
        }
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BUTTON)
        {
            if (phase == PhaseResults)
            {
                SetDlgItemText(hDlg, ID_TEXT, L"Cleaning...");
                SetDlgItemText(hDlg, ID_BUTTON, L"Cancel");
                phase = PhaseCleanup;
            }
            else if (phase == PhaseComplete || phase == PhaseScan)
            {
                EndDialog(hDlg, 0);
            }
            else if (phase == PhaseCleanup)
            {
                EndDialog(hDlg, 0);
            }
        }
        return TRUE;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
