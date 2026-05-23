#pragma once


// 状態を扱うクラス(オブジェクトに内包してあげる)

//! @brief 状態マシンを表すクラス
//! @tparam _T_ 状態マシンを使用するオブジェクトの型
template<typename _T_>
class StateMachine
{
protected:
	//! @brief コールバック関数のポインタ型
	//! @brief void型の戻り値を持つ引数なしのメンバ関数のポインタ
	typedef void (_T_::* CBFuncPtr)();

	//! @brief 状態の最大数
	static const int STATE_MAX = 16;

	//! @brief 状態を表すクラス
	class State
	{
	public:
		CBFuncPtr pInit;
		CBFuncPtr pUpdate;
		CBFuncPtr pExit;
		//void (_T_::* pInit)();
		//void (_T_::* pUpdate)();
		//void (_T_::* pExit)();
	};

public:
	//! @brief コンストラクタ
	StateMachine()
	{
		// 各関数ポインタの初期化
		for (int i = 0; i < STATE_MAX; i++) {
			State* pState = &stateArray[i];
			pState->pInit = pState->pUpdate = pState->pExit = nullptr;
		}
		// 状態の初期化
		curState = STATE_MAX - 1;
		// 次の状態の初期化
		nextState = -1;
	}

	//! @brief 状態を追加する
	//! @param stateId 追加する状態のID
	//! @param pInit 初期化関数のポインタ
	//! @param pUpdate 更新関数のポインタ
	//! @param pExit 終了関数のポインタ
	void add(int stateId, CBFuncPtr pInit, CBFuncPtr pUpdate, CBFuncPtr pExit)
	{
		State* pState = &stateArray[stateId];
		pState->pInit = pInit;
		pState->pUpdate = pUpdate;
		pState->pExit = pExit;
	}

	//! @brief 次の状態を設定する((状態の変更自体はupdateが行う))
	//! @param nextStateId 次の状態のID
	void change(int nextStateId)
	{
		// 現在の状態と同じなら何もせずに抜ける
		if (nextStateId == curState)
		{
			return;
		}

		// 次に移動するべき状態番号を保存して終了
		nextState = nextStateId;
	}

	//! @brief 状態に応じた更新処理の実行
	//! @param pObject 状態マシンを使用するオブジェクトのポインタ
	void update(_T_* pObject)
	{
		// 次の状態が保存されているかチェック
		// もしnextStateが0以上なら次の状態に変化する
		if (0 <= nextState)
		{
			// 現在の状態の終了処理を実行
			State* pPrevState = &stateArray[curState];
			if (pPrevState->pExit != nullptr)
			{
				CBFuncPtr pExit = pPrevState->pExit;
				// メンバ関数だから親のポインタと一緒に呼び出してあげる
				// 現在の状態の終了処理を実行
				(pObject->*pExit)();
			}

			// 次の状態の初期化処理を実行
			State* pNextState = &stateArray[nextState];
			if (pNextState->pInit != nullptr)
			{
				CBFuncPtr pInit = pNextState->pInit;
				// 次の状態の初期化処理を実行
				(pObject->*pInit)();
			}
			// 現在の状態を更新
			curState = nextState;
			// 次の状態に-1を入れて状態変化が起こらないように
			nextState = -1;
		}

		// 現在の状態の更新処理を呼び出す
		State* pCurState = &stateArray[curState];
		// 中身がnullptrなら何もしない
		if (pCurState->pUpdate != nullptr)
		{
			// 今の状態の更新処理を呼び出す
			CBFuncPtr pUpdate = pCurState->pUpdate;
			(pObject->*pUpdate)();
		}
	}

	//! @brief 現在の状態のIDを取得する
	int getStateId()
	{
		return curState;
	}

private:

	// 各状態でどの関数を呼び出せばいいのかの情報を保持する配列
	// std::array<_T_, STATE_MAX> stateArraay;
	State stateArray[STATE_MAX];

	// 現在の状態
	int curState;

	// 次に変更するべき状態(マイナスの値で状態変化をしない)
	int nextState;

};

