
#ifndef INGAME_SCENE_H
#define INGAME_SCENE_H

// 継承する、基底クラスのヘッダー
#include "SceneBase.h"
// 定義ヘッダー
#include "../Definition.h"

// インゲームシーンクラス
class InGameScene : public SceneBase
{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Exec();	// 処理を行う
	virtual void Draw();	// 描画を行う

	virtual bool IsEnd() const;	// シーンが終了したかどうかを返す

private:
	// 開始ジングル待ち
	void step_StartJingle();
	// 入力待ち
	void step_Input();
	// クリアジングル待ち
	void step_ClearJingle();

// 倉庫番に関係する関数群
private:
	// ゲームのクリア判定
	bool IsClear() const;
	// 初期状態にリセット
	void Reset();
	// 移動処理
	void Move( DirType dir_ );

private:
	int m_StageData[STAGE_HEIGHT][STAGE_WIDTH];
	int m_PlayerX;	// 配列上のX
	int m_PlayerY;	// 配列上のy

	int Direction;  // プレイヤー:向き
	int Animation;  // プレイヤー:アニメーション

	bool Clear;		//デバッグ用のクリア判定

	int  Moved;
};

#endif // #ifndef INGAME_SCENE_H
