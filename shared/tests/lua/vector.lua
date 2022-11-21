local ZERO = vector()
local TEST_VECTOR = vector(1, 2, 3)
local UP = vector(0, 1, 0)

local function expect(result)
	local info = debug.getinfo(2, "lS")
	if not result then
		print("Failed test on line " .. info.currentline)
		exit(1)
	end
end

expect(ZERO ~= TEST_VECTOR)
expect(ZERO * TEST_VECTOR == ZERO)
expect(TEST_VECTOR.x == 1)

expect(#(vector(0, 1, 0)) == 1)

expect(vector(1, 2, 4) // vector(2, 2, 2) == vector(0, 1, 2))
expect(UP + 3 == vector(3, 4, 3))
expect(UP * 3 == vector(0, 3, 0))

expect(tostring(ZERO) == "vec [0.0, 0.0, 0.0]")
expect(type(ZERO) == "table")

return true
