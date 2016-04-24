#pragma once


#using <mscorlib.dll>

namespace Photon
{
	namespace Services
	{
		///<summary>
		/// Service for managing memory
		///</summary>
		public ref class MemoryService abstract sealed
		{
		public:
			///<summary>
			///Allocate new chunck of unmanaged memory
			///</summary>
			///<param name="size">Amount of memory to allocate</param>
			///<param name="persistent">Mark memory persistent. Persistent memory will not be collected by FreeNonPersistent().</param>
			///<returns>Handler to the allocated memory</returns>
			static System::IntPtr Allocate(System::UInt32 size, bool persistent);

			///<summary>
			///Free chunck of unmanaged memory
			///</summary>
			///<param name="pageHandle">Handle to the allocated unmanaged memory</param>
			///<returns>Success if memory was released</returns>
			static bool Free(System::IntPtr pageHandle);

			///<summary>
			///Free all non-persistent memory
			///</summary>
			static void FreeNonPersistent();
		};
	}
}