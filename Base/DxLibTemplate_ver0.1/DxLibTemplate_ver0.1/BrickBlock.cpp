#include "BrickBlock.h"
#include "BlockManager.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "ImageManager.h"
#include <DxLib.h>

//---------------------------------------------------------------------------------
//	BrickBlock 実装
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
BrickBlock::BrickBlock(int _id, Float2 _start)
	: Block(_id, OBJECT_TYPE::BRICK_BLOCK, _start, { 16.0f, 16.0f })
{
	image = ImageManager::IMAGE_BRICK_BLOCK;
	isSolid = true;
}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
BrickBlock::~BrickBlock()
{
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void BrickBlock::update()
{
	// 現状特別な更新は不要
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void BrickBlock::render()
{
	// スクリーン座標変換
	float drawX = Camera::getInstance().worldToScreenX(pos.x);
	int drawY = (int)pos.y;

	// 画像ハンドルを取得
	int imgHandle = ImageManager::getInstance()->getImageHandle(image);

	int x1 = (int)drawX;
	int y1 = drawY;
	int x2 = (int)(drawX + size.x);
	int y2 = drawY + (int)size.y;

	// レンガ色で描画
	//DrawBox(x1, y1, x2, y2, GetColor(200, 100, 50), TRUE);
	//DrawLineBox(x1, y1, x2, y2, GetColor(150, 75, 0));

	DrawGraph(drawX, drawY, imgHandle, TRUE);
}

//---------------------------------------------------------------------------------
//	ヒット後処理
//---------------------------------------------------------------------------------
void BrickBlock::onHit(int hitDirection)
{
	// 下からのヒットでブロックを消す
	if (hitDirection == CollisionManager::BOTTOM)
	{
		ObjectManager::getInstance()->kill(getObjectId());
		BlockManager::getInstance()->remove(getObjectId());
	}
}