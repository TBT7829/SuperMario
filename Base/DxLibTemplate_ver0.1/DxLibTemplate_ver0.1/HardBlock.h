#pragma once

#include "Block.h"

// ここでは、HardBlockクラスの宣言を行う
// (1-1は階段ブロックの固いブロック用)
//! @brief 空のブロック
class HardBlock : public Block
{
public:
	//! @brief コンストラクタ
	HardBlock(int _id, Float2 _start);

	//! @brief デストラクタ
	virtual ~HardBlock();

	//! @brief 更新
	void update() override;

	//! @brief 描画
	void render() override;

	//! @brief ブロックがヒットされた時のコールバック
	void onHit(int hitDirection) override;

	//! @brief 画像を保存する変数
	int image;
};