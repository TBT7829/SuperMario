#include "QuestionBlock.h"
#include "ObjectManager.h"
#include "BlockManager.h"
#include "ImageManager.h"
#include "Camera.h"
#include "Coin.h"
#include "SuperMushroom.h"
#include "FireFlower.h"
#include"CommonFunc.h"
#include "CollisionManager.h"
#include "ItemManager.h"
#include <DxLib.h>

//---------------------------------------------------------------------------------
//	QuestionBlock の実装
//---------------------------------------------------------------------------------

//! @brief コンストラクタ
QuestionBlock::QuestionBlock(int _id, Float2 _start, int _itemType)
	: Block(_id, OBJECT_TYPE::QUESTION_BLOCK, _start, { 16.0f, 16.0f })
{
	hasSpawned = false;		//! 未生成状態で開始
	itemType = _itemType;	//! 内部アイテムを設定
	isSolid = true;			//! ハテナブロックは当たり判定を持つ
	image = ImageManager::IMAGE_EMPTY_BLOCK_01;
}

//! @brief デストラクタ
QuestionBlock::~QuestionBlock()
{
}

//! @brief 更新処理
void QuestionBlock::update()
{
	
}

//! @brief 描画処理
void QuestionBlock::render()
{
	// カメラオフセットを適用してワールド座標をスクリーン座標に変換
	float drawX = Camera::getInstance().worldToScreenX(pos.x);
	int drawY = (int)pos.y;
	int x1 = (int)drawX;
	int y1 = drawY;
	int x2 = (int)(drawX + size.x);
	int y2 = drawY + (int)size.y;

	if (hasSpawned)
	{
		// 画像ハンドルを取得
		int imgHandle = ImageManager::getInstance()->getImageHandle(image);
		DrawGraph(x1, y1, imgHandle, TRUE);

		//! 使用済み: グレー色（空ブロック状態）
		//DrawBox(x1, y1, x2, y2, GetColor(128, 128, 128), TRUE);
		//DrawLineBox(x1, y1, x2, y2, GetColor(64, 64, 64));
	}
	else
	{
		//! 未使用: 黄色（ハテナマーク）
		DrawBox(x1, y1, x2, y2, GetColor(255, 255, 0), TRUE);
		DrawLineBox(x1, y1, x2, y2, GetColor(200, 200, 0));

		//! ハテナマーク '?' を中央に描画
		SetFontSize(12);
		DrawString(x1 + 4, y1 + 2, "?", GetColor(0, 0, 0));
	}
}

//! @brief ブロックがヒットされた時のコールバック
void QuestionBlock::onHit(int hitDirection)
{
	// 既に生成済みの場合は何もしない
	if (hasSpawned)
	{
		return;
	}

	// 下からのヒット（プレイヤーがジャンプして下から衝突）の場合のみアイテムを生成
	if (hitDirection == CollisionManager::BOTTOM)
	{
		spawnItem();
		hasSpawned = true;
	}
}

//! @brief ハテナブロックからアイテムを生成する関数
void QuestionBlock::spawnItem()
{
	// 新しいIDを生成
	int newItemId = ObjectManager::getInstance()->generateId();

	// アイテムの生成位置: ブロックの中央上部
	Float2 itemPos = { pos.x + size.x / 2.0f - 4.0f, pos.y - 8.0f };

	// アイテムタイプに応じてオブジェクトを生成
	Item* pItem = nullptr;
	switch (itemType)
	{
	case ITEM_COIN:
		pItem = new Coin(newItemId, itemPos);
		break;

	case ITEM_MUSHROOM:
		pItem = new SuperMushroom(newItemId, itemPos);
		break;

	case ITEM_FIREFLOWER:
		pItem = new FireFlower(newItemId, itemPos);
		break;

	default:
		// 不明なアイテムタイプの場合はコインで代用
		pItem = new Coin(newItemId, itemPos);
		break;
	}

	// ObjectManagerに登録
	if (pItem && !ObjectManager::getInstance()->add(pItem))
	{
		// 登録失敗時のメモリ解放
		delete pItem;
		MY_ABORT();
	}
	// もし登録できなかったら、作ったアイテムを削除して中断する
	if (pItem && !ItemManager::getInstance()->Add(pItem)) {
		delete pItem;
		MY_ABORT();
	}

}