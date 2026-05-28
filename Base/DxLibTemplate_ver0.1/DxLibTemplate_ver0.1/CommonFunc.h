#pragma once

#include <cstdio>
#include <cstdlib>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

class Float2;

//---------------------------------------------------------------------------------
//	汎用関数
//---------------------------------------------------------------------------------

// 度をラジアンに変換する
float TO_RADIAN(float);

// ラジアン角から度(オイラー角)に変換する
float TO_DEGREE(float);

// 値を確認し最大値と最小値の範囲内に修正
int fixValue(int val, int min, int max);

// テンプレート関数の実体定義ファイルの読み込み
//	引数の値を最小値minと最大値maxの範囲内に修正する
//	void fixValueAll(_T_* pVal, _T_ min, _T_ max)
//	第一引数に指定された値が、第二引数と第三引数の間におさまっているかをチェック
//	bool checkRange(_T_ val, _T_ min, _T_ max)
//          ↓
#include "CommonFunc.inc"

#if defined(_MSC_VER)
#define MY_FUNCTION_NAME __FUNCSIG__
#else
#define MY_FUNCTION_NAME __func__
#endif

static inline void MyAbortImpl(const char* file, int line, const char* func)
{
    fprintf(stderr, "Fatal Error: abort() called at %s:%d in function %s\n", file, line, func);
    fflush(stderr);
#if defined(_WIN32) || defined(_WIN64)
    char _my_abort_buf[1024];
    int _n = snprintf(_my_abort_buf, sizeof(_my_abort_buf), "Fatal Error: abort() called at %s:%d in function %s\n", file, line, func);
    if (_n > 0) { OutputDebugStringA(_my_abort_buf); }
#endif
    abort();
}

#define MY_ABORT() MyAbortImpl(__FILE__, __LINE__, MY_FUNCTION_NAME)

//---------------------------------------------------------------------------------
//	マウス関数
//---------------------------------------------------------------------------------

// マウスの状態を更新
void UpdateMouseButtonState();

// マウスのボタンが押されているか判定
bool CheckMouseInput(int mouseButton);

// マウスのボタンが押された瞬間か判定
bool PushMouseInput(int mouseButton);

// マウスの座標を取得
void GetMousePos(Float2*);

// マウスのX座標を取得
float GetMouseX();

// マウスのY座標を取得
float GetMouseY();

//---------------------------------------------------------------------------------
//	ランダム関数
//---------------------------------------------------------------------------------
int GetRandomI(int i_max);
int GetRandomI(int i_from, int i_to);

float GetRandomF();
float GetRandomF(float f_max);
float GetRandomF(float f_from, float f_to);