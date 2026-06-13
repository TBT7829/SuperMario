#include "Pipe.h"
#include "Camera.h"
#include <DxLib.h>

//---------------------------------------------------------------------------------
//	Pipe の実装（enterable フラグと pipeId の扱いを明確に）
//---------------------------------------------------------------------------------

//! @brief コンストラクタ
Pipe::Pipe(int _id, Float2 _start, Float2 _size, Float2 _exitPos, int _pipeId, bool _enterable)
	: Block(_id, OBJECT_TYPE::PIPE_BLOCK, _start, _size) // ブロックのカテゴリとして地形扱い
{
	exitPos = _exitPos;
	pipeId = _pipeId;
	enterable = _enterable; // プレイヤーが入れるかどうか
	isSolid = true;		//! 土管は足場になる（上からは固い）
}

//! @brief デストラクタ
Pipe::~Pipe()
{
}

//! @brief 更新処理
void Pipe::update()
{
	// 基本静止。将来パックンフラワーやアニメがあればここで処理
}

//! @brief 描画処理
void Pipe::render()
{
	// カメラオフセットを適用
	float drawX = Camera::getInstance().worldToScreenX(pos.x);
	int drawY = (int)pos.y;

	int x1 = (int)drawX;
	int y1 = (int)drawY;
	int x2 = (int)(drawX + size.x);
	int y2 = (int)(drawY + size.y);

	// 左上と右下の座標を計算（どちらが左上かは x1/x2, y1/y2 の大小関係で決まる）
	// DrawBox は左上(x1, y1) と右下(x2, y2) を指定するが、x1/x2, y1/y2 のどちらが左上かは保証されないので、min/max で正しい座標を計算する
	// (DrawBox / DrawExtendGraph は左上, 右下)
	//int left = min(x1, x2);
	//int top = min(y1, y2);
	//int right = max(x1, x2);
	//int bottom = max(y1, y2);
	int left = x1;
	int top = y1;
	int right = x2;
	int bottom = y2;



	// 単純な矩形塗りつぶし（既存の見た目）
	DrawBox(left, top, right, bottom, GetColor(34, 139, 34), TRUE);

	// 内側を塗る（見た目）
	int innerMargin = 4;
	DrawBox(left + innerMargin, top + innerMargin, right - innerMargin, bottom - innerMargin,
		GetColor(0, 200, 0), TRUE);

	// 上部のリム（強調）
	DrawBox(left, top, right, top + 4, GetColor(50, 100, 50), TRUE);

	// もし画像で描画したい場合（ImageManager で画像ハンドルを取得できるなら）
	// int handle = ImageManager::getInstance()->getImageHandle(ImageManager::IMAGE_PIPE_TOP);
	// if (handle >= 0) {
	//     // DrawExtendGraph は左上(x＝left, y＝top) から右下(right, bottom) に画像を引き伸ばして描く
	//     DrawExtendGraph(left, top, right, bottom, handle, TRUE);
	// });

	// 入れる/入れない の視覚的ヒント（デバッグ表示）
#ifdef IS_DEBUG
	SetFontSize(8);
	char pipeDebugText[64];
	sprintf_s(pipeDebugText, sizeof(pipeDebugText), "P%d %s", pipeId, (enterable ? "Enter" : "NoEnter"));
	DrawString(x1 + 2, y1 + 2, pipeDebugText, GetColor(255, 255, 255));
#endif
}

//! @brief 土管の出口位置を取得
Float2 Pipe::getExitPos() const
{
	return exitPos;
}

//! @brief 土管識別IDを取得
int Pipe::getPipeId() const
{
	return pipeId;
}

//! @brief プレイヤーが土管に侵入可能かチェック
bool Pipe::isEnterable() const
{
	return enterable;
}

//! @brief ブロックがヒットされた時のコールバック実装
void Pipe::onHit(int hitDirection)
{
	// 何も起きないので特に処理はなし。
}
