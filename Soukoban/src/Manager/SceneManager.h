
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Definition.h"

// シーン管理クラス
class SceneManager
{
public:
	void Exec();	// シーンの実行
	void Draw();	// シーンの描画

	static void SetNextScene( SceneID next_ );	// 次のシーン設定

private:
	class SceneBase* create_NextScene();	// 次のシーンを作成

private:
	class SceneBase*	m_pScene;		// 実行中のシーン
	static SceneID 		m_NextSceneID;	// 次に作るシーンのID

//------------------------------------------------------------
// シングルトンデザイン
public:
	// staticなm_pInstanceへのアクセス用関数群
	// 実体を作る関数
	static void CreateInstance();
	// 実体を破棄する関数
	static void DestroyInstance();
	// 実体があるかを確認する関数
	static bool IsNull();
	// 実体を取得する関数
	static SceneManager* GetInstance();

private:
	SceneManager();
	~SceneManager();

private:
	static SceneManager* m_pInstance;
};

#endif	// #ifndef SCENE_MANAGER_H

