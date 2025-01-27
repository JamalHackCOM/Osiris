#pragma once

#include <CSGO/Functions.h>
#include <Platform/DynamicLibraryView.h>
#include <RetSpoof/FunctionInvoker.h>
#include <RetSpoof/RetSpoofInvoker.h>

struct InterfaceFinder {
    template <typename PlatformApi>
    explicit InterfaceFinder(DynamicLibraryView<PlatformApi> library, RetSpoofInvoker invoker)
        : createInterface{ invoker, std::uintptr_t(library.getFunctionAddress("CreateInterface")) }
    {
    }

    void* operator()(const char* name) const noexcept
    {
        if (createInterface)
            return createInterface(name, nullptr);
        return nullptr;
    }

private:
    FunctionInvoker<csgo::CreateInterface> createInterface;
};
