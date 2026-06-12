#include "CoinBlock.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "Coin.h"
#include "CommonFunc.h"
#include "CollisionManager.h"
#include <DxLib.h>

//---------------------------------------------------------------------------------
//	CoinBlock の実装
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CoinBlock::CoinBlock(int _id, Float2 _start, int _coinCount)
	: Block(_id, OBJECT_TYPE::COIN_BLOCK, _start, { 16.0f, 16.0f })
{
	maxCoinCount = _coinCount;
	coinSpawnedCount = 0;
	isSolid = true;
}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
CoinBlock::~CoinBlock()
{
}

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void CoinBlock::update()
{

}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void CoinBlock::render()
{
	// カメラオフセットを適用
	float drawX = Camera::getInstance().worldToScreenX(pos.x);
	int drawY = (int)pos.y;
	int x1 = (int)drawX;
	int y1 = drawY;
	int x2 = (int)(drawX + size.x);
	int y2 = drawY + (int)size.y;

	// コインブロック: 金色の矩形
	DrawBox(x1, y1, x2, y2, GetColor(255, 200, 100), TRUE);
	DrawLineBox(x1, y1, x2, y2, GetColor(200, 150, 50));

	// 残りコイン数を矩形内に表示
	SetFontSize(10);
	char coinText[16];
	sprintf_s(coinText, sizeof(coinText), "%d", getRemainingCoins());
	DrawString(x1 + 3, y1 + 3, coinText, GetColor(0, 0, 0));

	// デバッグ: 生成済みコイン数表示（オプション）
#ifdef IS_DEBUG
	SetFontSize(8);
	char coinDebugText[16];
	sprintf_s(coinDebugText, sizeof(coinDebugText), "[%d]", coinSpawnedCount);
	DrawString(x1, y1 - 12, coinDebugText, GetColor(255, 255, 255));
#endif
}

//---------------------------------------------------------------------------------
//	ヒット後処理
//---------------------------------------------------------------------------------
void CoinBlock::onHit(int hitDirection)
{
	// コインがまだ残っており、下からのヒット（ジャンプで下から叩いた）の場合のみ生成
	if (coinSpawnedCount < maxCoinCount && hitDirection == CollisionManager::BOTTOM)
	{
		spawnCoin();
	}
}


//---------------------------------------------------------------------------------
//	残りのコイン数を取得
//---------------------------------------------------------------------------------
int CoinBlock::getRemainingCoins() const
{
	return maxCoinCount - coinSpawnedCount;
}

//---------------------------------------------------------------------------------
//	コインブロックからコインを生成
//---------------------------------------------------------------------------------
void CoinBlock::spawnCoin()
{
	// 新しいIDを生成
	int newCoinId = ObjectManager::getInstance()->generateId();

	// コインの生成位置: ブロックの中央上部
	Float2 coinPos = { pos.x + size.x / 2.0f - 4.0f, pos.y - 8.0f };

	// 新しいコインオブジェクトを生成
	Coin* pCoin = new Coin(newCoinId, coinPos);

	// ObjectManagerに登録
	if (ObjectManager::getInstance()->add(pCoin))
	{
		coinSpawnedCount++;		//! 生成成功時のみカウント増加
	}
	else
	{
		//! 登録失敗時のメモリ解放
		delete pCoin;
		MY_ABORT();
	}
}