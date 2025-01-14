#pragma once
#include <vector>
#include "cdc/dtp/objectproperties/intro.h"

class Instance;

class InstanceManager {
public:
	static Instance *CreateInstance1();
	static Instance *CreateInstance2();

	inline static Instance *CreateInstance(dtp::Intro *intro) {
		if (intro->field40 & 4)
			return CreateInstance1();
		else
			return CreateInstance2();
	}

	static std::vector<Instance*> s_instances;
};
