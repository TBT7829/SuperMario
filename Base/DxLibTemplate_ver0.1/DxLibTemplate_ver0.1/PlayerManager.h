#pragma once

class Player;

class PlayerManager final
{
	//-------------------------
	// 静的メンバ関数
	//-------------------------
public:
	// シングルトン
	static inline PlayerManager* getInstance()
	{
		static PlayerManager s_instance;
		return &s_instance;
	}

	//-------------------------
	// メンバ関数
	//-------------------------
private:
	// コンストラクタ
	PlayerManager();

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// コピーコンストラクタを削除
	// これをしないと実体が複数作れてしまう
	PlayerManager(const PlayerManager& obj) = delete;

	// プログラム中に実体が一つしか存在しないという
	// シングルトンパターンを保証するために
	// 代入演算子をオーバーロードして削除
	PlayerManager& operator = (const PlayerManager& obj) = delete;

	// デストラクタ
	~PlayerManager();

public:
	// プレイヤーの生成関数
	void playerGenerate();

	// ポインタを貰う関数(ゲッター)
	inline Player* get()
	{
		Player* ret = nullptr;

		if (pPlayer != nullptr)
		{
			ret = pPlayer;
		}

		return ret;
	}

	
	// 終了関数
	void exit();

	//-------------------------
	// メンバ変数
	//-------------------------
private:
	// Playerクラスのポインタ
	Player* pPlayer;

};