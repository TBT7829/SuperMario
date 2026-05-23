#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__



// すべての表示物に持たせるクラス
class Renderable
{
protected:
	static const float PRIORITY_MIN;
	static const float PRIORITY_MAX;
	static const float PRIORITY_DEFAULT;

public:
	inline Renderable(float priority = PRIORITY_DEFAULT)
	{
		setPriority(priority);
		_blendRate = 1.0f;
		_blendMode = DX_BLENDMODE_ALPHA;
	}

	void setPriority(float newPriority);

	inline float getPriority()
	{
		return _priority;
	}

	void setBlendRate(float blendRate);

	inline float getBlendRate()
	{
		return _blendRate;
	}

	// 描画関数
	virtual void render() = 0;

protected:
	virtual void preRender();

	virtual void postRender();

protected:
	// 優先順位
	float _priority;
	// 透明度(透過率 0: 完全透明  1: 完全不透明)
	float _blendRate;
	// 透過の種類
	int _blendMode;

	int _beforeBlendMode;
	int _beforeBlendValue;

	friend class RenderableManager;

};


#endif