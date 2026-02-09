#include <iostream>
#include <windows.h>

// game logic
bool isRunning = true;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    LRESULT ret = 0;
    switch(msg) {
        case WM_CLOSE:
            isRunning = false;
            break;
        default:
            ret = DefWindowProc(hwnd, msg, wp, lp);
            break;
    }

    return ret;
}

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd
)
{
    WNDCLASS wc = {sizeof(WNDCLASS)};
    
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "MyTemplateClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    
    if(!RegisterClass(&wc)) {
        MessageBox(0, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
    }
    
    HWND hwnd = CreateWindowExW(0, L"MyTemplateClass", L"3D renderer", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
                                CW_USEDEFAULT, CW_USEDEFAULT, 800, 800, NULL, NULL, hInst, NULL);
    
    if(!hwnd) return 0;
    
    MSG msg = {};
    while(isRunning) {
        while(PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE) > 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // your game loop or logic goes here.
    }
    return (int)msg.wParam;
}