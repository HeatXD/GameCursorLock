#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class GameCursorLocker {
public:
    GameCursorLocker(const std::wstring& windowTitle, int lockX, int lockY)
        : title(windowTitle), requestedX(lockX), requestedY(lockY), hwnd(NULL) {
    }

    void Run() {
        hwnd = FindWindowW(NULL, title.c_str());
        if (!hwnd) {
            std::wcerr << L"Window not found: " << title << std::endl;
            return;
        }
        else {
            std::wcerr << L"Window found!: " << title << std::endl;
        }

        while (true) {
            if (GetForegroundWindow() == hwnd) {
                ConfineCursor();
            }
            else {
                ClipCursor(NULL);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

private:
    std::wstring title;
    int requestedX, requestedY;
    HWND hwnd;

    void ConfineCursor() {
        RECT clientRect;
        if (!GetClientRect(hwnd, &clientRect)) return;

        int maxX = clientRect.right - 1;
        int maxY = clientRect.bottom - 1;

        int clampedX = requestedX;
        int clampedY = requestedY;

        // Clamp X position
        if (clampedX < 0) clampedX = 0;
        if (clampedX > maxX) clampedX = maxX;

        // Clamp Y position
        if (clampedY < 0) clampedY = 0;
        if (clampedY > maxY) clampedY = maxY;

        POINT pt = { clampedX, clampedY };
        if (!ClientToScreen(hwnd, &pt)) return;

        RECT lockRect = { pt.x, pt.y, pt.x + 1, pt.y + 1 };
        ClipCursor(&lockRect);
    }
};

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 4) {
        std::wcout << L"Usage: <WindowTitle> <X> <Y>" << std::endl;
        return 1;
    }

    std::wstring title = argv[1];
    int x = std::stoi(argv[2]);
    int y = std::stoi(argv[3]);

    GameCursorLocker locker(title, x, y);
    locker.Run();

    return 0;
}
