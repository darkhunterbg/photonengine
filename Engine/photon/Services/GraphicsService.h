#pragma once

#include "../PE.h"
#include "MemoryStack.h"

namespace photon
{

	namespace graphics
	{

		class EXPORT GraphicsService
		{
			DISABLE_NEW_DELETE(GraphicsService);
			DISABLE_COPY(GraphicsService);

		private:
			GraphicsService();
		public:
			static GraphicsService* Initialize( MemoryStack& stack);
			static void Uninitialize();

			//void SetCurrentWindow(photon::platform::Window window);
		};
	}

	EXPORT extern graphics::GraphicsService* gl_GraphicsService;
}