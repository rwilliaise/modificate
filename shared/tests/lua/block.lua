-- Tests creating and loading blocks.

local TestBlock = world.block("test")

print(TestBlock)

function TestBlock:place()
	print("Hello, world!")
end

return TestBlock ~= nil and TestBlock == world.block("test")
