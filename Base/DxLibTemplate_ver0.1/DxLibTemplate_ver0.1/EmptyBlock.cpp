#include "EmptyBlock.h"
#include "Camera.h"
#include <DxLib.h>

//---------------------------------------------------------------------------------
//	EmptyBlock 実装
//---------------------------------------------------------------------------------
EmptyBlock::EmptyBlock(int _id, Float2 _start)
	: Block(_id, OBJECT_TYPE::EMPTY_BLOCK, _start, { 16.0f, 16.0f })
{
	isSolid = true;
}

EmptyBlock::~EmptyBlock()
{

}

void EmptyBlock::update()
{
	// 特に更新処理なし
}

void EmptyBlock::render()
{
	// スクリーン座標変換
	float drawX = Camera::getInstance().worldToScreenX(pos.x);
	int drawY = (int)pos.y;
	int x1 = (int)drawX;
	int y1 = drawY;
	int x2 = (int)(drawX + size.x);
	int y2 = drawY + (int)size.y;

	// グレーで描画（使い切られたブロックの見た目）
	DrawBox(x1, y1, x2, y2, GetColor(128, 128, 128), TRUE);
	DrawLineBox(x1, y1, x2, y2, GetColor(64, 64, 64));
}