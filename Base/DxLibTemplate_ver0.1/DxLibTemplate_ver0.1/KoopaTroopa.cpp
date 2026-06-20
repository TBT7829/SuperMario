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
				movSpeed.y = 0.0f;

			}
		}
		return; // 出現前はこれ以降の移動処理をしない
	}

	// マリオに踏まれたかどうかの判定
	Player* pPlayer = PlayerManager::getInstance()->get();
	if (pPlayer != nullptr) {
		if (state == WALKING || (state == SHELL && movSpeed.x != 0.0f))
		{
			if (pPlayer->movSpeed.y > 0.0f &&
				pPlayer->pos.x + pPlayer->size.x > pos.x &&
				pPlayer->pos.x < pos.x + size.x)
			{
				float marioFootY = pPlayer->pos.y + pPlayer->size.y;
				if (marioFootY >= pos.y && marioFootY <= pos.y + 12.0f)
				{
					// 踏みつけ成功
					state = SHELL;      // 甲羅状態にする
					movSpeed.x = 0.0f;  // その場に止める

					// オブジェクト自体の当たり判定サイズも甲羅サイズにする
					pos.y += (size.y - 16.0f);
					size.y = 16.0f;

					// 画像ハンドルを甲羅のものに切り替える
					m_imageHandle = ImageManager::getInstance()->getImageHandle(ImageManager::IMAGE_KOOPA_SHELL);
					

					// マリオを上にポーンと跳ね返らせる
					pPlayer->movSpeed.y = -5.0f;
				}
			}
		}
		// B. すでに甲羅状態で、かつ止まっているときに横から触られたら滑らす
		else if (state == SHELL && movSpeed.x == 0.0f)
		{
			// マリオと甲羅の矩形が重なっているかチェック
			if (pPlayer->pos.x + pPlayer->size.x > pos.x &&
				pPlayer->pos.x < pos.x + size.x &&
				pPlayer->pos.y + pPlayer->size.y > pos.y &&
				pPlayer->pos.y < pos.y + size.y)
			{
				// マリオと甲羅の中心点を計算して、左右どちらから触ったかを判別する
				float marioCenterX = pPlayer->pos.x + (pPlayer->size.x / 2.0f);
				float shellCenterX = pos.x + (size.x / 2.0f);


				if (marioCenterX < shellCenterX)
				{
					// マリオが左側にいる ? 右へ高速に滑り出す
					movSpeed.x = 4.0f;
				}
				else
				{
					// マリオが右側にいる ? 左へ高速に滑り出す
					movSpeed.x = -4.0f;
				}


			}
		}
	}
	// 2. 歩行中のとき
	if (state == WALKING || state == SHELL)
	{
		// 重力を加算
		movSpeed.y += 0.5f;

		if (movSpeed.y > 8.0f)
		{
			movSpeed.y = 8.0f;
		}

		// 左右移動の更新
		pos.x += movSpeed.x;
		pos.y += movSpeed.y;

		// 滑っている甲羅の壁跳ね返りテスト
		if (state == SHELL && movSpeed.x != 0.0f)
		{
			float leftWallX = 100.0f;
			float rightWallX = 2130.0f;

			// 左の壁にぶつかった、または突き抜けたとき
			if (pos.x < leftWallX)
			{
				pos.x = leftWallX;     // 壁の位置に補正
				movSpeed.x *= -1.0f;   // 速度を反転させて右へ跳ね返す！
			}
			// 右の壁にぶつかった、または突き抜けたとき
			else if (pos.x > rightWallX)
			{
				pos.x = rightWallX;    // 壁の位置に補正
				movSpeed.x *= -1.0f;   // 速度を反転させて左へ跳ね返す！
			}
		}

		// 地面での着地
		float groundY = 185.0f;
		if (pos.y > groundY)
		{
			float holeLeftX = 0.0f;
			float holeRightX = 1400.0f;

			// もしノコノコが穴の範囲の中にいないときだけ着地させる
			if (pos.x < holeLeftX || pos.x > holeRightX)
			{
				pos.y = groundY;
				movSpeed.y = 0.0f;
			}
		}

		// 奈落の底まで落ちたら消滅させる処理
		// 画面の下端に到達したか
		if (pos.y > 450.0f)
		{
			movSpeed.y = 0.0f;
			movSpeed.x = 0.0f;
		}
	}
}

//! @brief 描画処理
void KoopaTroopa::render()
{
	if (state == WAIT_APPEAR) return; // 出現前は非表示

	float drawX = Camera::getInstance().worldToScreenX(pos.x);

	// 状態に合わせて描画する四角形のサイズを変える
	float drawSizeX = size.x; // 横幅はそのまま
	float drawSizeY = size.y; // 縦幅
	float drawPosY = pos.y;  // 描画を始めるY座標

	// 甲羅状態のときは小さくする
	if (state == SHELL)
	{
		drawSizeY = 16.0f; // 甲羅っぽく、縦幅をに小さくする

		// 地面にピッタリつけるために、小さくなった差分だけ
		// 描画位置を下にずらす
		drawPosY += (24.0f - drawSizeY);
	}

	// 画像の代わりに、緑色の四角形を画面に描く
	// DrawBox((int)drawX, (int)drawPosY, (int)(drawX + drawSizeX), (int)(drawPosY + drawSizeY), GetColor(0, 255, 0), TRUE);
	// ノコノコの画像を描画する
	DrawGraph((int)drawX, (int)pos.y, m_imageHandle, TRUE);
}