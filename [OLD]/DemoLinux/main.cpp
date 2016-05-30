#include <Photon/Memory/MemoryService.h>
#include <Photon/Memory/MemoryStack.h>
#include <Photon/Graphics/GraphicsService.h>
#include <Photon/Platform/Linux/LinuxOpenGL.h>

#include <X11/X.h>
#include <X11/Xlib.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

XVisualInfo* vi;

Window CreateAndShowWindow(Display* display)
{
    Window root = DefaultRootWindow(display);

    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    vi = glXChooseVisual(display, root, att);
    Colormap colormap = XCreateColormap(display, root, vi->visual, AllocNone);

    XSetWindowAttributes swa;
    swa.colormap = colormap;
    swa.event_mask = ExposureMask | KeyPressMask;

    Window window = XCreateWindow(
        display, root, 0, 0, 1280, 720, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    XMapWindow(display, window);
    XStoreName(display, window, "DemoLinux");

    return window;
}

int main(int argc, char* argv[])
{
    Display* display = XOpenDisplay(nullptr);
    Window window = CreateAndShowWindow(display);

    return 0;
}