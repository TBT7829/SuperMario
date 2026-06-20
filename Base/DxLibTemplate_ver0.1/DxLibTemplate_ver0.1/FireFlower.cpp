#include "FireFlower.h"
#include "Camera.h"
#include "ObjectManager.h"

#include <DxLib.h>

//---------------------------------------------------------------------------------
//	FireFlower の実装
//---------------------------------------------------------------------------------

//! @brief コンストラクタ
FireFlower::FireFlower(int _id, Float2 _pos)
	: Item(_id, OBJECT_TYPE::FIRE_FLOWER, _pos)	
{
	pos = _pos;
	size = { 14.0f, 16.0f };		// ファイアフラワーサイズ
	velocity = { 0.0f, 0.0f };
	moveDirection = 1;				// 初期：右方向
	moveSpeed = 0.0f;				// 移動速度
	rotationAngle = 0.0f;
}

//! @brief デストラクタ
FireFlower::~FireFlower()
{
}

//! @brief 更新処理
void FireFlower::update()
{
	// マッシュルームと同じ物理演算
	// 初代マリオ：ファイアフラワーは出現後、水平方向に移動して落ちていく

	// 横方向移動
	velocity.x = moveDirection * moveSpeed;
	pos.x += velocity.x;

	// 重力による垂直移動
	// 重力による垂直移動
	if (isGround == false) {
		velocity.y += 0.2f;				// 重力加速度
		pos.y += velocity.y;
	}

	rotationAngle += 12.0f;			// 毎フレーム12度回転
	
}

//! @brief 描画処理
void FireFlower::render()
{
	// カメラオフセットを適用
	float drawX = Camera::getInstance().worldToScreenX(pos.x);
	int drawY = (int)pos.y;

	int x1 = (int)drawX;
	int y1 = drawY;
	int x2 = (int)(drawX + size.x);
	int y2 = drawY + (int)size.y;

	// 赤・黄色のファイアフラワー形状
	// 本実装ではImageManagerでファイアフラワー画像を描画
	
	// 茎（緑）
	DrawBox(x1 + 4, y1 + 8, x2 - 4, y2, GetColor(0, 200, 0), TRUE);

	// 花弁（赤）- 中央
	DrawCircle((int)drawX + 4, y1 + 4, 4, GetColor(255, 0, 0), TRUE);

	// 花弁（黄色）- 周辺
	DrawCircle((int)drawX - 2, y1 + 6, 2, GetColor(255, 255, 0), TRUE);
	DrawCircle((int)drawX + 10, y1 + 6, 2, GetColor(255, 255, 0), TRUE);

	// デバッグ: 移動方向表示（オプション）
#ifdef IS_DEBUG
	SetFontSize(8);
	char fireFlowerDebugText[16];
	sprintf_s(fireFlowerDebugText, sizeof(fireFlowerDebugText), "F%d", moveDirection);
	DrawString((int)drawX - 8, drawY - 8, fireFlowerDebugText, GetColor(255, 255, 255));
#endif
}

//! @brief プレイヤーに拾われた時の処理
void FireFlower::onCollectByPlayer()
{
	// プレイヤーのフォーム変更
	// TODO: PlayerManager::getInstance()->get()->setFormState(Player::FIRE);

	// パワーアップサウンド再生（オプション）
	// TODO: SoundManager::getInstance()->play(SOUND_FIRE_POWER_UP);

	// ファイアフラワー消去
	ObjectManager::getInstance()->kill(getObjectId());

	// デバッグ出力
#ifdef IS_DEBUG
	// OutputDebugStringA("Fire Flower collected!\n");
#endif
}