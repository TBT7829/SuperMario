#include "Coin.h"
#include "Camera.h"
#include "ObjectManager.h"

#include <DxLib.h>

//---------------------------------------------------------------------------------
//	Coin の実装
//---------------------------------------------------------------------------------

//! @brief コンストラクタ
Coin::Coin(int _id, Float2 _pos)
	: Item(_id, OBJECT_TYPE::COIN, _pos)
{
	pos = _pos;
	size = { 8.0f, 8.0f };			// コインサイズ
	velocity = { 0.0f, 0.0f };
	spawnFrame = 0;
	lifetimeFrames = 20;			// 20フレーム表示（約0.33秒）
	verticalVelocity = -2.0f;		// 初期上向き速度
	rotationAngle = 0.0f;
}

//! @brief デストラクタ
Coin::~Coin()
{
}

//! @brief 更新処理
void Coin::update()
{
	spawnFrame++;

	// 初代マリオ：コインは上に浮き上がり、放物線を描いて落ちる
	pos.y += verticalVelocity;
	verticalVelocity += 0.15f;		// 重力加速度

	rotationAngle += 6.0f;			// 毎フレーム6度回転

	// ライフタイムを超過したら消去
	if (spawnFrame >= lifetimeFrames)
	{
		// コイン消去
		ObjectManager::getInstance()->kill(getObjectId());
	}
}

//! @brief 描画処理
void Coin::render()
{
	// カメラオフセットを適用
	float drawX = Camera::getInstance().worldToScreenX(pos.x);
	int drawY = (int)pos.y;

	// 現在は黄色い円で描画
	// 本実装ではImageManagerでコイン画像を描画
	DrawCircle((int)drawX, drawY, 4, GetColor(255, 255, 0), TRUE);
	DrawCircle((int)drawX, drawY, 4, GetColor(200, 200, 0), FALSE);

	// デバッグ: ライフタイム表示（オプション）
#ifdef IS_DEBUG
	SetFontSize(8);
	char coinDebugText[16];
	sprintf_s(coinDebugText, sizeof(coinDebugText), "%d", lifetimeFrames - spawnFrame);
	DrawString((int)drawX - 8, drawY - 8, coinDebugText, GetColor(255, 255, 255));
#endif
}

//! @brief プレイヤーに拾われた時の処理
void Coin::onCollectByPlayer()
{
	// スコア加算（PlayerManager経由がよさそう）
	// PlayerManager::getInstance()->addScore(10);

	// コイン回収サウンド再生
	// TODO: SoundManager::getInstance()->play(SOUND_COIN);

	// コイン消去
	ObjectManager::getInstance()->kill(getObjectId());

	// デバッグ出力
#ifdef IS_DEBUG
	// OutputDebugStringA("Coin collected!\n");
#endif
}