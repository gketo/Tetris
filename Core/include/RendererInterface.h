#ifndef RENDERER_INTERFACE_H
#define RENDERER_INTERFACE_H


#include <iostream>
#include <windows.h>

namespace Core {
    class RendererInterface
    {
    public:
        RendererInterface() = default;

        virtual ~RendererInterface() = default;

        //virtual RawInputEvent readUserEvent(bool readlock) = 0;
    };


}

#endif