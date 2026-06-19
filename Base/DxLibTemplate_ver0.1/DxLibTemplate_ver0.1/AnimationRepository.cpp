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

	//=============================================================
	// マリオのアニメーションデータの構築 (AOT_MARIO)
	//=============================================================
	AnimationDataSet* pAds = getAds(AOT_MARIO);
    if (pAds == NULL)
    {
        printfDx("AnimationRepository::initAnimationRepository - getAds returned NULL\n");
        return;
    }

	// -------------------------------------------------------------
	// 【チビマリオ (LOW)】 mini_mario.png (1コマ16x16)
	// -------------------------------------------------------------
    int imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_MINI_MARIO);
    if (imageHandle == -1)
    {
        printfDx("AnimationRepository::initAnimationRepository - IMAGE_MINI_MARIO not loaded\n");
    }

	// 待機 (0コマ目)
    AnimationData* pAd = pAds->getAnimationData(A_MARIO_LOW_IDLE);
    if (pAd == NULL) { printfDx("initAnimationRepository: pAd NULL for A_MARIO_LOW_IDLE\n"); }
    else {
        pAd->pushSetImage(DerivationGraph(2, 0, 14, 16, imageHandle));
        pAd->pushSetWait(9999);
        pAd->pushEnd();
    }

	// 歩き (1, 2, 3コマ目をループ)
	pAd = pAds->getAnimationData(A_MARIO_LOW_WALK);
	pAd->pushSetImage(DerivationGraph(16, 0, 16, 16, imageHandle));
	pAd->pushSetWait(6);
	pAd->pushSetImage(DerivationGraph(32, 0, 16, 16, imageHandle));
	pAd->pushSetWait(6);
	pAd->pushSetImage(DerivationGraph(48, 0, 16, 16, imageHandle));
	pAd->pushSetWait(6);
	pAd->pushJump(0);

	// ジャンプ (5コマ目)
	pAd = pAds->getAnimationData(A_MARIO_LOW_JUMP);
	pAd->pushSetImage(DerivationGraph(80, 0, 16, 16, imageHandle));
	pAd->pushSetWait(9999);
	pAd->pushEnd();

	// ブレーキ (4コマ目)
	pAd = pAds->getAnimationData(A_MARIO_LOW_BRAKE);
	pAd->pushSetImage(DerivationGraph(64, 0, 16, 16, imageHandle));
	pAd->pushSetWait(9999);
	pAd->pushEnd();

	// -------------------------------------------------------------
	// 【デカマリオ (TALL)】 big_mario.png (1コマ16x32)
	// -------------------------------------------------------------
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_BIG_MARIO);

	// 待機
	pAd = pAds->getAnimationData(A_MARIO_TALL_IDLE);
	pAd->pushSetImage(DerivationGraph(0, 0, 16, 32, imageHandle));
	pAd->pushSetWait(9999);
	pAd->pushEnd();

	// 歩き
	pAd = pAds->getAnimationData(A_MARIO_TALL_WALK);
	pAd->pushSetImage(DerivationGraph(16, 0, 16, 32, imageHandle));
	pAd->pushSetWait(6);
	pAd->pushSetImage(DerivationGraph(32, 0, 16, 32, imageHandle));
	pAd->pushSetWait(6);
	pAd->pushSetImage(DerivationGraph(48, 0, 16, 32, imageHandle));
	pAd->pushSetWait(6);
	pAd->pushJump(0);

	// ジャンプ
	pAd = pAds->getAnimationData(A_MARIO_TALL_JUMP);
	pAd->pushSetImage(DerivationGraph(80, 0, 16, 32, imageHandle));
	pAd->pushSetWait(9999);
	pAd->pushEnd();

	// ブレーキ
	pAd = pAds->getAnimationData(A_MARIO_TALL_BRAKE);
	pAd->pushSetImage(DerivationGraph(64, 0, 16, 32, imageHandle));
	pAd->pushSetWait(9999);
	pAd->pushEnd();

	// しゃがみ (6コマ目)
	pAd = pAds->getAnimationData(A_MARIO_TALL_SNEAK);
	pAd->pushSetImage(DerivationGraph(96, 0, 16, 32, imageHandle));
	pAd->pushSetWait(9999);
	pAd->pushEnd();

	// -------------------------------------------------------------
	// 【ファイアマリオ (FIRE)】 各専用単体ファイル
	// -------------------------------------------------------------

	// 待機
	pAd = pAds->getAnimationData(A_MARIO_FIRE_IDLE);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_FIRE_MARIO_STOP));
	pAd->pushSetWait(9999);
	pAd->pushEnd();

	// 歩き
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_FIRE_MARIO_WALK);
	pAd = pAds->getAnimationData(A_MARIO_FIRE_WALK);
	pAd->pushSetImage(DerivationGraph(0, 0, 16, 32, imageHandle));
	pAd->pushSetWait(6);
	pAd->pushSetImage(DerivationGraph(16, 0, 16, 32, imageHandle));
	pAd->pushSetWait(6);
	pAd->pushSetImage(DerivationGraph(32, 0, 16, 32, imageHandle));
	pAd->pushSetWait(6);
	pAd->pushJump(0);

	// ジャンプ
	pAd = pAds->getAnimationData(A_MARIO_FIRE_JUMP);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_FIRE_MARIO_JUMP));
	pAd->pushSetWait(9999);
	pAd->pushEnd();

	// ブレーキ
	pAd = pAds->getAnimationData(A_MARIO_FIRE_BRAKE);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_FIRE_MARIO_DASH));
	pAd->pushSetWait(9999);
	pAd->pushEnd();

	// しゃがみ
	pAd = pAds->getAnimationData(A_MARIO_FIRE_SNEAK);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_FIRE_MARIO_DOWN));
	pAd->pushSetWait(9999);
	pAd->pushEnd();
}

AnimationDataSet* AnimationRepository::getAds(int AnimobjectType)
{
    // 引数が範囲外の場合は NULL を返す
    if (AnimobjectType < 0 || AnimobjectType >= AOT_NUM)
    {
        return NULL;
    }

    return &ads[AnimobjectType];
}
