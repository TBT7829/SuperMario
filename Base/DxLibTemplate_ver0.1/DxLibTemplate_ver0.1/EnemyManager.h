#pragma once

#include "Const.h"

class Enemy;

//エネミーを管理するクラス
//! @brief Enemyクラスのポインタ配列を持ち、エネミーの生成や削除、更新などを一括管理する
class EnemyManager final
{
	//-------------------------
	// 静的メンバ関数
	//-------------------------
public:
	//! @brief シングルトン インスタンスを取得する
	static EnemyManager* getInstance();

	//-------------------------
	// メンバ関数
	//-------------------------
private:
	//! @brief コンストラクタ
	EnemyManager();

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// コピーコンストラクタを削除
	// これをしないと実体が複数作れてしまう
	EnemyManager(const EnemyManager& obj) = delete;

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// 代入演算子をオーバーロードして削除
	EnemyManager& operator = (const EnemyManager& obj) = delete;

	//! @brief デストラクタ
	~EnemyManager();

	//! @brief 渡されたIDからポインタ配列に登録されているエネミーの要素番号を取得する
	//! @param id 取得するエネミーのID
	//! @return エネミーの要素番号、存在しない場合は-1
	int searchIdx(int id);

public:
	//! @brief エネミーのポインタ配列にエネミーを加えてIDを渡す
	//! @param pEnemy 追加するエネミーのポインタ
	//! @return 追加に成功した場合はtrue、失敗した場合はfalse
	bool Add(Enemy* pEnemy);

	//! @brief ポインタ配列の中からエネミーを外す
	//! @param id 外すエネミーのID
	//! @return 外すことに成功した場合はtrue
	//! @return 失敗した場合はfalse
	bool remove(int id);

	//! @brief IDからポインタ配列に登録されているエネミーのポインタを取得する
	//! @param id 取得するエネミーのID
	//! @return エネミーのポインタ、存在しない場合はnullptr
	Enemy* search(int id);

	//! @brief 今生きているエネミーの数を調べる
	//! @return 生きているエネミーの数
	int getEnemyNum();

	//! @brief 終了処理
	void exit();

	//-------------------------
	// メンバ変数
	//-------------------------
private:
	//! @brief 現在登録されているエネミーの数を保持する
	int enemyNum;

public:
	//! @brief Enemyクラスのポインタ配列
	Enemy* pEnemyArray[ENEMY_MAX];

};