#ifndef __RENDERABLE_MANAGER_H__
#define __RENDERABLE_MANAGER_H__

class Renderable;

// 表示物管理クラス
// このクラスは表示物のポインタを内部で持ち、
// 表示優先順に並び替えて表示する機能を持つ。
 
// ただ、TaskManagerのようにポインタの管理だけでなく、
// メモリの開放まで行うわけではないので注意
class RenderableManager final
{
//-------------------------
// 定数
//-------------------------
public:
	const static int RENDERABLE_ARRAY_LENGTH = 16;

//-------------------------
// 静的メンバ関数
//-------------------------
public:
	// シングルトン
	static inline RenderableManager* getInstance()
	{
		static RenderableManager s_instance;
		return &s_instance;
	}

//-------------------------
// メンバ関数
//-------------------------
private:
	// コンストラクタ
	RenderableManager();
	// コピーコンストラクタを削除
	RenderableManager(const RenderableManager& obj) = delete;
	// 代入演算子を削除
	void operator = (const RenderableManager& obj) = delete;

	// 所持する表示物配列の空きを詰める関数
	void fillGap();

	// 描画優先順位順に並べ替えを行う関数
	void sort();

public:
	// 保持する配列に表示物を登録する関数
	// 表示物の登録
	bool add(Renderable* pObj);

	// 保持する配列から表示物を除去する関数
	// 表示物の登録解除
	void remove(Renderable* pObj);

	// 登録された全表示物を描画する関数
	void renderAll();


//-------------------------
// メンバ変数
//-------------------------
private:
	// Renderableクラスを継承した表示物を保持する配列
	Renderable* pRenderableArray[RENDERABLE_ARRAY_LENGTH];

};


#endif