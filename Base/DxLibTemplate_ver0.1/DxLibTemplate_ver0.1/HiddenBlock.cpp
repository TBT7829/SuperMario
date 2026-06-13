#include "HiddenBlock.h"
#include "Camera.h"
#include "ImageManager.h"

#include <DxLib.h>

//---------------------------------------------------------------------------------
// HardBlock の処理
//---------------------------------------------------------------------------------

//! @brief コンストラクタ
HiddenBlock::HiddenBlock(int _id, Float2 _start, int _itemType)
	: Block(_id, OBJECT_TYPE::HIDDEN_BLOCK, _start, { 16.0f, 16.0f })
{
	hasSpawned = false;		//! 未生成状態で開始
	itemType = _itemType;	//! 内部アイテムを設定
	isSolid = true;			//! 空ブロックは当たり判定を持つ

	image = ImageManager::IMAGE_HIDDEN_BLOCK;
}

HiddenBlock::~HiddenBlock()
{
}

//---------------------------------------------------------------------------------
// 更新処理
//---------------------------------------------------------------------------------
void HiddenBlock::update()
{
	// 特に更新処理なし
}

//---------------------------------------------------------------------------------
// 描画処理
//---------------------------------------------------------------------------------
void HiddenBlock::render()
{
	// スクリーン座標変換
	float drawX = Camera::getInstance().worldToScreenX(pos.x);

	// 画像ハンドルを取得
	int imgHandle = ImageManager::getInstance()->getImageHandle(image);


	int x1 = (int)drawX;
	int y1 = (int)pos.y;
	int x2 = (int)(drawX + size.x);
	int y2 = (int)(pos.y + size.y);

	//DrawGraph(drawX, y1, imgHandle, TRUE);

	// まだアイテム未生成（隠し状態）：通常は描画しない（透明）
	// デバッグ時のみ薄く枠を描画して位置が分かるようにする
	if (!hasSpawned)
	{
//#ifdef IS_DEBUG
		// 半透明の薄い枠で表示（デバッグ用）
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 48);
		DrawBox(x1, y1, x2, y2, GetColor(0, 128, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawLineBox(x1, y1, x2, y2, GetColor(0, 64, 128));
//#endif

		return;
	}

	// 既にスポーン済み（空ブロック化）：EmptyBlock と視覚的に区別するため、薄い青緑系で描画
	DrawBox(x1, y1, x2, y2, GetColor(160, 200, 200), TRUE);
	DrawLineBox(x1, y1, x2, y2, GetColor(80, 120, 120));

	DrawGraph(drawX, y1, imgHandle, TRUE);
}

//---------------------------------------------------------------------------------
// ヒット後処理
//---------------------------------------------------------------------------------
void HiddenBlock::onHit(int hitDirection)
{
	// 下からヒットされた場合のみ反応（hitDirection == 1 は下から）
	if (hitDirection != 1)
	{
		return;
	}

	// 既に出現済みなら何もしない
	if (hasSpawned)
	{
		return;
	}

	// アイテム生成
	spawnItem();

	// 見た目を空ブロック風に変更して再利用可能な見た目にする
	hasSpawned = true;

	// （任意）ここでサウンドやエフェクトを鳴らす／再生する処理を追加可能
}

//---------------------------------------------------------------------------------
// ハテナブロックからアイテムを生成する関数
//---------------------------------------------------------------------------------
void HiddenBlock::spawnItem()
{
	/*
	// ObjectManager に新規 ID を生成してもらう
	int newItemId = ObjectManager::getInstance()->generateId();

	// アイテムの生成位置（ブロックの上方中央あたり）
	Float2 itemPos = { pos.x + size.x / 2.0f - 4.0f, pos.y - 8.0f };

	// アイテム生成
	Item* pItem = nullptr;
	switch (itemType)
	{
	case ITEM_COIN:
		pItem = new Coin(newItemId, itemPos);
		break;

	case ITEM_1UP_MUSHROOM:
		pItem = new SuperMushroom(newItemId, itemPos);
		break;

	default:
		// デフォルトはコイン
		pItem = new Coin(newItemId, itemPos);
		break;
	}

	// ObjectManager に登録
	if (pItem && !ObjectManager::getInstance()->add(pItem))
	{
		// 登録に失敗したら破棄して致命的エラー
		delete pItem;
		MY_ABORT();
	}
	*/
}

