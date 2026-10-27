#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>

#include <string>

#include "counter.h"

namespace {

constexpr int kButtonId = 1001;
constexpr wchar_t kClassName[] = L"CounterAppWindow";

Counter g_counter;
HWND g_label = nullptr;

void UpdateLabel() {
    const std::wstring text = L"Count: " + std::to_wstring(g_counter.Value());
    SetWindowTextW(g_label, text.c_str());
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        HINSTANCE inst = reinterpret_cast<LPCREATESTRUCTW>(lParam)->hInstance;
        g_label = CreateWindowExW(0, L"STATIC", L"Count: 0",
                                  WS_CHILD | WS_VISIBLE | SS_CENTER,
                                  20, 20, 240, 24, hwnd, nullptr, inst, nullptr);
        CreateWindowExW(0, L"BUTTON", L"Click me",
                        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                        80, 60, 120, 32, hwnd,
                        reinterpret_cast<HMENU>(static_cast<INT_PTR>(kButtonId)),
                        inst, nullptr);
        return 0;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == kButtonId && HIWORD(wParam) == BN_CLICKED) {
            g_counter.Increment();
            UpdateLabel();
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

} // namespace

int WINAPI wWinMain(HINSTANCE inst, HINSTANCE, PWSTR, int showCmd) {
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = inst;
    wc.lpszClassName = kClassName;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    RegisterClassW(&wc);

    RECT rect = {0, 0, 280, 120};
    const DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    AdjustWindowRect(&rect, style, FALSE);

    HWND hwnd = CreateWindowExW(0, kClassName, L"Click Counter", style,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                rect.right - rect.left, rect.bottom - rect.top,
                                nullptr, nullptr, inst, nullptr);
    if (!hwnd) {
        return 1;
    }
    ShowWindow(hwnd, showCmd);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return static_cast<int>(msg.wParam);
}
