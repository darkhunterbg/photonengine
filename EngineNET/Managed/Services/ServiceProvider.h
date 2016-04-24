#pragma once

#using <mscorlib.dll>

#include "MemoryService.h"

namespace Photon
{
	namespace Services
	{
		///<summary>
		///Manages engine's services
		///</summary>
		public ref class ServiceProvider abstract sealed
		{
		public:
			///<summary>
			///Initialize all services
			///</summary>
			static void InitializeServices();

			///<summary>
			///Uninitialize all services
			///</summary>
			static void UninitializeServices();

			///<summary>
			///Gets the memory service
			///</summary>
			static property Photon::Services::MemoryService^ MemoryService
			{
				Photon::Services::MemoryService^ get();
			}
		};
	}

}