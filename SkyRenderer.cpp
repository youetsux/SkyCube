#include "SkyRenderer.h"
#include "Engine/Direct3D.h"

SkyRenderer::SkyRenderer()
	:pVertexShader_(nullptr),
	 pPixelShader_(nullptr),
	 pConstantBuffer_(nullptr),
	 pCubemapSRV_(nullptr),
	 pSamplerState_(nullptr),
	 pDepthStencilState_(nullptr)
{}

SkyRenderer::~SkyRenderer()
{}

HRESULT SkyRenderer::Initialize()
{
    return S_OK;
}

void SkyRenderer::Draw()
{}

void SkyRenderer::Release()
{
	SAFE_RELEASE(pPixelShader_);
	SAFE_RELEASE(pVertexShader_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pCubemapSRV_);
	SAFE_RELEASE(pSamplerState_);
	SAFE_RELEASE(pDepthStencilState_);
}
