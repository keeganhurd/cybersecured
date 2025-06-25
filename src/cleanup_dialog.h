#pragma once
#include <windows.h>

// Shows the multi-phase cleanup dialog. This function blocks until the
// dialog is closed.
void ShowCleanupDialog(HWND parent);
