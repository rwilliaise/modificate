
local tmp = io.tmpfile()

tmp:write("Foo")
tmp:seek("set", 0)

local read = tmp:read("*a")

warn("tmpfile out: ", read)

tmp:close()

return read == "Foo"

