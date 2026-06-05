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
#include<DxLib.h>


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
			// detectCollision を使って当たり方向を取得
			CollisionInfo ci = detectCollision(pPlayer->pos, pPlayer->size, pBlock->pos, pBlock->size);

			// 当たっているかどうか
			if (ci.isHit) {
				// 床の上に立たせる押し戻し処理
				if (ci.side == TOP) {
					// マリオをブロックのすぐ上にピッタリ配置する
					float collectY = pBlock->pos.y - pPlayer->size.y;
					pPlayer->pos.y = collectY;
					// 下向きの落下速度を 0 にして、落下のエネルギーを止める
					pPlayer->movSpeed.y = 0.0f;
					// プレイヤーの状態を「地面に接地している状態」にする
					pPlayer->onLand(pBlock->pos.y);
				}
				else {
					// 将来的にLEFT/RIGHT/BOTTOMなどで追加したい処理(横方向の押し戻しや頭打ち)があるならここに追加して！！！
					// 現時点ではプレイヤーがブロックに食い込んだ場合、最小分離ベクトルに従って位置を補正してます
					if (ci.side == LEFT || ci.side == RIGHT) {
						pPlayer->pos.x += ci.penetration.x;
					}
					else if (ci.side == BOTTOM) {
						// 頭打ち時の位置補正
						pPlayer->pos.y += ci.penetration.y;
						// 必要なら上方向への速度のキャンセルとかをここで行ってもいい
					}
				}
			}
			break;
		}

		

		
	}
	
}


//---------------------------------------------------------------------------------
//	矩形同士の衝突検出(相対での判定)
//	return: CollisionInfo
//	概要：
//	   overlapX, overlapY を計算し、どちらの重なりが小さいかで主方向を決定
//	   penetrationは「Aを押し戻す最小ベクトル」を返す(y増加は下方向の座標系を想定したもの)
//	   拡張性を持たせるためCollisionSideとCollisionInfo構造体を使用
//---------------------------------------------------------------------------------
CollisionManager::CollisionInfo CollisionManager::detectCollision(const Float2& pos1, const Float2& size1, const Float2& pos2, const Float2& size2) const
{
	CollisionInfo info;

	// A: 一個目のオブジェクト
	// B: 二個目のオブジェクト

	// Aの左、上、右、下の座標
	float left1 = pos1.x;
	float top1 = pos1.y;
	float right1 = pos1.x + size1.x;
	float bottom1 = pos1.y + size1.y;

	// Bの左、上、右、下の座標
	float left2 = pos2.x;
	float top2 = pos2.y;
	float right2 = pos2.x + size2.x;
	float bottom2 = pos2.y + size2.y;

	// 重なり幅
	float overlapX = min(right1, right2) - max(left1, left2);
	float overlapY = min(bottom1, bottom2) - max(top1, top2);

	// 重なり幅が正の値であれば衝突している
	if (overlapX <= 0.0f || overlapY <= 0.0f) {
		// 衝突なし
		return info;
	}

	// 上で弾かれていないので、衝突していると判断
	info.isHit = true;

	// 中心位置を比較してAがBのどの側にいるか判定
	float centerX1 = pos1.x + size1.x * 0.5f;
	float centerY1 = pos1.y + size1.y * 0.5f;
	float centerX2 = pos2.x + size2.x * 0.5f;
	float centerY2 = pos2.y + size2.y * 0.5f;

	// より小さい重なり方向で主な衝突面を決める
	// 例えば、重なり幅が水平方向の方が小さい場合は、水平方向の衝突とみなす
	if (overlapX < overlapY) {
		// 水平方向の衝突
		if (centerX1 < centerX2) {
			info.side = LEFT;             // AはBの左側から入っている
			info.penetration.Set(-overlapX, 0.0f); // Aを左へ押し戻す
		}
		else {
			info.side = RIGHT;            // AはBの右側から入っている
			info.penetration.Set(overlapX, 0.0f);  // Aを右へ押し戻す
		}
	}
	else {
		// 垂直方向の衝突
		if (centerY1 < centerY2) {
			info.side = TOP;              // AはBの上側から入っている
			info.penetration.Set(0.0f, -overlapY); // Aを上へ押し戻す
		}
		else {
			info.side = BOTTOM;           // AはBの下側から入っている
			info.penetration.Set(0.0f, overlapY);  // Aを下へ押し戻す
		}
	}

	return info;
}