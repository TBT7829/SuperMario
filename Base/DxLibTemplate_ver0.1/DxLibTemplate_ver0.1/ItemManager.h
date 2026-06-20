#pragma once

#include "Const.h"

class Item;

//アイテムを管理するクラス
//! @brief Itemクラスのポインタ配列を持ち、アイテムの生成や削除、更新などを一括管理する
class ItemManager final
{
	//-------------------------
	// 静的メンバ関数
	//-------------------------
public:
	//! @brief シングルトン インスタンスを取得する
	static ItemManager* getInstance();

	//-------------------------
	// メンバ関数
	//-------------------------
private:
	//! @brief コンストラクタ
	ItemManager();

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// コピーコンストラクタを削除
	// これをしないと実体が複数作れてしまう
	ItemManager(const ItemManager& obj) = delete;

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// 代入演算子をオーバーロードして削除
	ItemManager& operator = (const ItemManager& obj) = delete;

	//! @brief デストラクタ
	~ItemManager();

	//! @brief 渡されたIDからポインタ配列に登録されているアイテムの要素番号を取得する
	//! @param id 取得するアイテムのID
	//! @return アイテムの要素番号、存在しない場合は-1
	int searchIdx(int id);

public:
	//! @brief アイテムのポインタ配列にアイテムを加えてIDを渡す
	//! @param pItem 追加するアイテムのポインタ
	//! @return 追加に成功した場合はtrue、失敗した場合はfalse
	bool Add(Item* pItem);

	//! @brief ポインタ配列の中からアイテムを外す
	//! @param id 外すアイテムのID
	//! @return 外すことに成功した場合はtrue
	//! @return 失敗した場合はfalse
	bool remove(int id);

	//! @brief IDからポインタ配列に登録されているアイテムのポインタを取得する
	//! @param id 取得するアイテムのID
	//! @return アイテムのポインタ、存在しない場合はnullptr
	Item* search(int id);

	//! @brief 今生きているアイテムの数を調べる
	//! @return 生きているアイテムの数
	int getItemNum();

	//! @brief 終了処理
	void exit();

	//-------------------------
	// メンバ変数
	//-------------------------
private:
	//! @brief 現在登録されているアイテムの数を保持する
	int ItemNum;

public:
	//! @brief Itemクラスのポインタ配列
	Item* pItemArray[ITEM_MAX];

};