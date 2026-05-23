#pragma once

enum OBJECT_TYPE {
	PLAYER = 0,
	GROUND_BLOCK,
};

// 全てのオブジェクト(キャラや地形、弾など)に
// 持たせる要素を持った基底クラス(親クラス)
// (抽象クラスにしてある)

//! @brief 色んな物体の基底となるクラス
//! @brief 操作キャラや敵、アイテムなどのオブジェクトに
//! @brief 共通して持たせる要素を持っている
class Object
{
public:

	//! @brief オブジェクトの状態の名前
	enum OBJECT_STATE
	{
		//! @brief 動作開始前
		READY,
		//! @brief 動作中
		ACTIVE,
		//! @brief 一時停止
		PAUSE,
		//! @brief	動作終了(死亡状態)
		INACTIVE
	};

	//-----------------------
	// メンバ関数
	//-----------------------

	//! @brief コンストラクタ(オブジェクトが生成された時に自動的に呼ばれる関数)
	//! @param id 
	Object(int id, int objectType);

	//! @brief デストラクタ(オブジェクトが削除された時、あるいはプログラムの終了時に自動的に呼ばれる関数)
	//! @brief virtualをつけてアップキャスト(子クラスから親クラスへの型変換)したときに
	//! @brief Taskのデストラクタが呼ばれないことを防ぐ
	virtual ~Object();

	//! @brief オブジェクトのIDの取得
	//! @return オブジェクトのID
	int getObjectId();

	//! @brief オブジェクトの状態の取得
	//! @return オブジェクトの状態(state)
	int getObjectState();

	//! @brief オブジェクトの型の取得
	//! @return オブジェクトの型(objectType)
	int getObjectType();

	//! @brief 初回起動時に実行される処理を動かす関数
	//! @brief 内部で状態をACTIVE(動作中)にする
	//! @return 無事に実行出来たらtrue、動作開始前ではなかった場合はfalse
	bool activate();

	//! @brief オブジェクトの死亡時に実行される処理を動かす関数
	//! @brief 内部で状態をINACTIVE(死亡状態)にする
	//! @return 無事に実行出来たらtrue、そもそも死亡状態になっていなければ実行せずにfalse
	bool deactivate();

	//-----------------------
	// 純粋仮想関数
	//-----------------------
	// virtualが付いた関数の後ろに「 = 0」がついている関数は"純粋仮想関数"である。
	// 純粋仮想関数を持つクラスは抽象クラスとなりこのクラスの型のオブジェクトを直接生成できなくなる。
	// 派生クラス(子クラス、基底クラスを継承したクラス)はこの純粋仮想関数をオーバーライド(上書き)しない限りエラーが吐かれる。
	// 要は作られたら困る基底クラスはオブジェクトを作れないようにしつつ、絶対に派生クラスに持たせたい関数を実装させる機構となっている。

	//! @brief 更新処理
	virtual void update() = 0;

	//! @brief 描画処理
	virtual void render() = 0;

protected:
	//! @brief  初回実行時にしてほしい内容を実行する関数
	//! @brief  もし初回実行時に処理してほしい処理があるなら
	//! @brief	virtualをつけて仮想関数にしてあるので子クラスで関数オーバーライド(上書き)して使用すればよい
	virtual void activateProc() {}

	//! @brief	死亡時に処理してほしい内容を実行する関数
	//!	@brief	もし死亡時に処理してほしい処理があるなら
	//!	@brief	virtualをつけて仮想関数にしてあるので
	//!	@brief	子クラスで関数オーバーライド(上書き)して使用すればよい
	virtual void deactiveProc() {}

private:
	//-----------------------
	// メンバ変数
	//-----------------------

	//! @brief ID
	int id;

	//! @brief 状態
	int objectState;

	//! @brief オブジェクトの型
	int objectType;
};