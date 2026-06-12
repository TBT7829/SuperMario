#pragma once

#include "Block.h"

//! @brief ハテナブロッククラス
//! @brief Block クラスを継承
//! @brief 下から叩かれると、内部アイテム（コイン/マッシュルーム/ファイアフラワー）を生成して使用済みに変わる
//! @brief 初代マリオの挙動を再現
class QuestionBlock : public Block
{
public:
	//! @brief アイテムタイプ定義
	enum ITEM_TYPE
	{
		ITEM_COIN = 0,			//! @brief コイン
		ITEM_MUSHROOM = 1,		//! @brief スーパーマッシュルーム
		ITEM_FIREFLOWER = 2,	//! @brief ファイアフラワー
	};

	//! @brief コンストラクタ
	//! @param _id ブロックID
	//! @param _start ブロック位置
	//! @param _itemType 内部に含まれるアイテムタイプ
	QuestionBlock(int _id, Float2 _start, int _itemType = ITEM_COIN);

	//! @brief デストラクタ
	virtual ~QuestionBlock();

	//! @brief 更新処理
	void update() override;

	//! @brief 描画処理
	void render() override;

	//! @brief ブロックがヒットされた時のコールバック
	//! @param hitDirection ヒット方向（1=下から, 2=上から, 3=左から, 4=右から）
	//! @note CollisionManager から呼び出される
	void onHit(int hitDirection) override;

private:
	//! @brief アイテムが生成済みかどうか
	bool hasSpawned;

	//! @brief 内部アイテムタイプ
	int itemType;

	//! @brief ハテナブロックからアイテムを生成する関数
	void spawnItem();
};
