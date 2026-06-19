#pragma once

#include "AnimationData.h"

// 複数のAnimationDataを持ち、複数のアニメーションを切り替えらえるようにするためのクラス
class AnimationDataSet
{
private:
    // AnimationRepository で定義されるアニメーション番号を格納できるように
    // 十分な数を確保しておく。マリオ用で14個程度使うため余裕を持たせて16に設定。
    static const int ANIMATION_DATA_NUM = 16;

public:
	// 指定した番号のアニメーション情報を取得
	AnimationData* getAnimationData(int no);

	// 指定されたアニメーション番号が、有効な物かチェック
	// 引数に番号(no)をもらう
	bool isAnimationDataNoValid(int no);


private:
	AnimationData animationDataArray[ANIMATION_DATA_NUM];

};


