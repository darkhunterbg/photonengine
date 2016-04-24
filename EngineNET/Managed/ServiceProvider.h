#pragma once

#using <mscorlib.dll>

#include "Memory/MemoryService.h"

namespace Photon
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
		///Gets the Memory Service
		///</summary>
		static property Photon::Memory::MemoryService^ MemoryService
		{
			Photon::Memory::MemoryService^ get();
		}
	};

}