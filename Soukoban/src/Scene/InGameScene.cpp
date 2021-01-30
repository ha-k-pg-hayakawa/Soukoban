
#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "ResultScene.h"
#include "../MovedSingleton.h"

// 実行ステップ定義
enum
{
	STEP_START_JINGLE,	// 開始ジングル待ち
	STEP_INPUT,			// 入力待ち
	STEP_CLEAR_JINGLE,	// クリアジングル待ち
	STEP_END,
};

// 倉庫番のサンプルステージ
const int g_SampleStage[STAGE_HEIGHT][STAGE_WIDTH] =
{
	0,0,0,1,1,1,1,1,0,0,0,
	0,0,0,1,3,3,3,1,0,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	1,1,1,1,1,0,1,1,1,1,1,
	1,0,0,4,0,0,1,0,0,0,1,
	1,0,1,0,0,4,0,4,0,0,1,
	1,0,0,0,1,1,1,0,0,0,1,
	1,1,1,0,1,0,1,0,1,1,1,
	0,0,1,0,1,0,1,0,1,0,0,
	0,0,1,0,0,0,0,0,1,0,0,
	0,0,1,0,0,2,0,0,1,0,0,
	0,0,1,1,1,0,1,1,1,0,0,
};

InGameScene::InGameScene()
	: m_PlayerX( 0 )
	, m_PlayerY( 0 )
{
	Reset();
	set_Step( STEP_START_JINGLE );
}

InGameScene::~InGameScene()
{
}

void InGameScene::Exec()
{
	switch ( m_Step )
	{
	case STEP_START_JINGLE:	step_StartJingle();	break;
	case STEP_INPUT:		step_Input();		break;
	case STEP_CLEAR_JINGLE:	step_ClearJingle();	break;
	default:									break;
	}
}

void InGameScene::Draw()
{
	// ステージの中身と、プレイヤーを描画(DXライブラリのDrawBoxを使用)
	// 	int DrawBox( int x1 , int y1 , int x2 , int y2 , unsigned int Color , int FillFlag ) ;
	
	// 課題(22日まで)
	// m_StageDataの配列の中身をみて、それぞれの四角形を描画する
	//	ObjectType_Ground,			// 0 なし
	//	ObjectType_Wall,			// 1 白(255, 255, 255)
	//	ObjectType_Target,			// 3 赤(255,   0,   0)
	//	ObjectType_UnsetCrate,		// 4 紫(255,   0, 255)
	//	ObjectType_SetCrate = 7,	// 7 緑(  0, 255,   0)
	for( int y = 0; y < STAGE_HEIGHT; y++ )
	{
		for( int x = 0; x < STAGE_WIDTH; x++ )
		{
			int tmp = 0;
			switch( m_StageData[y][x] )
			{
			case ObjectType_Ground:
				// 0 なし
				tmp = LoadGraph("data/Ground/ground.png");
				break;
			case ObjectType_Wall:
				tmp = LoadGraph("data/Ground/block.png");
				break;
			case ObjectType_Target:
				tmp = LoadGraph("data/Crate/crate_00.png");
				break;
			case ObjectType_UnsetCrate:
				tmp = LoadGraph("data/Crate/crate_01.png");
				break;
			case ObjectType_SetCrate:
				tmp = LoadGraph("data/Crate/crate_02.png");
				break;
			}

			// DrawBoxで描画するなら地面以外という判定でもよい
			//if( m_StageData[y][x] != ObjectType_Ground )
			//{
				

			//マップの描画
			DrawExtendGraph(x * CHIP_WIDTH,
							y * CHIP_HEIGHT,
							x * CHIP_WIDTH + CHIP_WIDTH,
							y * CHIP_HEIGHT + CHIP_HEIGHT,
							tmp,
							TRUE);
			//}
		}
	}

	//プレイヤー画像に読み込み
	int Player[]
	{
		LoadGraph("data/Player/player_00.png"),
		LoadGraph("data/Player/player_01.png"),
		LoadGraph("data/Player/player_02.png"),
		LoadGraph("data/Player/player_03.png"),
		LoadGraph("data/Player/player_04.png"),
		LoadGraph("data/Player/player_05.png"),
		LoadGraph("data/Player/player_06.png"),
		LoadGraph("data/Player/player_07.png"),
		LoadGraph("data/Player/player_08.png"),
		LoadGraph("data/Player/player_09.png"),
		LoadGraph("data/Player/player_10.png"),
		LoadGraph("data/Player/player_11.png"),
	};

	if (Direction == DirType_Up)
	{
		if      (Animation == 1)Animation = 2;
		else if (Animation == 0)Animation = 1;
		else if (Animation != 0)Animation = 0;
	}
	else if (Direction == DirType_Down)
	{
		if      (Animation == 4)Animation = 5;
		else if (Animation == 3)Animation = 4;
		else if (Animation != 3)Animation = 3;
	}
	else if (Direction == DirType_Left)
	{
		if      (Animation == 7)Animation = 8;
		else if (Animation == 6)Animation = 7;
		else if (Animation != 6)Animation = 6;
	}
	else
	{
		if      (Animation == 10)Animation = 11;
		else if (Animation == 9)Animation = 10;
		else if (Animation != 9)Animation = 9;
	}

	//プレイヤーの描画
	DrawExtendGraph( m_PlayerX * CHIP_WIDTH,
				m_PlayerY * CHIP_HEIGHT,
				m_PlayerX * CHIP_WIDTH  + CHIP_WIDTH,
				m_PlayerY * CHIP_HEIGHT + CHIP_HEIGHT,
				Player[Animation],
				TRUE );

	if (IsClear() == true)
	{
		DrawString( 100, 240, "!! Game Clear !!", GetColor(255,255,0) );
	}

	// 画面左上にデバッグ用の文字を黒で表示する
	//DrawString( 20, 20, "InGameScene", GetColor(0,0,0) );

	DrawFormatString(400, 350, GetColor(255, 255, 255), "手数: %d", Moved);

	DrawString(400, 120, "デバッグ用:「C」キーでクリア", GetColor(255, 255, 255));

}

