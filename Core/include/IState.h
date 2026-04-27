#pragma once

#include <iostream>

#include <typeinfo>
#include <string>
#include <cxxabi.h> // For demangling (GCC/Clang)

namespace Core {

    class IContext;

    inline std::string dbg_demangle(const char* name) 
    {
        int status = -1;
        std::unique_ptr<char, void(*)(void*)> res{
            abi::__cxa_demangle(name, NULL, NULL, &status),
            std::free
        };
        return (status == 0) ? res.get() : name;
    }

    class IState 
    {
    public:
        IState(IContext* context)
        : m_context{ context }
        {}
        
        virtual ~IState() = default;

        virtual void enter() = 0;
        virtual void exit() = 0;
        virtual void update() = 0;
        virtual bool isFinished() const = 0;

        virtual void pause() {};
        virtual void resume() {};

        virtual std::string dbg_nameYourself() const { return dbg_demangle(typeid(*this).name()); }
        
    protected:
        IContext *m_context;
        bool m_isFinished{ false };
    };
}
