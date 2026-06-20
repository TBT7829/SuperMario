#pragma once

#include "Block.h"

//! @brief コインブロッククラス
//! @brief Block クラスを継承
//! @brief ハテナブロックとは異なり、複数回叩くことができる
//! @brief 初代マリオのコインブロック機能を再現
class CoinBlock : public Block
{
public:
	//! @brief コンストラクタ
	//! @param _id ブロックID
	//! @param _start ブロック位置
	//! @param _coinCount コインの生成回数上限（デフォルト8回）
	CoinBlock(int _id, Float2 _start, int _coinCount = 8);

	//! @brief デストラクタ
	virtual ~CoinBlock();

	//! @brief 更新処理
	void update() override;

	//! @brief 描画処理
	void render() override;

	//! @brief ブロックがヒットされた時のコールバック
	//! @param hitDirection ヒット方向（1=下から, 2=上から, 3=左から, 4=右から）
	//! @note CollisionManager から呼び出される
	void onHit(int hitDirection) override;

	//! @brief 残りのコイン数を取得
	//! @return 残りコイン数
	int getRemainingCoins() const;

private:
	//! @brief コインの生成回数（上限）
	int maxCoinCount;

	//! @brief 既に生成されたコインの回数
	int coinSpawnedCount;

	//! @brief コインブロックからコインを生成する関数
	void spawnCoin();

	//! @brief 画像を保存する変数
	int image;
};