bool InGameScene::IsEnd() const
{
	return ( m_Step == STEP_END );
}

// 開始ジングル待ち
void InGameScene::step_StartJingle()
{
	set_Step( STEP_INPUT );
}
// 入力待ち
void InGameScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	/******************デバッグ用*************************/
	if (pInputMng->IsPush(KeyType_Clear))
	{
		Clear = true;
	}
	/******************デバッグ用*************************/
	if( pInputMng->IsPush(KeyType_Reset) )
	{
		Reset();
	}
	else if( pInputMng->IsPush(KeyType_Up) )
	{
		Move( DirType_Up );
		Direction = DirType_Up;
	}
	else if( pInputMng->IsPush(KeyType_Down) )
	{
		Move( DirType_Down );
		Direction = DirType_Down;
	}
	else if( pInputMng->IsPush(KeyType_Left) )
	{
		Move( DirType_Left );
		Direction = DirType_Left;
	}
	else if( pInputMng->IsPush(KeyType_Right) )
	{
		Move( DirType_Right );
		Direction = DirType_Right;
	}

	if( IsClear() )
	{
		set_Step( STEP_CLEAR_JINGLE );
	}
}
// クリアジングル待ち
void InGameScene::step_ClearJingle()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if( pInputMng->IsPush(KeyType_Enter) )
	{
		MovedSingleton::Instance()->SetMoved(Moved);

		set_Step( STEP_END );
		SceneManager::SetNextScene( SceneID_Result );
	}
}


// ゲームのクリア判定
// true  = クリアしている
// false = 未クリア
bool InGameScene::IsClear() const
{
	/******************デバッグ用*************************/
	if (Clear == true)
	{
		return true;
	}
	/******************デバッグ用*************************/

	// ２重for文でm_StageDataの配列を検索し、
	// １つでもObjectType_UnsetCrateが見つかったらfalseを返す
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (m_StageData[y][x] == ObjectType_UnsetCrate )
			{
				return false;
			}
		}
	}

	// for文を抜けてきたらObjectType_UnsetCrateがなかったことになり、
	// 逆説的にすべてObjectType_SetCrate状態になっている(== ゲームクリア)
	return true;
}

