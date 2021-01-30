
#include "GameManager.h"

//------------------------------------------------------------
// シングルトンデザイン
GameManager* GameManager::m_pInstance = nullptr;

// 実体を作る関数
void GameManager::CreateInstance()
{
	// nullチェックをして、２回以上作られるのを防止
	if( m_pInstance == nullptr )
	{
		m_pInstance = new GameManager();
	}
}
// 実体を破棄する関数
void GameManager::DestroyInstance()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}
// 実体があるかを確認する関数
bool GameManager::IsNull()
{
	return (m_pInstance == nullptr);
}
// 実体を取得する関数
GameManager* GameManager::GetInstance()
{
	return m_pInstance;
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}



