#include "GraphicsAPI.h"
#include "GLGraphicsAPI.h"
#include "DXGraphicsAPI.h"
#include "../Services/MemoryStack.h"

namespace photon
{
	GraphicsAPI::GraphicsAPI(GraphicsAPIType type):
		type(type)
	{
		
	}

	GraphicsAPI* GraphicsAPI::CreateAPI(GraphicsAPIType type,const void* apiParam, MemoryStack& stack)
	{
		switch (type)
		{
#ifdef OPENGL
		case GraphicsAPIType::OpenGL:
		{
			void* ptr = stack.Allocate(sizeof(GLGraphicsAPI));
			return new(ptr) GLGraphicsAPI((const GLAPIParam*)apiParam);
		}
		break;
#endif

#ifdef DIRECTX
		case GraphicsAPIType::DirectX:
		{
			void* ptr = stack.Allocate(sizeof(DXGraphicsAPI));
			return new(ptr) DXGraphicsAPI((const DXAPIParam*)apiParam);
		}
		break;
#endif

		default:
			ASSERT(false);
		}

		return nullptr;
	}

}