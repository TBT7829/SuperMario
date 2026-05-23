#pragma once



//! @brief カウントアップを更新関数でするタイマークラス
struct Timer
{
public:
	enum TIMER_STATE {
		STOP = 0,
		ACTIVE,
	};
//-------------------------
// メンバ関数
//-------------------------
public:
	//! @brief スタート処理
	//! @param max 
	void start(int max);

	//! @brief 更新処理
	void update();

	//! @brief タイマーをどこまで数えるかを指定し、現在の秒数を0にして停止させる
	//! @param max 
	void setMaxTimeStop(int max);

	//! @brief タイマーのカウントが終わっているかを返す関数
	//! @return 終わっていればtrue
	//! @return 終わっていなければfalse
	inline bool isOver()
	{
		return isFinish;
	}

	//! @brief 今のカウントを取得する関数
	//! @return 現在のタイマーの秒数
	inline int getCount()
	{
		return myTimerCount;
	}

//-------------------------
// メンバ変数
//-------------------------
private:
	//! @brief 今のカウントを保持する変数
	int myTimerCount;
	//! @brief 何フレームまでカウントするかを保持する変数
	int timerCountMax;
	//! @brief 終わっているかどうか
	int isFinish;
	//! @brief タイマーの状態
	int state;
};

