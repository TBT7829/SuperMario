#include "GroundBlock.h"
#include "Camera.h"
#include "ImageManager.h"

#include<DxLib.h>

//---------------------------------------------------------------------------------
//	GroundBlockの処理
//---------------------------------------------------------------------------------
GroundBlock::GroundBlock(int _id, Float2 _start)
    : Block(_id, OBJECT_TYPE::GROUND_BLOCK, _start, { 16.0f, 16.0f })
{
    image = ImageManager::IMAGE_GROUND_BLOCK_11;
}

GroundBlock::~GroundBlock()
{
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------   
void GroundBlock::update()
{
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GroundBlock::render()
{
	// カメラのオフセットを考慮して、ワールド座標をスクリーン座標に変換
    float drawX = Camera::getInstance().worldToScreenX(pos.x);

	// 画像ハンドルを取得
    int imgHandle = ImageManager::getInstance()->getImageHandle(image);

	// 四角形の左上と右下の座標を整数に変換
    int x1 = (int)drawX;
    int y1 = (int)pos.y;
    int x2 = (int)(drawX + size.x);
    int y2 = (int)(pos.y + size.y);

    // 地面は分かりやすく白（255, 255, 255）で枠線を描く例
    //DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), TRUE);

    DrawGraph(drawX, y1, imgHandle, TRUE);
}

<<<<<<< HEAD
//---------------------------------------------------------------------------------
//	ヒット後処理
//---------------------------------------------------------------------------------
void GroundBlock::onHit(int hitDirection)
{
}
=======
//! @brief ブロックがヒットされた時のコールバック実装
void GroundBlock::onHit(int hitDirection)
{
    // 何も起きないので特に処理はなし。
}
>>>>>>> 9ef37ef2cb22b7e96f47321853e3332edbfef40c
