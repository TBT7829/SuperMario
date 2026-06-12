#pragma once

#include "Block.h"

//! @brief 空のブロック
class EmptyBlock : public Block
{
public:
	//! @brief コンストラクタ
	EmptyBlock(int _id, Float2 _start);

	//! @brief デストラクタ
	virtual ~EmptyBlock();

	//! @brief 更新
	void update() override;

	//! @brief 描画
	void render() override;

	//! @brief ブロックがヒットされた時のコールバック
	void onHit(int hitDirection) override;
};