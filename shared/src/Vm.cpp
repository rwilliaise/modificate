
#include <memory>
#include <shared/Vm.h>

#include <lua.hpp>

namespace sh {

    Vm::Vm() {
        lua_State *L = luaL_newstate();
        luaL_openlibs(L);
        
        global_context = execution_context(L, [](lua_State *L) {
            lua_close(L);
        });
    }

    void Vm::search() {
    }

    void Vm::enter(VmInterfaces id, VmInterface &&interface) {
        if (interfaces.contains(id)) {
            interfaces.erase(id);
        } else {
            interface.mount(global_context);
        }
        for (Mod mod : mounted) {
            interface.update(mod.mod_context);
        }
        interfaces[id] = std::forward<VmInterface>(interface);
    }
}
