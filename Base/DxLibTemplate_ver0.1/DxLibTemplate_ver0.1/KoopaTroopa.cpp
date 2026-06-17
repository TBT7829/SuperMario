#include "KoopaTroopa.h"
#include "Object.h"
#include "ImageManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Camera.h"
#include <DxLib.h>

//! @brief コンストラクタ
KoopaTroopa::KoopaTroopa(float startX, float startY) : Object(0, KOOPA_TROOPA)
{
	pos.x = startX;
	pos.y = startY;
	size.x = 16.0f;
	size.y = 24.0f;
	movSpeed.x = 0.0f;
	movSpeed.y = 0.0f;

	state = WAIT_APPEAR;

	
	m_imageHandle = ImageManager::getInstance()->getImageHandle(ImageManager::IMAGE_KOOPA_WALK);
}

KoopaTroopa::~KoopaTroopa()
{
}

//! @brief 更新処理（出現チェックと移動）
void KoopaTroopa::update()
{
	// 1. 出現待ち状態のとき
	if (state == WAIT_APPEAR)
	{
		// プレイヤーの現在地を取得
		Player* pPlayer = PlayerManager::getInstance()->get();
		if (pPlayer != nullptr)
		{
			// マリオとの距離が「画面外右側の一定ラインに入ったら出現
			if (pos.x - pPlayer->pos.x < 240.0f)
			{
				state = WALKING;
				movSpeed.x = -1.0f; // 左に向かって歩き出す
			}
		}
		return; // 出現前はこれ以降の移動処理をしない
	}

	// 2. 歩行中のとき
	if (state == WALKING)
	{
		// 左右移動の更新
		pos.x += movSpeed.x;
		pos.y += movSpeed.y;

		
	}
}

//! @brief 描画処理
void KoopaTroopa::render()
{
	if (state == WAIT_APPEAR) return; // 出現前は非表示

	float drawX = Camera::getInstance().worldToScreenX(pos.x);

	// 画像の代わりに、緑色の四角形を画面に描く
	// DrawBox((int)drawX, (int)pos.y, (int)(drawX + size.x), (int)(pos.y + size.y), GetColor(0, 255, 0), TRUE);
	// ノコノコの画像を描画する
	DrawGraph((int)drawX, (int)pos.y, m_imageHandle, TRUE);
}