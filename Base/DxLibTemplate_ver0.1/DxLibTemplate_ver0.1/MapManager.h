#pragma once

#include "Const.h"

//! @brief マップデータを管理するマネージャークラス
//! ステージのマップ配列とサイズを一括管理し、デバッグ描画機能を提供する
class MapManager final
{
private:

	//! @brief シングルトン用の記述
	MapManager();

	//! @brief コピーコンストラクタ削除
	MapManager(const MapManager&) = delete;

	//! @brief 代入演算子削除
	MapManager& operator=(const MapManager&) = delete;

	//! @brief デストラクタ
	~MapManager();

public:
  
	//! @brief シングルトン
	//! @return 自分自身のただ一つの実体の参照
	inline static MapManager* getInstance()
	{
		static MapManager s_instance;
		return &s_instance;
	}

	//! @brief ステージ番号に応じたマップを配列にセットする
	//! @param mapData マップデータの2次元配列
	//! @param stageWidth ステージの幅
	void createStage(int mapData[MAP_ROW][MAP_COL], int stageWidth);

	//! @brief デバッグ用マップ描画処理
	void drawDebugMap();

   
	//! @brief マップの2次元配列
	int mapArray[MAP_ROW][MAP_COL];

	//! @brief 現在のステージの幅
	int currentStageWidth;

};