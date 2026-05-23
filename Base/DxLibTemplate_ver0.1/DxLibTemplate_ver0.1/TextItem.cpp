#include "TextItem.h"

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
TextItem::TextItem(Float2 pos_, Float2 size_, const std::string& text_, const Color& boxCol_, const Color& textCol_)
{
	pos.x = pos_.x;
	pos.y = pos_.y;
	size.x = size_.x;
	size.y = size_.y;
	boxCol = boxCol_;
	textCol = textCol_;

	text = text_;
}

//---------------------------------------------------------------------------------
//	描画関数
//---------------------------------------------------------------------------------
void TextItem::render()
{
	int width, height;
	GetDrawStringSize(&width, &height, NULL, text.c_str(), text.size());

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, boxCol.a);
	DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.x, GetColor(boxCol.r, boxCol.g, boxCol.b), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, textCol.a);
	DrawString(pos.x + (size.x - width) * 0.5f, pos.y + (size.y - height) * 0.5f, text.c_str(), GetColor(textCol.r, textCol.g, textCol.b));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
