#pragma once


#pragma once

#include "Const.h"

class Block;

//! @brief Blockクラスのポインタ配列を持ち、ブロックの生成や削除、更新などを一括管理する
class BlockManager final
{
	//-------------------------
	// 静的メンバ関数
	//-------------------------
public:
	//シングルトン
	static BlockManager* getInstance();

	//-------------------------
	// メンバ関数
	//-------------------------
private:
	// コンストラクタ
	BlockManager();

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// コピーコンストラクタを削除
	// これをしないと実体が複数作れてしまう
	BlockManager(const BlockManager& obj) = delete;

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// 代入演算子をオーバーロードして削除
	BlockManager& operator = (const BlockManager& obj) = delete;

	// デストラクタ
	~BlockManager();
	// 渡されたIDからポインタ配列に登録されている
	// そのIDを持つブロックの要素番号を貰う関数
	int searchIdx(int id);

public:
	// ブロックのポインタ配列にブロックを加えてIDを渡す
	bool Add(Block* pBlock);

	// ポインタ配列の中からブロックを外す
	bool remove(int id);

	// IDからポインタ配列に登録されている
	// そのIDを持つブロックのポインタを貰う関数
	Block* search(int id);

	//今生きているブロックの数を調べる
	int getBlockNum();

	void exit();

	//-------------------------
	// メンバ変数
	//-------------------------
private:
	// 現在登録されているブロックの数を保持する
	int BlockNum;

public:
	//Blockクラスのポインタ配列
	Block* pBlockArray[BLOCK_MAX];

};