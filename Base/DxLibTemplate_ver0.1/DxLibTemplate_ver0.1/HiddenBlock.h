#pragma once

#include "Block.h"

// ここでは、HardBlockクラスの宣言を行う
// (1-1は階段ブロックの固いブロック用)
//! @brief 空のブロック
class HiddenBlock : public Block
{
public:
	//! @brief アイテムタイプ定義
	enum ITEM_TYPE
	{
		ITEM_COIN = 0,			//! @brief コイン
		ITEM_1UP_MUSHROOM,		//! @brief 1UPキノコ
	};

	//! @brief コンストラクタ
	HiddenBlock(int _id, Float2 _start, int _itemType = ITEM_1UP_MUSHROOM);

	//! @brief デストラクタ
	virtual ~HiddenBlock();

	//! @brief 更新
	void update() override;

	//! @brief 描画
	void render() override;

	//! @brief ブロックがヒットされた時のコールバック
	void onHit(int hitDirection) override;

private:
	//! @brief 画像を保存する変数
	int image;

	//! @brief アイテムが生成済みかどうか
	bool hasSpawned;

	//! @brief 内部アイテムタイプ
	int itemType;

	//! @brief 隠しブロックからアイテムを生成する関数
	void spawnItem();

};