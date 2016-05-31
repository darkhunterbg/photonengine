#include "DXGraphicsAPI.h"

#include "../Platform/Platform.h"

#if GRAPHICS_API == DIRECTX

#include <d3d11.h>

#include "../Services/MemoryStack.h"

namespace photon
{
	DXGraphicsAPI::DXGraphicsAPI(DXAPIParam apiParam)
	{

		D3D_FEATURE_LEVEL featureLevel;

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

		desc.BufferCount = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = (HWND)apiParam.hWindow;
		desc.SampleDesc.Count = 1;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		DWORD createDeviceFlags = 0;
#if DEBUG > DEBUG_DEV
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &desc, &swapChain, &device, &featureLevel, &deviceContext);
#if DEBUG > DEBUG_DEV
		device->QueryInterface(IID_PPV_ARGS(&d3d11Debug));
#endif
	}

	DXGraphicsAPI* DXGraphicsAPI::InitializeAPI(MemoryStack& stack, GraphicsAPIParam apiParam)
	{
		void* ptr = stack.Allocate(sizeof(DXGraphicsAPI));
		return new(ptr) DXGraphicsAPI(apiParam);
	}

	void DXGraphicsAPI::UninitializeAPI(DXGraphicsAPI* api)
	{
		if (api->d3d11Debug)
			api->d3d11Debug->Release();

		api->deviceContext->Release();

		api->swapChain->SetFullscreenState(false, nullptr);
		api->swapChain->Release();

		api->device->Release();
	}



	void DXGraphicsAPI::SwapBuffers()
	{
		swapChain->Present(0, 0);
	}
}

#endif