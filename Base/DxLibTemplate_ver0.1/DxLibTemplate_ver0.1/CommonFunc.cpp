#include "CommonFunc.h"
#include "Float2.h"
#include<DxLib.h>

//---------------------------------------------------------------------------------
//	汎用関数
//---------------------------------------------------------------------------------

int mouseLeftFrame = 0;
int mouseRightFrame = 0;


// 度数法:degree
// 弧度法:radian

// 度をラジアンに変換する
float TO_RADIAN(float degree)
{
	return degree * 3.14159265f / 180.0f;
}

// ラジアン角からオイラー角へ
float TO_DEGREE(float radian)
{
	return radian / 3.14159265f * 180.0f;
}


// 値を確認し最大値と最小値の範囲内に修正
int fixValue(int val, int min, int max)
{
	int ret = val;
	if (ret < min) ret = min;
	if (max < ret) ret = max;

	return ret;
}


//---------------------------------------------------------------------------------
//	マウス関数
//---------------------------------------------------------------------------------
int mouseButtonStatePrev = 0;
int mouseButtonStateCurrent = 0;

// マウスの状態を更新
void UpdateMouseButtonState()
{
	mouseButtonStatePrev = mouseButtonStateCurrent;
	mouseButtonStateCurrent = GetMouseInput();
}

// マウスのボタンが押されているか判定
bool CheckMouseInput(int mouseButton)
{
	return mouseButtonStateCurrent & mouseButton;
}

// マウスのボタンが押された瞬間か判定
bool PushMouseInput(int mouseButton)
{
	return ((mouseButtonStateCurrent ^ mouseButtonStatePrev) & mouseButtonStateCurrent) == mouseButton;
}

// マウスの座標を取得
void GetMousePos(Float2* pPos)
{
	int x = 0;
	int y = 0;
	GetMousePoint(&x, &y);
	pPos->x = (float)x;
	pPos->y = (float)y;
}

// マウスのX座標を取得
float GetMouseX()
{
	Float2 pos;
	GetMousePos(&pos);

	return pos.x;
}

// マウスのY座標を取得
float GetMouseY()
{
	Float2 pos;
	GetMousePos(&pos);

	return pos.y;
}

//---------------------------------------------------------------------------------
//	ランダム関数
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//	０～ i_max までのランダムな値を返す関数（ int 型）
//---------------------------------------------------------------------------------
int GetRandomI(int i_max)
{
	return rand() % (i_max + 1);
}
//---------------------------------------------------------------------------------
//	i_from ～ i_to までのランダムな値を返す関数（ int 型）
//---------------------------------------------------------------------------------
int GetRandomI(int i_from, int i_to)
{
	int value = i_to - i_from;
	int random = GetRandomI(value);
	return i_from + random;
}
//---------------------------------------------------------------------------------
//	0.0 ～ 1.0 までのランダムな値を返す関数（ float 型）
//---------------------------------------------------------------------------------
float GetRandomF()
{
	float random = (float)rand();
	return random / RAND_MAX;
}
//---------------------------------------------------------------------------------
//	0.0 ～ f_max までのランダムな値を返す関数（ float 型）
//---------------------------------------------------------------------------------
float GetRandomF(float f_max)
{
	float random = GetRandomF();
	return random * f_max;
}
//---------------------------------------------------------------------------------
//	f_from ～ f_to までのランダムな値を返す関数（ float 型）
//---------------------------------------------------------------------------------
float GetRandomF(float f_from, float f_to)
{
	float value = f_to - f_from;
	float random = GetRandomF(value);
	return f_from + random;
}
