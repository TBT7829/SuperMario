#pragma once

#include "Color.h"
#include"Float2.h"
#include <string>


// 文と四角を持つテキストアイテムクラス
class TextItem
{
//-------------------------
// メンバ関数
//-------------------------
public:
	// コンストラクタ
	TextItem(Float2 pos_ = { 0.0f, 0.0f }, Float2 size_ = { 0.0f, 0.0f }, const std::string& text_ = "",
		const Color& boxCol_ = Color(255, 255, 255, 1), const Color& textCol_ = Color(255, 255, 255, 1));

	// 描画関数
	void render();

//-------------------------
// メンバ変数
//-------------------------
public:
	// 座標
	Float2 pos;
	// サイズ
	Float2 size;
	// 四角の色
	Color boxCol;
	// 文字の色
	Color textCol;
	// 文字
	std::string text;

	
};


