#include<DxLib.h>
#include "RenderableManager.h"
#include "Renderable.h"
#include"const.h"



RenderableManager::RenderableManager()
{
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		pRenderableArray[i] = NULL;
	}
}

void RenderableManager::fillGap()
{
	// 表示物の配列の空き部分を詰める(並び替えをバグらせず、スムーズに行うため)
	
	int head = 0;
	int tail = RENDERABLE_ARRAY_LENGTH - 1;

	bool searchLoopEnd = false;
	while (searchLoopEnd == false)
	{
		// 現在headが参照している場所はNULLか？
		Renderable** ppHeadData = &pRenderableArray[head];
		if (*ppHeadData == NULL)
		{
			// 現在の場所がNULLなので、後ろからデータを詰める処理を行う。
			while (1)
			{
				// 現在のtailとheadが同じ場所を見ているか
				if (tail == head)
				{
					// 空きをすべて探し終えたので、ループを抜ける
					searchLoopEnd = true;
					break;
				}

				// 現在tailが見ている場所にデータがあるか
				Renderable** ppTailData = &pRenderableArray[tail];
				if (*ppTailData == NULL)
				{
					// 今tailが見ている場所にデータはないので
					// tailの位置を進めて比較を続ける
					tail--;
					continue;
				}

				// 現在のtailの場所にデータが見つかったので、
				// 現在のheadの場所にデータを移動する
				*ppHeadData = *ppTailData;
				*ppTailData = NULL;
				// headに次のNULLを探す処理に戻ってもらうためにループを抜ける
				break;
			}
		}


		// headを次の要素に進める
		head++;
	}
}

void RenderableManager::sort()
{
	// 表示物の並び替え(小さい順: 左が小さく、右が大きくなるように並び替え)
	
	// まずはデータの個数を確認(並び替え処理の回数を決める為)
	int dataNum = 0;
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		if (pRenderableArray[i] != NULL)
		{
			dataNum++;
		}
	}

	// データの個数 - 1回並び替えの処理を行う
	int sortLoopNum = dataNum - 1;
	while (1)
	{
		// 並び替えが発生した回数
		int flipCount = 0;
		for (int i = 0; i < sortLoopNum; i++)
		{
			// 従来の処理
			/*
			Renderable* pLeft = pRenderableArray[i];
			Renderable* pRight = pRenderableArray[i + 1];

			// 右(pRight)の方が優先順位が小さければ左右の入れ替えを行う
			if ( pRight->getPriority() < pLeft->getPriority() )
			{
				// 右のほうが優先順位が小さかったので左右を入れ替える
				Renderable* pTmp = pLeft;
				// 左に右のデータを保存
				pRenderableArray[i] = pRight;
				// 右に、先ほど保存しておいた左のデータを保存
				pRenderableArray[i + 1] = pTmp;

				flipCount++;
			}
			*/

			// ダブルポインタ(ポインタのポインタ)を使った処理
			// 要素へのポインタ
			Renderable** ppLeft = &pRenderableArray[i];
			Renderable** ppRight = &pRenderableArray[i + 1];

			// 右(pRight)の方が優先順位が小さければ左右の入れ替えを行う
			if ((*ppRight)->getPriority() < (*ppLeft)->getPriority())
			{
				// 右のほうが優先順位が小さかったので左右を入れ替える
				Renderable* pTmp = *ppLeft;
				// 左のデータが入っていた要素に右のデータが入っていた要素の中身を保存
				*ppLeft = *ppRight;
				// 右に、先ほど保存しておいた左のデータを保存
				*ppRight = pTmp;

				flipCount++;
			}

		}

		// 並び替えが発生したかをチェック
		if (flipCount <= 0)
		{
			// 並び替えが発生しなかったということは、
			// これ以上並び変える必要はないということなので、
			// ループを抜ける
			break;
		}
	}
}

bool RenderableManager::add(Renderable* pObj)
{
	bool ret = false;
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		// 現在参照している要素は空いているか
		if (pRenderableArray[i] == NULL)
		{
			// 要素は空いていたので、ここに引数に渡されたポインタを保存
			pRenderableArray[i] = pObj;
			ret = true;
			break;
		}
	}

	return ret;
}

void RenderableManager::remove(Renderable* pObj)
{
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		// 現在の要素に入っているポインタが、引数に指定されたものと同じか
		if (pRenderableArray[i] == pObj)
		{
			// 現在の要素にNULLを入れて、オブジェクトの登録を解除する
			pRenderableArray[i] = NULL;
		}
	}
}

void RenderableManager::renderAll()
{
	// 隙間を詰める
	fillGap();
	// 並び替えを行う
	sort();

	// 表示
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		Renderable* pRenderable = pRenderableArray[i];
		if (pRenderable == NULL)
		{
			continue;
		}

		if (pRenderable)
		{
			pRenderable->preRender();
			pRenderable->render();
			pRenderable->postRender();
		}

	}

#ifdef DBG_PRINT_RENDERABLE_DATA
	for (int i = 0; i < RENDERABLE_ARRAY_LENGTH; i++)
	{
		printfDx("[%d]: %llu\n", i, pRenderableArray[i]);
	}
#endif

}
