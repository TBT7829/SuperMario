#include "HardBlock.h"
#include "Camera.h"
#include "ImageManager.h"

#include <DxLib.h>

//---------------------------------------------------------------------------------
// HardBlock の処理
//---------------------------------------------------------------------------------
HardBlock::HardBlock(int _id, Float2 _start)
	: Block(_id, OBJECT_TYPE::HARD_BLOCK, _start, { 16.0f, 16.0f })
{
	image = ImageManager::IMAGE_HARD_BLOCK;
}

HardBlock::~HardBlock()
{
}

//---------------------------------------------------------------------------------
// 更新処理
//---------------------------------------------------------------------------------
void HardBlock::update()
{
	// 特に更新処理なし
}

//---------------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------------
void HardBlock::render()
{
	// スクリーン座標変換
	float drawX = Camera::getInstance().worldToScreenX(pos.x);

	// 画像ハンドルを取得
	int imgHandle = ImageManager::getInstance()->getImageHandle(image);


	int x1 = (int)drawX;
	int y1 = (int)pos.y;
	int x2 = (int)(drawX + size.x);
	int y2 = (int)(pos.y + size.y);

	DrawGraph(drawX, y1, imgHandle, TRUE);
}

//---------------------------------------------------------------------------------
// ヒット後処理
//---------------------------------------------------------------------------------
void HardBlock::onHit(int hitDirection)
{
}
