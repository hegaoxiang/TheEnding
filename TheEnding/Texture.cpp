#include "Texture.h"
#include "WICTextureLoader.h"

using  namespace DirectX;
Texture::Texture(Graphics& gfx, const wchar_t* szFileName)
{
	HR(CreateWICTextureFromFile(GetDevice(gfx), szFileName, nullptr, pTextureView.GetAddressOf()));
}

void Texture::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());
}