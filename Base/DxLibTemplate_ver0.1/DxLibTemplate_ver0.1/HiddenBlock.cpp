#include "HiddenBlock.h"
#include "Camera.h"
#include "ImageManager.h"

#include <DxLib.h>

//---------------------------------------------------------------------------------
// HardBlock の処理
//---------------------------------------------------------------------------------

//! @brief コンストラクタ
HiddenBlock::HiddenBlock(int _id, Float2 _start, int _itemType)
	: Block(_id, OBJECT_TYPE::HIDDEN_BLOCK, _start, { 16.0f, 16.0f })
{
	hasSpawned = false;		//! 未生成状態で開始
	itemType = _itemType;	//! 内部アイテムを設定
	isSolid = true;			//! 空ブロックは当たり判定を持つ

	image = ImageManager::IMAGE_HIDDEN_BLOCK;
}

HiddenBlock::~HiddenBlock()
{
}

//---------------------------------------------------------------------------------
// 更新処理
//---------------------------------------------------------------------------------
void HiddenBlock::update()
{
	// 特に更新処理なし
}

//---------------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------------
void HiddenBlock::render()
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

//! @brief ブロックがヒットされた時のコールバック実装
void HiddenBlock::onHit(int hitDirection)
{
	// 後で処理を書きます
}