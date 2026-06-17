#pragma once
#include "Object.h"
#include "Float2.h"

class KoopaTroopa : public Object
{
public:
	enum KOOPATROOPA_STATE {
		WAIT_APPEAR = 0, //!< 出現待ち
		WALKING,         //!< 歩行中
		SHELL            //!< 甲羅状態
	};

	//! @brief コンストラクタ
	//! @param startX 配置する初期X座標
	//! @param startY 配置する初期Y座標
	KoopaTroopa(float startX, float startY);

	//! @brief デストラクタ
	virtual ~KoopaTroopa() override;

	//! @brief 更新処理
	void update() override;
	//! @brief 描画処理
	void render() override;

private:
	Float2 pos;
	Float2 size;
	Float2 movSpeed;
	KOOPATROOPA_STATE state;
	int m_imageHandle;
};
