#pragma once

#include"AnimationDataSet.h"
#include"ImageManager.h"

class AnimationRepository
{
private :
	AnimationRepository();
	AnimationRepository(const AnimationRepository& other) = delete;
	AnimationRepository& operator = (const AnimationRepository& other) = delete;

public :
	static AnimationRepository* getInstance();

	static enum AnimationObjectType
	{
		AOT_MARIO,

		AOT_QUESTIONBLOCK,

		AOT_GOOMBA,

		AOT_NUM,
	};

	// マリオ用のアニメーション定義を追加
	static enum MarioAnim
	{
		A_MARIO_LOW_IDLE,
		A_MARIO_LOW_WALK,
		A_MARIO_LOW_JUMP,
		A_MARIO_LOW_BRAKE,

		A_MARIO_TALL_IDLE,
		A_MARIO_TALL_WALK,
		A_MARIO_TALL_JUMP,
		A_MARIO_TALL_BRAKE,
		A_MARIO_TALL_SNEAK,

		A_MARIO_FIRE_IDLE,
		A_MARIO_FIRE_WALK,
		A_MARIO_FIRE_JUMP,
		A_MARIO_FIRE_BRAKE,
		A_MARIO_FIRE_SNEAK,
	};

	

private :
	AnimationDataSet ads[AOT_NUM];

public :
	void initAnimationRepository();
	AnimationDataSet* getAds(int AnimobjectType);

};