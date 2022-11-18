
local TestBlock = world.block("test")

function TestBlock:placed()
	print("Hello, world!")
end

return TestBlock ~= nil
