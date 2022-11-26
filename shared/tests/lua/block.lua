-- Tests creating and loading blocks.

local TestBlock = world.block("test")

function TestBlock:placed()
	print("Hello, world!")
end

return TestBlock ~= nil and TestBlock == world.block("test")
