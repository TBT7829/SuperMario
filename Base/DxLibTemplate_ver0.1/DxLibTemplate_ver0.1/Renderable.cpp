#include<Dxlib.h>
#include "Renderable.h"

void Renderable::setPriority(float newPriority)
{
	if (newPriority < PRIORITY_MIN)
	{
		newPriority = PRIORITY_MIN;
	}
	if (PRIORITY_MAX < newPriority)
	{
		newPriority = PRIORITY_MAX;
	}

	_priority = newPriority;
}

void Renderable::setBlendRate(float blendRate)
{
	if (blendRate < 0.0f)
	{
		blendRate = 0.0f;
	}
	if (1.0f < blendRate)
	{
		blendRate = 1.0f;
	}

	_blendRate = blendRate;
}

void Renderable::preRender()
{
	GetDrawBlendMode(&_beforeBlendMode, &_beforeBlendValue);

	if (_blendRate != 1.0)
	{
		SetDrawBlendMode(_blendMode, (int)(255.0f * _blendRate));
	}
}


// post:Œã
void Renderable::postRender()
{
	SetDrawBlendMode(_beforeBlendMode, _beforeBlendValue);
}




const float Renderable::PRIORITY_MIN = 0.0f;
const float Renderable::PRIORITY_MAX = 1.0f;
const float Renderable::PRIORITY_DEFAULT = 0.5f;

