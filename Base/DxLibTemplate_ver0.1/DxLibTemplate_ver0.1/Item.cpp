#include "Item.h"

//---------------------------------------------------------------------------------
//	Item の実装
//---------------------------------------------------------------------------------

//! @brief コンストラクタ
Item::Item(int _id, OBJECT_TYPE _itemType, Float2 _pos)
	: Object(_id, _itemType)
{
	pos = _pos;
	size = { 8.0f, 8.0f };		// デフォルトサイズ
	velocity = { 0.0f, 0.0f };
	isOffScreen = false;
	isGround = false;
}

//! @brief デストラクタ
Item::~Item()
{
}

//! @brief 初期化処理
void Item::activateProc()
{
	// 派生クラスでオーバーライドして使用する
}

//! @brief 終了処理
void Item::deactiveProc()
{
	// 派生クラスでオーバーライドして使用する
}