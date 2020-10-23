#pragma once
#include "EndingWin.h"
#include "DXTrace.h"
#include <DirectXMath.h>
#include <wrl.h>
#include <d3d11.h>
class Graphics
{
	friend class Bindable;

	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	 
public:
	void DrawIndexed(UINT count);

public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;

	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;

private:
	DirectX::XMMATRIX projection;

private:
	ComPtr<ID3D11Device> pDevice ;
	ComPtr<IDXGISwapChain> pSwap ;
	ComPtr<ID3D11DeviceContext> pContext ;
	ComPtr<ID3D11RenderTargetView> pTarget ;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};

