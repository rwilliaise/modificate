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

local function round(num, numDecimalPlaces)
  local mult = 10 ^ (numDecimalPlaces or 0)
  return math.floor(num * mult + 0.5) / mult
end

expect(ZERO ~= TEST_VECTOR)
expect(ZERO * TEST_VECTOR == ZERO)
expect(TEST_VECTOR.x == 1)

expect(#(vector(0, 1, 0)) == 1)
expect(#TEST_VECTOR == #vector(3, 2, 1))
expect(#(ZERO - UP) == ZERO:distance(UP))
expect(round(#TEST_VECTOR:normalize(), 5) == 1) -- darn you IEEE-754

local RIGHT = vector(1, 0, 0)
local FORWARD = vector(0, 0, -1)

expect(RIGHT:cross(FORWARD) == UP)
expect(RIGHT:dot(FORWARD) == 0)
expect(RIGHT:dot(FORWARD) == RIGHT:dot(UP))

expect(vector(1, 2, 4) // 2 == vector(0, 1, 2))
expect(UP + 3 == vector(3, 4, 3))
expect(UP * 3 == vector(0, 3, 0))

expect(tostring(ZERO) == "vec [0.0, 0.0, 0.0]")
expect(type(ZERO) == "table")

return true
