
local TestBlock = Block.new()

function TestBlock:Registered()
	print(self)

end

TestBlock:Register("TestBlock")

return TestBlock ~= nil
