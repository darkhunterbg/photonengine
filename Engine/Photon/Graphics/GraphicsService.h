#pragma once

#include "../PE.h"
#include "../Memory/MemoryStack.h"

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
			static GraphicsService* Initialize( memory::MemoryStack& stack);
			static void Uninitialize();

			//void SetCurrentWindow(photon::platform::Window window);
		};
	}

	EXPORT extern graphics::GraphicsService* gl_GraphicsService;
}