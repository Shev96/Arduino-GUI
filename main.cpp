#include <windows.h>
#include <stdlib.h>
#include "CSerialPort.h"





#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3

#define GENERATE_BUTTON 4
#define COMPORT_CONNECT 5


 LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
 HMENU hMenu;
 HWND hName, hRx,hTx, hOut;

 void AddMenus(HWND);
 void AddControls(HWND);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nsmdshow )
{
    //MessageBox(NULL, "HELLP WORLD", "My first program",MB_OK );
    WNDCLASSW wc ={0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL,IDC_HAND);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;


                if (!RegisterClassW(&wc))
                return -1;

      CreateWindowW(L"myWindowClass", L"Arduino GUI", WS_OVERLAPPEDWINDOW| WS_VISIBLE, 100,100, 600, 400, NULL, NULL,NULL, NULL);
            MSG msg  ={0};
            while(GetMessage(&msg, NULL, NULL, NULL))
      {
          TranslateMessage(&msg);
          DispatchMessage (&msg);
      }

    return 0;

}



 LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
        switch (msg)
        {
    case WM_COMMAND:
                switch(wp)
                {
                case FILE_MENU_EXIT:
                    DestroyWindow(hWnd);
                break;

                case FILE_MENU_NEW:
                    MessageBeep(MB_ICONINFORMATION);
                break;


                case FILE_MENU_OPEN:
                 //   DestroyWindow(hWnd);
                break;
                case GENERATE_BUTTON:

                break;

                case COMPORT_CONNECT:
                auto p1= OpenPort(1);
                break;


                }

    break;
    case WM_CREATE:
            AddMenus(hWnd);
            AddControls(hWnd);
    break;

    case WM_DESTROY:
                PostQuitMessage(0);
    break;
        default:
         return  DefWindowProcW(hWnd,msg,wp,lp);

 }
 }


void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu =CreateMenu();

    AppendMenu(hSubMenu,MF_STRING, NULL,"Change title");

    AppendMenu(hFileMenu,MF_STRING, FILE_MENU_NEW,"New");
    AppendMenu(hFileMenu,MF_POPUP,(UINT_PTR)hSubMenu,"Open SubMenu");
    AppendMenu(hFileMenu,MF_SEPARATOR, NULL,NULL);
    AppendMenu(hFileMenu,MF_STRING, FILE_MENU_EXIT,"EXIT");

    AppendMenu(hMenu,MF_POPUP, (UINT_PTR)hFileMenu,"File");
    AppendMenu(hMenu,MF_STRING, NULL,"Help");

    SetMenu(hWnd, hMenu);


}

void AddControls(HWND hWnd)
{
CreateWindowW(L"Button",L"Connect", WS_VISIBLE | WS_CHILD| WS_BORDER| SS_CENTER, 20,40 ,65,55,hWnd,(HMENU)COMPORT_CONNECT, NULL,NULL);


CreateWindowW(L"Static",L"Rx", WS_VISIBLE | WS_CHILD| WS_BORDER| SS_CENTER, 100,50 ,98,48,hWnd,NULL, NULL,NULL);
hRx=CreateWindowW(L"Edit",L"", WS_VISIBLE | WS_CHILD| WS_BORDER| SS_CENTER, 200,50 ,98,48,hWnd,NULL, NULL,NULL);


CreateWindowW(L"Static",L"Tx", WS_VISIBLE | WS_CHILD| WS_BORDER| SS_CENTER, 100,90 ,98,48,hWnd,NULL, NULL,NULL);
hTx=CreateWindowW(L"Edit",L"", WS_VISIBLE | WS_CHILD| WS_BORDER| SS_CENTER, 200,90 ,98,48,hWnd,NULL, NULL,NULL);

CreateWindowW(L"Button",L"Generate", WS_VISIBLE | WS_CHILD| WS_BORDER| SS_CENTER, 300,90 ,98,48,hWnd,(HMENU)GENERATE_BUTTON, NULL,NULL);

hOut= CreateWindowW(L"Edit",L"", WS_VISIBLE | WS_CHILD| WS_BORDER| SS_CENTER, 100,200 ,300,200,hWnd,NULL, NULL,NULL);
}

