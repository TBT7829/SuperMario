#include"AnimationRepository.h"
#include<DxLib.h>


AnimationRepository::AnimationRepository()
{

}

AnimationRepository* AnimationRepository::getInstance()
{
	static AnimationRepository instance;
	return &instance;
}

void AnimationRepository::initAnimationRepository()
{
	ImageManager* pImageManager = ImageManager::getInstance();

	//AnimationDataSet* pAds = getAds(AOT_PLAYER_LEFT);
	//AnimationData* pAd = pAds->getAnimationData(A_PLAYER_LEFT_IDLE);


}

AnimationDataSet* AnimationRepository::getAds(int AnimobjectType)
{
	if (AOT_NUM < AnimobjectType)
	{
		return NULL;
	}
	return &ads[AnimobjectType];
}
