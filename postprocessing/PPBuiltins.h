#pragma once
#include "rendering/surfaces/CommonRenderTarget.h"
#include "rendering/surfaces/TextureMap.h"

void PPFastBlur(cdc::TextureMap *src, cdc::CommonRenderTarget *dst, uint32_t passMask /*...*/);
void PPAntiAlias(cdc::TextureMap *src, cdc::CommonRenderTarget *dst, uint32_t passMask);
