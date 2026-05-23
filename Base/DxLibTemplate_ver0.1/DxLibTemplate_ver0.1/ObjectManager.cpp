#include "ObjectManager.h"
#include "Object.h"

#include<DxLib.h>

//---------------------------------------------------------
// ObjectManagerの処理
//---------------------------------------------------------


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
ObjectManager::ObjectManager()
{
	// 配列の初期化
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		pObjectArray[i] = nullptr;
	}

	// 登録されているObjectの数は0から
	objectNum = 0;

	// 生成するIDの開始点の設定
	lastId = GENERATE_START_ID;
}


//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
ObjectManager::~ObjectManager()
{
	// 全オブジェクトの削除
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		// ダブルポインタ(ポインタのポインタ)
		Object** ppElem = &pObjectArray[i];
		Object* pObject = *ppElem;

		// nullptrじゃなければ何か入っているので
		if (pObject != nullptr)
		{
			// deleteしてnullptrを代入
			delete pObject;
			*ppElem = nullptr;
		}
	}
}


//---------------------------------------------------------
// マネージャにオブジェクトを登録する関数
//---------------------------------------------------------
bool ObjectManager::add(Object* pObject)
{
	// すでに配列がいっぱいならもう登録はしない
	if (OBJECT_MAX <= objectNum)
	{
		return false;
	}

	// 同じIDのオブジェクトが存在しないかチェック
	// nullptrじゃない、つまり見つかったら既に存在するので弾く
	if (search(pObject->getObjectId()) != nullptr)
	{
		return false;
	}

	// 配列の空きを検索
	Object** ppElem = nullptr;
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		Object** ppCurElem = &pObjectArray[i];


		if (*ppCurElem == nullptr)
		{
			// 今の要素数の状態を登録
			ppElem = ppCurElem;
			break;
		}
	}

	// 空きが見つからなかったので何もせず抜ける
	if (ppElem == nullptr)
	{
		return false;
	}

	// 空きが見つかったので、貰ったオブジェクトを登録
	*ppElem = pObject;

	// 登録オブジェクト数をカウントアップ
	objectNum++;



	return true;
}

//---------------------------------------------------------
// オブジェクト
//---------------------------------------------------------
bool ObjectManager::kill(int id)
{
	// 削除対象のオブジェクトを検索
	Object* pObject = search(id);
	// 削除対象が見つからなかったなら何もせず抜ける
	if (pObject == nullptr)
	{
		return false;
	}

	// 削除対象を死亡状態にする
	pObject->deactivate();



	return true;
}

//---------------------------------------------------------
// 更新関数
//---------------------------------------------------------
void ObjectManager::updateAll()
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		// 現在参照している要素のポインタを取得
		Object** ppElem = &pObjectArray[i];
		// 現在参照している要素に入っているオブジェクトのポインタ
		Object* pObject = *ppElem;

		// 現在参照されているオブジェクトがnullptrなら
		if (pObject == nullptr)
		{
			continue;
		}

		// 今の状態を取得
		int curState = pObject->getObjectState();


		// オブジェクト死亡状態か
		if (curState == Object::OBJECT_STATE::INACTIVE)
		{
			// 死んでいるならオブジェクトを削除
			delete pObject;
			// 現在参照している要素にnullptrを設定
			*ppElem = nullptr;
			// オブジェクトの登録数をカウントダウン
			objectNum--;

			// 現在参照しているオブジェクトはもう死んでこれ以上やることがないので、
			// 次の要素に進む
			continue;
		}

		// オブジェクト登録後初の実行の更新なら専用の更新処理を呼び出す
		if (curState == Object::OBJECT_STATE::READY)
		{
			pObject->activate();
		}

		// 現在参照しているオブジェクトの更新処理を行う
		pObject->update();
	}


}

//---------------------------------------------------------
// 描画関数
//---------------------------------------------------------
void ObjectManager::renderAll()
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		// 現在参照している要素のポインタを取得
		Object* pObject = pObjectArray[i];

		// 現在参照しているオブジェクトがnullptrなら
		if (pObject == nullptr)
		{
			continue;
		}

		// 状態を取得
		int state = pObject->getObjectState();

		// 現在のオブジェクトの状態が実行中でなければ表示処理は実行しない
		if (state != Object::OBJECT_STATE::ACTIVE) //|| state == Object::OBJECT_STATE::PAUSE) 
		{
			// 今回の要素は中断し配列の検索を続行
			continue;
		}

		// 現在参照しているオブジェクトの表示処理を行う
		pObject->render();

	}
}

//---------------------------------------------------------
// 渡されたIDのオブジェクトを探す
//---------------------------------------------------------
Object* ObjectManager::search(int id)
{
	Object* ret = nullptr;

	//	渡されたIDが異常な値(0未満)だった場合
	if (id < 0)
	{
		// ここでNULLを返す
		return ret;
	}

	// 配列を探す
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		// 現在参照している要素のポインタを取得
		Object* pObject = pObjectArray[i];

		// objectのポインタ配列から現在の要素を取ってきて
		// もし中身がnullptrだったら
		if (pObject == nullptr)
		{
			// 今回の要素は中断し配列の検索を続行
			continue;
		}

		// 指定されたIDが存在すれば
		if (pObject->getObjectId() == id)
		{
			// そのオブジェクトを返す
			ret = pObject;
			break;
		}
	}

	return ret;
}

//---------------------------------------------------------
// オブジェクトマネージャの情報を表示
//---------------------------------------------------------
void ObjectManager::dump()
{
	for (int i = 0; i < OBJECT_MAX; i++)
	{
		// デバッグ用情報表示
		int col = i / 24;
		int row = i % 24;


		DrawFormatString(col * 180, row * 24, 0xFFFFFF, "[%d]: %llu\n", i, pObjectArray[i]);
	}
}