// 初期状態にリセット
void InGameScene::Reset()
{
	/******************デバッグ用*************************/
	Clear = false;
	/******************デバッグ用*************************/
	Moved = 0;
	Animation = -1;
	Direction = DirType_Up;

	// g_SampleStageを使ってステージデータを初期化
	// ※外部データを読み込んだり、ステージを増やす場合は処理内容を考える必要がある
	for( int y = 0; y < STAGE_HEIGHT; y++ )
	{
		for( int x = 0; x < STAGE_WIDTH; x++ )
		{
			m_StageData[y][x] = g_SampleStage[y][x];
			if( m_StageData[y][x] == ObjectType_Player )
			{
				m_PlayerX = x;
				m_PlayerY = y;
				m_StageData[y][x] = ObjectType_Ground;
			}
		}
	}
}

// 移動処理
void InGameScene::Move( DirType dir_ )
{
	// DirTypeが範囲外だったら処理終了
	if( dir_ < DirType_Up && dir_ >= DirType_Max )
	{
		return;
	}

	// 判定用の一時変数
	int next_x  = m_PlayerX;	// 次の移動先Ｘ
	int next_y  = m_PlayerY;	// 次の移動先Ｙ
	int next2_x = m_PlayerX;	// 次の次Ｘ
	int next2_y = m_PlayerY;	// 次の次Ｙ

	// 移動方向に応じて座標を設定
	// next_x(y),next2_x(y)の値をそれぞれ設定する
	switch( dir_ )
	{
	case DirType_Up:
		next_y  -= 1;
		next2_y -= 2;
		Moved++;
		break;
	case DirType_Down:
		next_y  += 1;
		next2_y += 2;
		Moved++;
		break;
	case DirType_Left:
		next_x  -= 1;
		next2_x -= 2;
		Moved++;
		break;
	case DirType_Right:
		next_x  += 1;
		next2_x += 2;
		Moved++;
		break;
	}

	// 移動先が画面外なら、関数を抜ける
	if( next_x < 0 || next_y < 0 || next_x > (STAGE_WIDTH - 1) || next_y > (STAGE_HEIGHT - 1) )
	{
		Moved--;
		return;
	}

	// 通常移動
	// 移動先がプレイヤーの乗れるマップチップ]だったら、m_PlayerX(Y)をnext_x(y)で上書き
	if( m_StageData[next_y][next_x] == ObjectType_Ground ||
		m_StageData[next_y][next_x] == ObjectType_Target )
	{
		m_PlayerX = next_x;
		m_PlayerY = next_y;
	}
	// 移動先に箱（クレート）がある場合
	else if( m_StageData[next_y][next_x] == ObjectType_UnsetCrate ||
			 m_StageData[next_y][next_x] == ObjectType_SetCrate )
	{
		// ２つ先が画面外かチェック
		if( next2_x < 0 || next2_y < 0 || next2_x > (STAGE_WIDTH - 1) || next2_y > (STAGE_HEIGHT - 1) )
		{
			return;
		}
		// ２つ先が移動できない物かチェック
		// 移動できるマップチップでない場合という判定
		if( m_StageData[next2_y][next2_x] != ObjectType_Ground &&
			m_StageData[next2_y][next2_x] != ObjectType_Target )
		{
			return;
		}

		// となりの位置を変更する
		if (m_StageData[next_y][next_x] == ObjectType_UnsetCrate)
		{
			m_StageData[next_y][next_x] = ObjectType_Ground;
		}
		else
		{
			m_StageData[next_y][next_x] = ObjectType_Target;
		}

		// ２つ先に箱を配置する
		if (m_StageData[next2_y][next2_x] == ObjectType_Ground)
		{
			m_StageData[next2_y][next2_x] = ObjectType_UnsetCrate;
		}
		else if( m_StageData[next2_y][next2_x] == ObjectType_Target )
		{
			m_StageData[next2_y][next2_x] = ObjectType_SetCrate;
		}

		// プレイヤーを移動させる
		m_PlayerX = next_x;
		m_PlayerY = next_y;
	}
	else
	{
		Moved--;
	}
}


