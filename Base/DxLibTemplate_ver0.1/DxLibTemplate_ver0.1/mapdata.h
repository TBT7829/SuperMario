#pragma once

#include "Const.h"

//! @brief ステージ1-1 用のマップデータ（MAP_ROW x MAP_COL）
//! @note 値の意味は MapManager::createStage の switch に合わせること。
//!   - -1 : 空（何も置かない）
//!   - 0  : 地面 (GROUND)
//!   - 1  : レンガブロック (BRICK)
//!   - 2  : ハテナブロック (QUESTION)
//!   - 3  : 空ブロック (EMPTY)
//!   - 4  : 隠しブロック (HIDDEN)
//!   - 5  : コインブロック (COIN_BLOCK)
//!   - 6  : 硬いブロック (HARD_BLOCK)
//!   - 7  : 土管 (PIPE)
//!   - 8  : クリボー (GOOMBA / 敵)
extern int stage1MapData[MAP_ROW][MAP_COL];

//! @brief variable.cpp 内で全ステージマップを初期化する関数
//! @note main や Stage::init で一度だけ呼んでください
void initStage1Map();
