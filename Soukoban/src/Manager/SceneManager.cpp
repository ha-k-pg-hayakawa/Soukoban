
#include "SceneManager.h"

#include "../Scene/SceneBase.h"
#include "../Scene/TitleScene.h"
#include "../Scene/InGameScene.h"
#include "../Scene/ResultScene.h"

// staticなメンバ変数を初期化
SceneID SceneManager::m_NextSceneID = SceneID_Invalid;

void SceneManager::Exec()
{
	if( m_pScene == nullptr ){ return; }

	m_pScene->Exec();
	if( m_pScene->IsEnd() )
	{
		delete m_pScene;
		m_pScene = create_NextScene();
	}
}

void SceneManager::Draw()
{
	if( m_pScene == nullptr ){ return; }

	m_pScene->Draw();
}

void SceneManager::SetNextScene( SceneID next_ )
{
	m_NextSceneID = next_;
}

SceneBase* SceneManager::create_NextScene()
{
	SceneBase* next = nullptr;
	switch( m_NextSceneID )
	{
	// ここにそれぞれSceneBaseを継承した派生クラスをnewする処理を書く
	// シーンの増減があってもヘッダのインクルードとここ以外に変更は必要ない
	case SceneID_Title:		next = new TitleScene();	break;
	case SceneID_InGame:	next = new InGameScene();	break;
	case SceneID_Result:	next = new ResultScene();	break;
	default:				break;
	}
	return next;
}

//------------------------------------------------------------
// シングルトンデザイン
SceneManager* SceneManager::m_pInstance = nullptr;

// 実体を作る関数
void SceneManager::CreateInstance()
{
	// nullチェックをして、２回以上作られるのを防止
	if( m_pInstance == nullptr )
	{
		m_pInstance = new SceneManager();
	}
}
// 実体を破棄する関数
void SceneManager::DestroyInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}
// 実体があるかを確認する関数
bool SceneManager::IsNull()
{
	return (m_pInstance == nullptr);
}
// 実体を取得する関数
SceneManager* SceneManager::GetInstance()
{
	return m_pInstance;
}

SceneManager::SceneManager()
	: m_pScene( nullptr )
{
	// 最初に実行するシーンを作成する
	SetNextScene( SceneID_Title );
	m_pScene = create_NextScene();
}

SceneManager::~SceneManager()
{
	delete m_pScene;
	m_pScene = nullptr;
}

