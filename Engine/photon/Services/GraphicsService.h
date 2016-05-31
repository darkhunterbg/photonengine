#pragma once

#include "../Macro.h"
#include "MemoryStack.h"
#include "../GraphicsAPI/GraphicsAPI.h"

namespace photon
{


	class EXPORT GraphicsService
	{
		DISABLE_NEW_DELETE(GraphicsService);
		DISABLE_COPY(GraphicsService);

	private:
		GraphicsAPI* api;

		GraphicsService(GraphicsAPI* api);
	

	public:
		static GraphicsService* Initialize(GraphicsAPI* api, MemoryStack& stack);
		static void Uninitialize();

		void PresentFrame();
	};

	EXPORT extern GraphicsService* gl_GraphicsService;
}