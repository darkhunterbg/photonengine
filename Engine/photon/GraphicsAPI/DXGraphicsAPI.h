#pragma once

#include "../Macro.h"

#include "GraphicsAPI.h"

#if  GRAPHICS_API == DIRECTX

#pragma comment (lib,"d3d11.lib")

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11Debug;

namespace photon
{
	struct MemoryStack;

	struct EXPORT DXAPIParam
	{
		void* hWindow;
	} typedef GraphicsAPIParam;

	class EXPORT DXGraphicsAPI
	{
		DISABLE_COPY(DXGraphicsAPI);
		DISABLE_NEW_DELETE(DXGraphicsAPI);

	private:
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* deviceContext = nullptr;
		IDXGISwapChain* swapChain = nullptr;

		ID3D11Debug* d3d11Debug = nullptr;

		DXGraphicsAPI(DXAPIParam apiParam);
	public:
		static DXGraphicsAPI* InitializeAPI(MemoryStack& stack, GraphicsAPIParam apiParam);
		static void UninitializeAPI(DXGraphicsAPI* api);


		void SwapBuffers();
	} typedef GraphicsAPI;
}

#endif