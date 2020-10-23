#include "PixelShader.h"


PixelShader::PixelShader(Graphics& gfx, const std::wstring& path)
{
	/*INFOMAN(gfx);*/

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	HR(D3DReadFileToBlob(path.c_str(), &pBlob));
	(GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, pPixelShader.GetAddressOf()));
}

void PixelShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
