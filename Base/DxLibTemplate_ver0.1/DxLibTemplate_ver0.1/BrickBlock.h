#pragma once

#include "Block.h"

//! @brief レンガブロック（プレイヤーが下から当てると壊れる）
class BrickBlock : public Block
{
public:
	//! @brief コンストラクタ
	BrickBlock(int _id, Float2 _start);

	//! @brief デストラクタ
	virtual ~BrickBlock();

	//! @brief 更新
	void update() override;

	//! @brief 描画
	void render() override;

	//! @brief ヒット処理（外部から呼ばれる）
	//! @param hitDirection 1=下から, 2=上から, 3=左から, 4=右から
	void onHit(int hitDirection) override;
};