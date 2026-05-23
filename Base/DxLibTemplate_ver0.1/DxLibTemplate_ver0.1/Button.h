#pragma once

#include "Color.h"
#include "Float2.h"
#include <string>

// 四角とテキストを持つボタンクラス
class Button
{
//-------------------------
// メンバ関数
//-------------------------
public:
	Button(Float2 pos_ = { 0.0f, 0.0f }, Float2 size_ = {0.0f, 0.0f}, const std::string& text_ = "",
		const Color& defCol_ = Color(255, 255, 255, 1), const  Color& selCol_ = Color(255, 255, 255, 1), const Color& textCol_ = Color(255, 255, 255, 1) );
	// 決定した時の処理
	bool detect();
	// select変数に渡されたbool型の引数を代入する
	void setSelect(bool select);
	void setActive(bool active);
	// 描画関数
	void render();


//-------------------------
// メンバ関数
//-------------------------
public:
	// 座標
	Float2 pos;
	// サイズ
	Float2 size;
	// 通常時の色
	Color defCol;
	// 選んでいる時の色
	Color selCol;
	// 文字の色
	Color textCol;
	// 文字
	std::string text;
	// 選ばれているか
	bool isSelect;

	bool isActive;
};