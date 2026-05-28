#include "SuperMushroom.h"
#include "Camera.h"
#include "ObjectManager.h"

#include <DxLib.h>

//---------------------------------------------------------------------------------
//	SuperMushroom の実装
//---------------------------------------------------------------------------------

//! @brief コンストラクタ
SuperMushroom::SuperMushroom(int _id, Float2 _pos)
	: Item(_id, OBJECT_TYPE::SUPER_MUSHROOM, _pos)	
{
	pos = _pos;
	size = { 16.0f, 16.0f };		// マッシュルームサイズ
	velocity = { 0.0f, 0.0f };
	moveDirection = 1;				// 初期：右方向
	moveSpeed = 0.5f;				// 移動速度（敵と同じ程度）
	isBlocked = false;

}

//! @brief デストラクタ
SuperMushroom::~SuperMushroom()
{
}

//! @brief 更新処理
void SuperMushroom::update()
{
	// 初代マリオ：マッシュルームは出現後、水平方向に移動して落ちていく
	// 敵キャラ（Goomba等）と同じ物理演算を使用

	// 横方向移動
	velocity.x = moveDirection * moveSpeed;
	pos.x += velocity.x;

	// 重力による垂直移動
	velocity.y += 0.2f;				// 重力加速度
	pos.y += velocity.y;

	// ブロック衝突時の方向転換はCollisionManager で実装

	
}

//! @brief 描画処理
void SuperMushroom::render()
{
	// カメラオフセットを適用
	float drawX = Camera::getInstance().worldToScreenX(pos.x);
	int drawY = (int)pos.y;

	int x1 = (int)drawX;
	int y1 = drawY;
	int x2 = (int)(drawX + size.x);
	int y2 = drawY + (int)size.y;

	// 赤いマッシュルーム形状
	// 本実装ではImageManagerでマッシュルーム画像を描画
	DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), TRUE);
	DrawLineBox(x1, y1, x2, y2, GetColor(200, 0, 0));

	// マッシュルームの目を簡易描画
	DrawCircle(x1 + 4, y1 + 4, 1, GetColor(255, 255, 255), TRUE);
	DrawCircle(x2 - 4, y1 + 4, 1, GetColor(255, 255, 255), TRUE);

	// デバッグ: 移動方向表示（オプション）
#ifdef IS_DEBUG
	SetFontSize(8);
	char mushroomDebugText[16];
	sprintf_s(mushroomDebugText, sizeof(mushroomDebugText), "M%d", moveDirection);
	DrawString((int)drawX - 8, drawY - 8, mushroomDebugText, GetColor(255, 255, 255));
#endif
}

//! @brief プレイヤーに拾われた時の処理
void SuperMushroom::onCollectByPlayer()
{
	// プレイヤーのフォーム変更

	// パワーアップサウンド再生（オプション）
	// TODO: SoundManager::getInstance()->play(SOUND_POWER_UP);

	// マッシュルーム消去
	ObjectManager::getInstance()->kill(getObjectId());

	// デバッグ出力
#ifdef IS_DEBUG
	// OutputDebugStringA("Super Mushroom collected!\n");
#endif
}