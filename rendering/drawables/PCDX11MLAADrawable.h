#pragma once
#include "../IRenderDrawable.h"

namespace cdc {

class PCDX11MLAADrawable :
	public IRenderDrawable
{
public:
	PCDX11MLAADrawable(/*TODO*/)
	{}

	virtual void draw(uint32_t funcSetIndex, IRenderDrawable *other);
	virtual uint32_t compare(uint32_t funcSetIndex, IRenderDrawable *other);
};

}
