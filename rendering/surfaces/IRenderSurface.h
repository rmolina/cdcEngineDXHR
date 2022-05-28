#pragma once
#include <cstdint>

namespace cdc {

class TextureMap;

class IRenderSurface {
public:
	virtual TextureMap *getRenderTexture() = 0;
	virtual uint32_t getWidth() = 0;
	virtual uint32_t getHeight() = 0;
	virtual void registerAtRenderDevice() = 0;
	virtual void registerAtScene(void *ptr) = 0;
	virtual void method_14() = 0;
	virtual bool method_18() { return false; };
	virtual void method_1C() {};
	virtual ~IRenderSurface() = default;
};

}