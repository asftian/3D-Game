#pragma once
#include <main.h>
#include "core.h"
#include "scene.h"

class CoreTP1 : public Core
{
public:
	CoreTP1();
	virtual ~CoreTP1() override;

protected:
	virtual void Render(double dt) override;

protected:
	Box b;
	float f;
};
