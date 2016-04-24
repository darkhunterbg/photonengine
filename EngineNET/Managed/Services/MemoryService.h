#pragma once


#using <mscorlib.dll>

namespace photon
{
	namespace services
	{
		class MemoryService;
	}
}

namespace Photon
{
	namespace Services
	{
		///<summary>
		/// Service for managing native  memory
		///</summary>
		public ref class MemoryService  sealed
		{
		private:
			static MemoryService^ instance;

			photon::services::MemoryService* native;
		internal:
			MemoryService(photon::services::MemoryService* native);
			~MemoryService();
		public:

			///<summary>
			///Gets the singleton instance of the MemoryService
			///</summary>
			static property MemoryService^ Instance
			{
				MemoryService^ get();
			internal:
				void set(MemoryService^ value);
			}

			///<summary>
			///Allocate new chunck of unmanaged memory
			///</summary>
			///<param name="size">Amount of memory to allocate</param>
			///<param name="persistent">Mark memory persistent. Persistent memory will not be collected by FreeNonPersistent().</param>
			///<returns>Handler to the allocated memory</returns>
			System::IntPtr Allocate(System::UInt32 size, bool persistent);

			///<summary>
			///Free chunck of unmanaged memory
			///</summary>
			///<param name="pageHandle">Handle to the allocated unmanaged memory</param>
			///<returns>Number of bytes freed or 0 if failed</returns>
			System::UInt32 Free(System::IntPtr pageHandle);

			///<summary>
			///Free all non-persistent memory
			///</summary>
			///<returns>Number of bytes freed or 0 if failed</returns>
			System::UInt32 FreeNonPersistent();

		};
	}
}