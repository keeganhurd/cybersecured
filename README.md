# Cybersecured

This repository contains a very small example of a native Windows application
written in C++ using the Win32 API. The goal is to provide an interface for
scanning HP printer drivers, cleaning temporary files/registry entries, and
offering basic security awareness links. The code is intentionally minimal and
only implements placeholder functionality.

## Building on Windows

1. Open the folder in **Visual Studio 2022**.
2. Create a new **Win32 Project** and add the files from the `src` directory.
3. Enable Unicode and set the subsystem to Windows (`/SUBSYSTEM:WINDOWS`).
4. Build either x86 or x64. The code is designed to run on Windows 7 and later.

The application has one main window with three buttons:

- **Scan Drivers** – placeholder for HP driver update logic.
- **Clean System** – opens a dialog that simulates a multi-phase cleanup.
- **Get Help** – opens a telephone link.

At the bottom of the window a clickable link opens the Google phishing quiz to
help users learn about scams.

Feel free to extend the driver and cleanup logic using the Windows SetupDi APIs
and registry/file APIs.
