#include "SkyRenderer.h"
#include "Engine/Direct3D.h"
#include <d3dcompiler.h>

SkyRenderer::SkyRenderer()
	:pVertexShader_(nullptr),
	 pPixelShader_(nullptr),
	 pConstantBuffer_(nullptr),
	 pCubemapSRV_(nullptr),
	 pSamplerState_(nullptr),
	 pDepthStencilState_(nullptr)
{
}

SkyRenderer::~SkyRenderer()
{}

HRESULT SkyRenderer::Initialize()
{
    ID3DBlob* pCompileVS = nullptr;
    ID3DBlob* pCompilePS = nullptr;

    HRESULT hr = D3DCompileFromFile(
        L"Sky.hlsl", nullptr, nullptr,
        "VS", "vs_5_0", 0, 0,
        &pCompileVS, nullptr);

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"Sky頂点シェーダーのコンパイルに失敗しました", L"エラー", MB_OK);
        return hr;
    }

    hr = D3DCompileFromFile(
        L"Sky.hlsl", nullptr, nullptr,
        "PS", "ps_5_0", 0, 0,
        &pCompilePS, nullptr);

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"Skyピクセルシェーダーのコンパイルに失敗しました", L"エラー", MB_OK);
        SAFE_RELEASE(pCompileVS);
        return hr;
    }

    hr = Direct3D::pDevice->CreateVertexShader(
        pCompileVS->GetBufferPointer(),
        pCompileVS->GetBufferSize(),
        nullptr,
        &pVertexShader_);

    if (FAILED(hr))
    {
        SAFE_RELEASE(pCompileVS);
        SAFE_RELEASE(pCompilePS);
        return hr;
    }

    hr = Direct3D::pDevice->CreatePixelShader(
        pCompilePS->GetBufferPointer(),
        pCompilePS->GetBufferSize(),
        nullptr,
        &pPixelShader_);

    SAFE_RELEASE(pCompileVS);
    SAFE_RELEASE(pCompilePS);

    return hr;
}

void SkyRenderer::Draw()
{
    Direct3D::pContext->VSSetShader(pVertexShader_, nullptr, 0);
    Direct3D::pContext->PSSetShader(pPixelShader_, nullptr, 0);

    // SV_VertexID で頂点を作るので、頂点バッファも入力レイアウトも使わない。
    Direct3D::pContext->IASetInputLayout(nullptr);
    Direct3D::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 3頂点だけで画面全体を覆う三角形を描く。
    Direct3D::pContext->Draw(3, 0);
}

void SkyRenderer::Release()
{
	SAFE_RELEASE(pPixelShader_);
	SAFE_RELEASE(pVertexShader_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pCubemapSRV_);
	SAFE_RELEASE(pSamplerState_);
	SAFE_RELEASE(pDepthStencilState_);
}
