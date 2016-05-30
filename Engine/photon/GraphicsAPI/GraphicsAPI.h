#pragma once

#include "../PE.h"


namespace photon
{
	class MemoryStack;

	enum class GraphicsAPIType
	{
#if defined(DIRECTX)
		DirectX = 1,
#endif
#if defined(OPENGL)
		OpenGL = 2,
#endif
	};

	class GraphicsAPI
	{
		DISABLE_COPY(GraphicsAPI);
		
	private:
		GraphicsAPIType type;

	protected:
		GraphicsAPI(GraphicsAPIType type);
	public:
		virtual ~GraphicsAPI() = 0 {};

		virtual void SwapBuffers() = 0;

		static GraphicsAPI* CreateAPI(GraphicsAPIType type,const  void* apiParam, MemoryStack& stack);
	};

}