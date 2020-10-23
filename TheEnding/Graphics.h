#pragma once
#include "EndingWin.h"
#include "DXTrace.h"
#include <wrl.h>
#include <d3d11.h>
class Graphics
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
	 
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;

	void DrawTriangle(float angle) ;
private:
	ComPtr<ID3D11Device> pDevice ;
	ComPtr<IDXGISwapChain> pSwap ;
	ComPtr<ID3D11DeviceContext> pContext ;
	ComPtr<ID3D11RenderTargetView> pTarget ;
};

