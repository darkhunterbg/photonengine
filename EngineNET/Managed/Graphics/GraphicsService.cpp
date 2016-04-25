#include "GraphicsService.h"
#include <Photon/Graphics/GraphicsService.h>


namespace Photon
{
	namespace Graphics
	{
		GraphicsService::GraphicsService(photon::graphics::GraphicsService* native) :
			native(native)
		{

		}
		GraphicsService::~GraphicsService()
		{

		}

		GraphicsService^ GraphicsService::Instance::get()
		{
			return instance;
		}
		void GraphicsService::Instance::set(GraphicsService^ value)
		{
			instance = value;
		}

	}
}