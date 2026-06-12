#include "mapdata.h"
#include "Object.h"

//------------------------------------------------------------
//  初代マリオ 1-1: 簡易マップデータ初期化
//  - 可読性と変更性を優先し、まずは空(-1)で埋めた後に
//    必要なタイルを個別にセットします。
//  - マップの行/列は Const.h の MAP_ROW / MAP_COL を使用。
//------------------------------------------------------------

int stage1MapData[MAP_ROW][MAP_COL];

// 指定した行の、特定の列範囲を特定のブロックで埋める
void fillBlocks(int row, int startCol, int endCol, int blockType) {
    for (int c = startCol; c <= endCol; ++c) {
        stage1MapData[row][c] = blockType;
    }
}

// 土管を生成する（左下の列と、高さを指定）
// ※マリオの土管は幅2ブロックです
void createPipe(int startCol, int height) {
    for (int h = 0; h < height; ++h) {
        stage1MapData[MAP_ROW - 3 - h][startCol] = PIPE_BLOCK;
        stage1MapData[MAP_ROW - 3 - h][startCol + 1] = PIPE_BLOCK;
    }
}

// 右上がりの階段を生成する（左下の列と、幅/高さを指定）
void createStairsUp(int startCol, int size) {
    for (int i = 0; i < size; ++i) {
        for (int h = 0; h <= i; ++h) {
            stage1MapData[MAP_ROW - 3 - h][startCol + i] = HARD_BLOCK;
        }
    }
}

// 右下がりの階段を生成する（左下の列と、幅/高さを指定）
void createStairsDown(int startCol, int size) {
    for (int i = 0; i < size; ++i) {
        for (int h = 0; h < size - i; ++h) {
            stage1MapData[MAP_ROW - 3 - h][startCol + i] = HARD_BLOCK;
        }
    }
}

