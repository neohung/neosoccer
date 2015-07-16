#include <stdio.h>
#include <stdlib.h>
//
#include <windows.h>
#include <WindowsX.h>
#include <string>
//For srand()
#include <time.h>
//
#include "worldtimer.h"
#include "neogdi.h"
//################################################################
//0)標頭檔<必要>
#include "SoccerPitch.h"
//################################################################

//-----------------
#define IDR_MENU1                       101
//-----------------
const int constWindowWidth  = 700;
const int constWindowHeight = 400;
//-----------------
LPCTSTR g_szApplicationName = TEXT("Win32 Test application 名字");
LPCTSTR g_szWindowClassName = TEXT("Win32 Test application 類別");
//################################################################
//1)宣告Global全域變數<必要>
//World* g_GameWorld;
SoccerPitch* g_GameWorld;
//################################################################
LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam)
{
  //these hold the dimensions of the client window area
  static int cxClient, cyClient; 
  //used to create the back buffer
  static HDC   hdcBackBuffer;
  static HBITMAP hBitmap;
  static HBITMAP hOldBitmap;
  switch (msg)
  {
  case WM_CREATE:
  {
         RECT rect;
         GetClientRect(hwnd, &rect);
         cxClient = rect.right;
         cyClient = rect.bottom;
         //seed random number generator
         srand((unsigned) time(NULL));  
         //建立暫存的DC:　hdcBackBuffer
         hdcBackBuffer = CreateCompatibleDC(NULL);
         //get the DC for the front buffer
         //得到DC和front buffer: hBitmap
         HDC hdc = GetDC(hwnd);
         hBitmap = CreateCompatibleBitmap(hdc,
                                          cxClient,
                                          cyClient);
         //select the bitmap into the memory device context
         //將hBitmap指到暫存的DC
         hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);
         //don't forget to release the DC
         ReleaseDC(hwnd, hdc); 
         //################################################################
         //2)初始化世界<必要>
         //g_GameWorld = new World(cxClient, cyClient);
         g_GameWorld = new SoccerPitch(cxClient, cyClient);
        //################################################################

  }
  break;
  case WM_COMMAND:
  {
    //g_GameWorld->HandleMenuItems(wParam, hwnd); 
  }
  break;
  case WM_LBUTTONUP:
  {
    //################################################################
    //3)定義滑鼠左鍵事件
    //g_GameWorld->SetCrosshair(MAKEPOINTS(lParam));
    //################################################################
  }
  break;
  case WM_RBUTTONUP:
  {    
    //################################################################
    //4)定義滑鼠右鍵事件
    //g_GameWorld->SetSelected(MAKEPOINTS(lParam));
    //################################################################
  }
  break;
  case WM_KEYUP:
  {
    switch(wParam)
    {
      case VK_ESCAPE:
      { 
        //
        wprintf(L"%s",L"按下ESC\n");            
        SendMessage(hwnd, WM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);
      }
      break;
      case 'R':
      {
        wprintf(L"%s",L"按下RESET\n"); 
        //################################################################
        //5)定義重置事件
        //delete g_GameWorld;
        //g_GameWorld = new World(cxClient, cyClient);
        //################################################################
      }
      break;
    }
    //handle any others
    //################################################################
    //6)定義其他按鍵事件
    //g_GameWorld->HandleKeyPresses(wParam); 
    //################################################################
  }
  break;  
  case WM_PAINT:
  {
    PAINTSTRUCT ps;   
    //BeginPaint來取出ps
    BeginPaint (hwnd, &ps);
    //將來源(NULL)的(0,0)位置整個WHITENESS, 也可BLACKNESS
    //填到目標(hdcBackBuffer)的(0,0)-(cxClient,cyClient)中
    BitBlt(hdcBackBuffer,
            0,
            0,
            cxClient,
            cyClient,
            NULL,
            0, //NULL,
            0, //NULL,
            BLACKNESS);
            //WHITENESS);       
    
    ngdi->StartDrawing(hdcBackBuffer); 
    //################################################################
    //7)重繪世界<必要>
    g_GameWorld->Render();
    //################################################################
    ngdi->StopDrawing(hdcBackBuffer);
    //now blit backbuffer to front
    //將來源(hdcBackBuffer)的(0,0)-(cxClient,cyClient)整個圖像資料
    //填到目標(ps.hdc)的(0,0)-(cxClient,cyClient)中 
    BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 
    EndPaint(hwnd, &ps);
  }
  break;   
  case WM_DESTROY:
  {
  //clean up our backbuffer objects
    SelectObject(hdcBackBuffer, hOldBitmap);
    DeleteDC(hdcBackBuffer);
    DeleteObject(hBitmap); 
    // kill the application, this sends a WM_QUIT message  
    PostQuitMessage (0);
    }
    break;
  }
  return DefWindowProc (hwnd, msg, wParam, lParam);
}

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     szCmdLine, 
                    int       iCmdShow)
{
  //為了wprintf中文
  setlocale(LC_CTYPE, "");
  //handle to our window
  HWND            hWnd;    
  //our window class structure
  WNDCLASSEX     winclass;  
  // first fill in the window class stucture
  winclass.cbSize        = sizeof(WNDCLASSEX);
  winclass.style         = CS_HREDRAW | CS_VREDRAW;
  winclass.lpfnWndProc   = WindowProc;
  winclass.cbClsExtra    = 0;
  winclass.cbWndExtra    = 0;
  winclass.hInstance     = hInstance;
  winclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  winclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
  winclass.hbrBackground = NULL;
  winclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
  winclass.lpszClassName = g_szWindowClassName;
  winclass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  //register the window class
  if (!RegisterClassEx(&winclass))
  {
    MessageBox(NULL, TEXT("Registration Failed!"), TEXT("Error"), 0);
    //exit the application
    return 0;
  }
  //create the window and assign its ID to hwnd    
  hWnd = CreateWindowEx (0,                 // extended style
                         g_szWindowClassName,  // window class name,同winclass的lpszClassName
                         g_szApplicationName,  // window caption
                         WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
                         GetSystemMetrics(SM_CXSCREEN)/2 - constWindowWidth/2,
                         GetSystemMetrics(SM_CYSCREEN)/2 - constWindowHeight/2,                    
                         constWindowWidth,     // initial x size
                         constWindowHeight,    // initial y size
                         (HWND)NULL,                 // parent window handle
                         (HMENU)NULL,                 // window menu handle
                         hInstance,            // program instance handle
                         (LPVOID)NULL);                // creation parameters
  //make sure the window creation has gone OK
  if(!hWnd)
  {
    MessageBox(NULL, TEXT("CreateWindowEx Failed!"), TEXT("Error!"), 0);
  }     
  ShowWindow(hWnd, iCmdShow);
  UpdateWindow (hWnd);
  // Enter the message loop
  bool bDone = false;
  WorldTimer timer;
  timer.SmoothUpdatesOn();
  //start the timer
  timer.Start();
  MSG msg;  
  while(!bDone)
  {   
    while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
    {
      if( msg.message == WM_QUIT) 
      {
        //stop loop if it's a quit message
        bDone = true;
      } 
      else 
      {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
      }
    }
    if (msg.message != WM_QUIT )
    {
      //################################################################
      //8)這裡更新Update世界<必要>
      g_GameWorld->Update(timer.TimeElapsed());
      //################################################################
      //render
      RedrawWindow(hWnd,NULL,NULL,RDW_INVALIDATE | RDW_INTERNALPAINT);
      Sleep(2);
    }            
  }//end while
  //delete g_GameWorld;
  UnregisterClass( g_szWindowClassName, winclass.hInstance );
  return msg.wParam;
}

