#pragma once
#include "Field.hpp"
class InputField : public Field
{
public:
	virtual void onRender() = 0;
	virtual void onSelect() = 0;
};

