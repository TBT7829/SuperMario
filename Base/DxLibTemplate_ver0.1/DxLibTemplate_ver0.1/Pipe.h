#pragma once

#include "Block.h"

//! @brief 土管ブロッククラス
//! @brief Block を継承
//! @note Object の id は ObjectManager が生成する一意の ID。
//!       pipeId は土管同士のペアやデバッグ用識別子で、object id とは別目的です。
//!       pipe には「入れる」「入れない」両タイプをサポートします。
class Pipe : public Block
{
public:
	//! @brief コンストラクタ
	//! @param _id ObjectManager が発行するオブジェクトID（この土管自身の一意なID）
	//! @param _start 土管のワールド位置
	//! @param _size 土管サイズ（幅/高さ）
	//! @param _exitPos ワープ先のワールド座標（ワープを設定しない場合は無視してよい）
	//! @param _pipeId 土管識別ID（ペアを紐付けるための任意識別子、object id とは別）
	//! @param _enterable プレイヤーが土管に入れるか（true = 入れる, false = 入れない）
	Pipe(int _id, Float2 _start, Float2 _size, Float2 _exitPos, int _pipeId = 0, bool _enterable = true);

	virtual ~Pipe();

	//! @brief 更新処理
	void update() override;

	//! @brief 描画処理
	void render() override;

	//! @brief ワープ出口位置を取得
	Float2 getExitPos() const;

	//! @brief 土管識別IDを取得
	int getPipeId() const;

	//! @brief その土管が「入れるタイプ」かどうか
	bool isEnterable() const;

	//! @brief ブロックがヒットされた時のコールバック
	void onHit(int hitDirection) override;

private:
	int image;
	Float2 exitPos;	//! @brief ワープ出口座標
	int pipeId;		//! @brief 土管識別ID（object idとは別）
	bool enterable;	//! @brief プレイヤーが入れるかどうか（true=入れる）
};
