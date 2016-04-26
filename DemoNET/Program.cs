using Photon;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DemoNET
{

    class Program
    {

        static void Main(string[] args)
        {

            using (Form form = new Form()
            {
                Width = 1280,
                Height = 720

            })
            {
                form.Show();

                ServiceProvider.InitializeServices(form.Handle);

                while(form.Visible)
                {
                    Application.DoEvents();
                    ServiceProvider.SwapBackBuffer();
                }

                ServiceProvider.UninitializeServices();
            }

        }

    }


}
