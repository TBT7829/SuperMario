#pragma once

#include"const.h"

//! @brief 音声情報
struct SoundInfo
{

	int soundHandle;

	const char* soundPath;
};

//! @brief 音声情報を一括管理するマネージャークラス
class SoundManager
{
private:
	//! @brief コンストラクタ
	SoundManager();

	SoundManager& operator = (SoundManager& other) = delete;
	SoundManager(const SoundManager& other) = delete;

	//! @brief 画像情報を保存する配列
	SoundInfo soundInfoArray[SOUND_INFO_LENGTH];

public:
	enum SOUND_NAME
	{
		SOUND_STAGE = 0,
	};

	//! @brief シングルトン
	//! @return 自分自身のただ一つの実体のポインタ
	inline static SoundManager* getInstance()
	{
		static SoundManager manager;
		return &manager;
	}

	//! @brief 初期化処理
	void initSoundManager();

	//! @brief 音声マネージャーに管理してほしい音声ファイルの場所(ファイル名)を設定
	//! @param soundId 
	//! @param soundPath 
	//! @return 登録できた場合にはtrue
	//! @return 見てはいけない番号などが渡された場合には登録せずにfalse
	bool setSoundInfo(int soundId, const char* soundPath);

	//! @brief 画像マネージャーに登録されたファイル名をもとに、全画像を読み込む
	void loadSoundAll();

	//! @brief 音声IDからDrawGraph等で必要な音声識別番号を取得
	//! @param soundId 
	//! @return 指定されたIDの音声を見つけたらその音声の識別番号
	//! @return 読み込めなければ-1
	int getSoundHandle(int soundId);

	//! @brief 全画像の削除(メモリからの解放)と、画像ファイルパスの無力化
	void clearSoundManager();

	//! @brief 音量を調節する
	//! @param volume 
	void setSoundVolume(int volume);
};

