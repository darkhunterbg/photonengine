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
            var ptr = MemoryService.Allocate(1024, false);
           bool result = MemoryService.Free(ptr);
        }
    }
}
