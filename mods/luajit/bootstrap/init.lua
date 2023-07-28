-- Runs to initialize the lua jit executing context.

FFI = require("ffi")
GLOBAL = {}
GLOBAL.mod = {
    id = MOD_ID,
    path = MOD_PATH
}

local sandbox = require("./sandbox.lua")

require("./log.lua") -- logging

function execute()
    
end

