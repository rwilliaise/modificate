
#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <lua.hpp>

namespace sh {

    using execution_context = std::shared_ptr<lua_State>;

    enum VmInterfaces {
        WORLD
    };

    class Vm;

    /**
     * Base class for objects that can change state in the Vm, such as the
     * current world.
     *
     * Usually represents an API in the Vm, such as the `world` global.
     */
    class VmInterface {
        public:

        explicit VmInterface(std::shared_ptr<Vm> vm): vm(vm) {}

        /**
         * Called only once, when the interface is called upon to "enter" the Vm.
         */
        virtual void mount(execution_context context) = 0;
        /**
         * Ran everytime that the interface is called upon to "enter" the Vm.
         */
        virtual void update(execution_context context) = 0;

    protected:
        std::shared_ptr<Vm> vm;
    };

    class Mod {
    private:
        friend class Vm;

        execution_context mod_context;
    };

    class Vm : public std::enable_shared_from_this<Vm> {
    public:

        Vm();

        Vm(Vm &&) = default;
        Vm &operator=(Vm &&) = default;
        Vm(const Vm &) = delete;
        Vm &operator=(const Vm &) = delete;

        /**
         * Find mods installed on the system, and mount them.
         */
        void search();
        
        /**
         * Adds an interface to the Vm, or updates it if detected.
         */
        void enter(VmInterfaces id, VmInterface &&interface);

    private:
        std::vector<Mod> mounted;
        std::unordered_map<VmInterfaces, VmInterface> interfaces;

        execution_context global_context;
    };
}
