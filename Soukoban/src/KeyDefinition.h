
#ifndef KEY_DEFINITION_H
#define KEY_DEFINITION_H

#include "DxLib.h"

// キーの種類
enum KeyType
{
	KeyType_Up,		// 上移動
	KeyType_Down,	// 下移動
	KeyType_Left,	// 左移動
	KeyType_Right,	// 右移動
	KeyType_Enter,	// 決定
	KeyType_Reset,	// リセット
	KeyType_Clear,  // クリアする

	KeyType_Max		// キーの種類の数
};

// キーの種類に対応する、実際の入力配列
const int KEY_ASSIGN[KeyType_Max] = 
{
	KEY_INPUT_UP,		// KeyType_Up
	KEY_INPUT_DOWN,		// KeyType_Down
	KEY_INPUT_LEFT,		// KeyType_Left
	KEY_INPUT_RIGHT,	// KeyType_Right
	KEY_INPUT_RETURN,	// KeyType_Enter
	KEY_INPUT_R,		// KeyType_Reset
	KEY_INPUT_C,		// KeyType_Clear
};

#endif	// #ifndef KEY_DEFINITION_H
