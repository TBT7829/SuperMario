// 引数で指定された型に勝手に変わる
template<typename _T_>

//! @brief 引数の値を最小値minと最大値maxの範囲内に修正する
//! @param pVal 
//! @param min 
//! @param max 
void fixValueAll(_T_* pVal, _T_ min, _T_ max)	
{
	if (*pVal < min)
	{
		*pVal = min;
	}
	else if (*pVal > max)
	{
		*pVal = max;
	}
}


template<typename _T_>
//! @brief 第一引数に指定された値が、第二引数と第三引数の間におさまっているかをチェック
//! @param val 
//! @param min 
//! @param max 
//! @return 値が指定された範囲内ならtrue
//! @return 値が指定された範囲外ならfalse
bool checkRange(_T_ val, _T_ min, _T_ max)
{
	bool ret = true;
	if (val < min || max < val) {
		ret = false;
	}


	return ret;
}

