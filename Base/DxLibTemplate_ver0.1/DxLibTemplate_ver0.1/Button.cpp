#include "Button.h"
#include "keyManager.h"


Button::Button(Float2 pos_, Float2 size_, const std::string& text_, const Color& defCol_, const Color& selCol_, const Color& textCol_)
{
	pos.x = pos_.x;
	pos.y = pos_.y;
	size.x = size_.x;
	size.y = size_.y;
	defCol = defCol_;
	selCol = selCol_;
	textCol = textCol_;
	
	text = text_;
	isSelect = false;
	isActive = false;
}

bool Button::detect()
{
	return true;
}

void Button::setSelect(bool select)
{
	isSelect = select;
}

void Button::setActive(bool active)
{
	isActive = active;
}

void Button::render()
{

	int width, height;
	GetDrawStringSize(&width, &height, NULL, text.c_str(), text.size());
	if (isSelect) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, selCol.a);
		DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y, GetColor(selCol.r, selCol.g, selCol.b), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, defCol.a);
		DrawLineBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y, GetColor(defCol.r, defCol.g, defCol.b));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, textCol.a);
		DrawString(pos.x + (size.x - width) * 0.5f, pos.y + (size.y - height) * 0.5f, text.c_str(), GetColor(textCol.r, textCol.g, textCol.b));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, defCol.a);
		DrawLineBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y, GetColor(defCol.r, defCol.g, defCol.b));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, textCol.a);
		DrawString(pos.x + (size.x - width) * 0.5f, pos.y + (size.y - height) * 0.5f, text.c_str(), GetColor(textCol.r, textCol.g, textCol.b));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}
