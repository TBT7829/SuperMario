#include "CollisionManager.h"

// デバッグ用
#include "MapManager.h"

#include "PlayerManager.h"
#include "EnemyManager.h"
#include "BlockManager.h"

#include "Object.h"
#include "Player.h"
#include "Block.h"

#include "Const.h"
#include "HitFunc.h"

//---------------------------------------------------------------------------------
//	衝突判定の更新
//---------------------------------------------------------------------------------
void CollisionManager::updateCollision()
{
	PlayerManager* pPM = PlayerManager::getInstance();
	BlockManager* pBM = BlockManager::getInstance();
	MapManager* pMM = MapManager::getInstance();
	Player* pPlayer = pPM->get();

	// 挙動確認用のベース、プレイヤーと地面のみでの当たり判定
	for (int b = 0; b < BLOCK_MAX; b++) {
		Block* pBlock = pBM->pBlockArray[b];
		if (pBlock == nullptr || !pBlock->isSolid) continue;

		switch (pBlock->getObjectType()) {
		case GROUND_BLOCK:
			// 四角形同士が当たっているかチェック
			bool isHit = CheckBoxHit(pPlayer->pos, pPlayer->size, pBlock->pos, pBlock->size);

			if (isHit) {
				// 床の上に立たせる押し戻し処理
				// マリオの足元が、ブロックの頭（Y座標）より少し下に入り込んでいたら「上から踏んだ」とみなす
				if (pPlayer->pos.y + pPlayer->size.y > pBlock->pos.y) {

					// 1. マリオをブロックのすぐ上にピッタリ配置する
					float collectY = pBlock->pos.y - pPlayer->size.y;
					pPlayer->pos.y = collectY;

					// 2. 下向きの落下速度を 0 にして、落下のエネルギーを止める
					pPlayer->movSpeed.y = 0.0f;

					pPlayer->onLand(pBlock->pos.y);
				}
			}
			break;
		}

		

		
	}
	
}
