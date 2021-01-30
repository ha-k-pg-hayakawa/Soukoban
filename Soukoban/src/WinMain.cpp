#include "DxLib.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"
#include "Manager/InputManager.h"

// プログラムは WinMain から始まります
// 警告C28251を回避するためにWinMainの引数に注釈を追記
// https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=view&no=4947
int WINAPI WinMain(_In_     HINSTANCE hInstance,
				   _In_opt_ HINSTANCE hPrevInstance,
				   _In_     LPSTR lpCmdLine,
				   _In_     int nCmdShow )
{
	// ＤＸライブラリ初期化処理
	SetOutApplicationLogValidFlag(FALSE);	// ログ出力
	ChangeWindowMode(TRUE);					// ウィンドウモード
	SetGraphMode(640, 480, 32);				// 画面モード変更
	SetBackgroundColor(0, 0, 0);		// 背景色
	SetMainWindowText("My倉庫番");			// メニューバーのタイトル
	if( DxLib_Init() == -1 ){ return -1; }

	// 描画先を裏の画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームを始める前の初期化処理
	GameManager::CreateInstance();
	InputManager::CreateInstance();
	SceneManager::CreateInstance();

	// ゲームループ
	while( true )
	{
		// Windowsのメッセージ処理に失敗したか、閉じられたら終了
		if( ProcessMessage() != 0 ){ break; }

		// DxLibのお約束：画面クリア
		ClearDrawScreen();
		clsDx();

		// シングルトンの実体を取得
		InputManager* pInputMng = InputManager::GetInstance();
		SceneManager* pSceneMng = SceneManager::GetInstance();

		// 処理
		pInputMng->Update();
		pSceneMng->Exec();

		// 表示
		pSceneMng->Draw();

		// DxLibのお約束：画面更新
		ScreenFlip();
	}

	// ゲーム終了前の後始末
	// シングルトンに限らず、作った順番と逆順で破棄する
	SceneManager::DestroyInstance();
	InputManager::DestroyInstance();
	GameManager::DestroyInstance();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}