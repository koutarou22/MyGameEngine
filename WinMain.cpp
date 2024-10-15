//インクルード
#include <Windows.h>
#include <stdlib.h>
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Fbx.h"
#include "Engine/RootJob.h"
#include "PlayScene.h"
#include "Player.h"
#include "Engine/Input.h"
#include"Model.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"d3d11.lib")

using namespace Direct3D;

const wchar_t * WIN_CLASS_NAME = L"SampleGame";
const wchar_t* APP_NAME = L"Error";

RootJob* pRootJob = nullptr;


//const int WINDOW_WIDTH = 800;  //ウィンドウの幅
//const int WINDOW_HEIGHT = 600; //ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
    wc.hInstance = hInstance;                   //インスタンスハンドル
    wc.lpszClassName = WIN_CLASS_NAME;          //ウィンドウクラス名
    wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
    wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
    wc.hIcon = LoadIcon(NULL, IDI_ERROR);       //アイコン
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
    wc.hCursor = LoadCursor(NULL, IDC_WAIT);    //マウスカーソル
    wc.lpszMenuName = NULL;                     //メニュー（なし）
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
    RegisterClassEx(&wc); //クラスを登録

    //ウィンドウサイズの計算(表示領域をWINDOW_WIDTH x WINDOW_HEIGHTに指定するための計算)
    RECT winRect = { 0, 0,  Direct3D::WINDOW_WIDTH, Direct3D::WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     //ウィンドウ幅
    int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ


    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //ウィンドウクラス名
        APP_NAME,     //タイトルバーに表示する内容
        WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
        CW_USEDEFAULT,       //表示位置左（おまかせ）
        CW_USEDEFAULT,       //表示位置上（おまかせ）
        winW,        //ウィンドウ幅
        winH,       //ウィンドウ高さ
        NULL,                //親ウインドウ（なし）
        NULL,                //メニュー（なし）
        hInstance,           //インスタンス
        NULL                 //パラメータ（なし）
    );

    ShowWindow(hWnd, nCmdShow);

    //Direct3D初期化
   HRESULT hr =  Direct3D::Initialize(winW, winH, hWnd);
   Camera::Initialize();



   pRootJob = new RootJob;
   pRootJob->Initialize();
   FBX fbx;

   //Player* player;
   //GreenBox.fbx

   // if (FAILED(hr))
   // {
   //     MessageBox(NULL, L"Direct3Dの初期化に失敗しました", L"Error", NULL);
   //     return hr;
   // }

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //メッセージあり
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //メッセージなし
        else
        {
           /* Input::Update();*/
            //カメラを更新
            Camera::Update();

            //入力の処理
          
            pRootJob->UpdateSub();

            //▼描画
            Direct3D::BeginDraw();
      
            //ルートジョブから、すべてのオブジェクトのドローを呼ぶ
            pRootJob->DrawSub();
            FBX* fbx;
            Direct3D::EndDraw();
        }
    }
    Model::Release();
    pRootJob->Release();
    Direct3D::Release();

	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:

        PostQuitMessage(0);  //プログラム終了
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}