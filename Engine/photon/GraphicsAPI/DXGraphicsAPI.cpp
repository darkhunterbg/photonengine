#include "DXGraphicsAPI.h"

#include "../Platform.h"

#if defined (DIRECTX)

#include <d3d11.h>

namespace photon
{
	DXGraphicsAPI::DXGraphicsAPI(const DXAPIParam* apiParam)
		:GraphicsAPI(GraphicsAPIType::DirectX)
	{

		D3D_FEATURE_LEVEL featureLevel;

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

		desc.BufferCount = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = (HWND)apiParam->hWindow;
		desc.SampleDesc.Count = 1;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		DWORD createDeviceFlags = 0;
#if PE_DEBUG > 0
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &desc, &swapChain, &device, &featureLevel, &deviceContext);


#if PE_DEBUG > 0
		device->QueryInterface(IID_PPV_ARGS(&d3d11Debug));
#endif
	}

	DXGraphicsAPI::~DXGraphicsAPI()
	{
		if (d3d11Debug)
			d3d11Debug->Release();

		deviceContext->Release();
		
		swapChain->SetFullscreenState(false, nullptr);
		swapChain->Release();

		device->Release();
	}

	void DXGraphicsAPI::SwapBuffers()
	{
		swapChain->Present(0, 0);
	}
}

#endif