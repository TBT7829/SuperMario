#pragma once

#include"const.h"

//! @brief 画像情報
struct ImageInfo
{
	// DrawGraph等で使用する実際の画像番号
	int imageHandle;
	// 画像ファイルの場所(フォルダ名・ファイル名を含む)
	const char* imagePath;
};


//! @brief 画像情報を一括管理するマネージャークラス
class ImageManager
{
private:

	//! @brief コンストラクタ
	ImageManager();

	ImageManager& operator = (ImageManager& other) = delete;
	ImageManager(const ImageManager& other) = delete;

	//! @brief 画像情報を保存する配列
	ImageInfo imageInfoArray[IMAGE_INFO_LENGTH];

public:
	enum IMAGE_NAME
	{
		IMAGE_MINI_MARIO,
		IMAGE_BIG_MARIO,
		IMAGE_FIRE_MARIO_STOP,
		IMAGE_FIRE_MARIO_WALK,
		IMAGE_FIRE_MARIO_JUMP,
		IMAGE_FIRE_MARIO_DOWN,
		IMAGE_FIRE_MARIO_DASH,
		IMAGE_FIRE_MARIO_ATTACK,

		IMAGE_STAGE_BG_11,
		IMAGE_GROUND_BLOCK_11,
		IMAGE_HARD_BLOCK,
		IMAGE_HIDDEN_BLOCK,
		IMAGE_BRICK_BLOCK,
		IMAGE_EMPTY_BLOCK_01,

		IMAGE_PIPE_LOW,
		IMAGE_PIPE_MIDDLE,
		IMAGE_PIPE_HIGH,

		IMAGE_SUPERMUSHROOM,

		IMAGE_MAX,
	};

	//! @brief シングルトン
	//! @return 自分自身のただ一つの実体のポインタ
	inline static ImageManager* getInstance()
	{
		static ImageManager manager;
		return &manager;
	}

	//! @brief 初期化関数
	void initImageManager();

	//! @brief 画像マネージャーに管理してほしい画像ファイルの場所(ファイル名)を設定
	//! @param imageId 
	//! @param imagePath 
	//! @return 登録できた場合にはtrue
	//! @return 見てはいけない番号などが渡された場合には登録せずにfalse
	bool setImageInfo(int imageId, const char* imagePath);

	//! @brief 画像マネージャーに登録されたファイル名をもとに、全画像を読み込む
	void loadImageAll();

	//! @brief 画像IDからDrawGraph等で必要な画像識別番号を取得
	//! @param imageId 
	//! @return 指定されたIDの画像を見つけたらその画像の識別番号
	//! @return 読み込めなければ-1
	int getImageHandle(int imageId);

	//! @brief 全画像の削除(メモリからの解放)と、画像ファイルパスの無力化
	void clearImageManager();
};
