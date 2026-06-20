#pragma once

#include "Item.h"

//! @brief スーパーマッシュルームクラス
//! @brief Item クラスを継承
//! @brief ハテナブロックから生成される
//! @brief プレイヤーが接触するとサイズが大きくなる（LOW→TALL）
class SuperMushroom : public Item
{
public:
	//! @brief コンストラクタ
	//! @param _id オブジェクトID
	//! @param _pos マッシュルーム出現位置
	SuperMushroom(int _id, Float2 _pos);

	//! @brief デストラクタ
	virtual ~SuperMushroom();

	//! @brief 更新処理
	//! @note 横方向に移動（敵と同じ物理演算）
	void update() override;

	//! @brief 描画処理
	void render() override;

	//! @brief プレイヤーに拾われた時の処理
	//! @note プレイヤーのフォーム変更（TALL状態へ）
	void onCollectByPlayer() override;

	//! @brief 移動方向（-1=左, 1=右）
	int moveDirection;

	//! @brief 移動速度
	float moveSpeed;

	//! @brief ブロック当たり判定用フラグ
	bool isBlocked;

};
