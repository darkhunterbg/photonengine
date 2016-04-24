using Photon;
using Photon.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DemoNET
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceProvider.InitializeServices();

            var t0 = ServiceProvider.MemoryService.Allocate(1024, false);
            var t1 = ServiceProvider.MemoryService.Allocate(1024 * 1024, false);
            var t2 = ServiceProvider.MemoryService.Allocate(1024 * 1024 * 1024, false);

            ServiceProvider.MemoryService.Free(t0);
            ServiceProvider.MemoryService.Free(t1);
            ServiceProvider.MemoryService.Free(t2);

            ServiceProvider.UninitializeServices();
        }
    }
}