void initStage1Map()
{
    // まずはすべて空で初期化
    for (int r = 0; r < MAP_ROW; ++r) {
        for (int c = 0; c < MAP_COL; ++c) {
            stage1MapData[r][c] = -1; // 空セル（何もない）
        }
    }

    /*
    // 地面: 下2行を全面地面
    for (int c = 0; c < MAP_COL; ++c) {
        stage1MapData[MAP_ROW - 1][c] = GROUND_BLOCK;     // 一番下の行
        stage1MapData[MAP_ROW - 2][c] = GROUND_BLOCK;     // その上も地面とする
    }
    */

    // 地面を全面に敷き詰める（下2行）
    fillBlocks(MAP_ROW - 1, 0, MAP_COL - 1, GROUND_BLOCK);
    fillBlocks(MAP_ROW - 2, 0, MAP_COL - 1, GROUND_BLOCK);

    // 穴（落とし穴）を開ける
    fillBlocks(MAP_ROW - 1, 69, 70, -1);
    fillBlocks(MAP_ROW - 2, 69, 70, -1);

    fillBlocks(MAP_ROW - 1, 86, 88, -1);
    fillBlocks(MAP_ROW - 2, 86, 88, -1);

    fillBlocks(MAP_ROW - 1, 153, 154, -1);
    fillBlocks(MAP_ROW - 2, 153, 154, -1);

    // 下段 (地上から4ブロック上の高さ想定)
    int lowRow = MAP_ROW - 6; // 行番号9
    // 上段 (地上から8ブロック上の高さ想定)
    int highRow = MAP_ROW - 10; // 行番号5



    stage1MapData[lowRow][16] = QUESTION_BLOCK;

    stage1MapData[lowRow][20] = BRICK_BLOCK;
    stage1MapData[lowRow][21] = QUESTION_BLOCK;
    stage1MapData[lowRow][22] = BRICK_BLOCK;
    stage1MapData[lowRow][23] = QUESTION_BLOCK;
    stage1MapData[lowRow][24] = BRICK_BLOCK;
    stage1MapData[highRow][22] = QUESTION_BLOCK; // 上段のハテナ

    // --- 土管群 ---
    createPipe(28, 2);
    createPipe(38, 3);
    createPipe(46, 4);
    createPipe(57, 4);

    stage1MapData[lowRow - 1][64] = HIDDEN_BLOCK; // 上段のハテナ

    // =================================================================
    // 【エリア2】最初の穴 〜 2つ目の穴まで (列 71 〜 85)
    // =================================================================
    // --- 落とし穴手前のブロック群 ---
    stage1MapData[lowRow][77] = BRICK_BLOCK;
    stage1MapData[lowRow][78] = QUESTION_BLOCK;
    stage1MapData[lowRow][79] = BRICK_BLOCK;

    fillBlocks(highRow, 80, 87, BRICK_BLOCK); // 上段に長く続くレンガ

    // =================================================================
    // 【エリア3】2つ目の穴 〜 階段地帯まで (列 89 〜 133)
    // =================================================================
    fillBlocks(highRow, 91, 93, BRICK_BLOCK);
    stage1MapData[highRow][94] = QUESTION_BLOCK; // レンガ列の右端がハテナ


    stage1MapData[lowRow][94] = BRICK_BLOCK;

    fillBlocks(lowRow, 100, 101, BRICK_BLOCK);

    stage1MapData[lowRow][106] = QUESTION_BLOCK; 
    stage1MapData[lowRow][109] = QUESTION_BLOCK; 
    stage1MapData[highRow][109] = QUESTION_BLOCK;
    stage1MapData[lowRow][112] = QUESTION_BLOCK;

    stage1MapData[lowRow][118] = BRICK_BLOCK;

    // 3連レンガ
    fillBlocks(highRow, 121, 123, BRICK_BLOCK);
    
    stage1MapData[highRow][128] = BRICK_BLOCK;
    fillBlocks(highRow, 129, 130, QUESTION_BLOCK);
    fillBlocks(lowRow, 129, 130, BRICK_BLOCK);
    stage1MapData[highRow][131] = BRICK_BLOCK;

    /*
    // --- 後半の階段（HARD_BLOCK） ---
    createStairsUp(134, 4);    // 4段の登り階段
    createStairsDown(140, 4);  // 4段の下り階段

    createStairsUp(148, 5);    // 5段の登り階段
    createStairsDown(155, 4);  // 4段の下り階段 (穴の直後)

    createStairsUp(181, 8);    // ゴール前の大階段（8段）
    */
    // =================================================================
    // 【エリア4】階段・3つ目の穴地帯 (列 134 〜 162)
    // =================================================================
    // 最初のすれ違い階段 (4段)
    createStairsUp(134, 4);
    createStairsDown(140, 4);

    // 穴をまたぐ階段
    createStairsUp(148, 4);
    // 穴の手前の最高段 (高さ4マス分を縦に配置)
    for (int h = 0; h < 4; ++h) stage1MapData[MAP_ROW - 3 - h][152] = HARD_BLOCK;

    // --- ここに穴3 (153, 154) が挟まる ---

    // 穴の直後の最高段
    for (int h = 0; h < 4; ++h) stage1MapData[MAP_ROW - 3 - h][155] = HARD_BLOCK;
    createStairsDown(155, 4);


    // =================================================================
    // 【エリア5】終盤 〜 ゴールまで (列 163 〜 ラスト)
    // =================================================================
    createPipe(163, 2); // 終盤の土管

    // ゴール前最後のブロック群
    stage1MapData[lowRow][168] = BRICK_BLOCK;
    stage1MapData[lowRow][169] = BRICK_BLOCK;
    stage1MapData[lowRow][170] = QUESTION_BLOCK;
    stage1MapData[lowRow][171] = BRICK_BLOCK;

    createPipe(179, 2); // ゴール直前の土管

    // ゴール前の超巨大大階段 (8段)
    createStairsUp(181, 8);
    // 階段の右端壁（高さ8マス分）
    for (int h = 0; h < 8; ++h) stage1MapData[MAP_ROW - 3 - h][189] = HARD_BLOCK;
   
    // ゴールポールの土台 (1マスだけぽつんとある固いブロック)
    stage1MapData[MAP_ROW - 3][198] = HARD_BLOCK;

}