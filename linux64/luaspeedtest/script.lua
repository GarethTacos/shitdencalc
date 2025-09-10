--print(add(5, 7))            --> 12
--print(get_string())         --> Hello from C!
--print(get_table().name)     --> Shitdencalc
--print(get_table().version)  --> 1
--x, y = get_coords()
--print(x, y)                     --> 3.14   2.71
--hello = io.read()
--print(hello)
-- Jz 1
-- Bz 13
-- Wz 25
-- Gz 37
-- Rz 49
local hs = {"甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"}
local eb = {"子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"}

function calcyear(year)
	return (year-3)%60
end
function hrem(n)
	-- just wraps so i have no headache
	  -- If n is a number, we perform the wrapping
  if type(n) == "number" then
    return (n - 1) % 10 + 1
  else
    -- Handle cases where the input isn't a number
    return nil
  end
end
function calcterm(day,month,ymt)
	-- need year mod 10
	itg = 0 -- based on tiger (init tiger)
	if ymt == 1 or ymt == 6 then
		itg = 3
	elseif ymt == 2 or ymt == 7 then
		itg = 5
	elseif ymt == 3 or ymt == 8 then
		itg = 7
	elseif ymt == 4 or ymt == 9 then
		itg = 9
	elseif ymt == 5 or ymt == 10 then
		itg = 1
	end
	if day > 3 and month == 2 or day < 6 and month == 3 then
		print("雨水")
		print(hs[itg]..eb[3])
	end
	if day > 5 and month == 3 or day < 5 and month == 4 then
		print("春分")
		print(hs[hrem(itg+1)]..eb[4])
	end
	if day > 4 and month == 4 or day < 6 and month == 5 then
		print("谷雨")
		print(hs[hrem(itg+2)]..eb[5])	
	end
	if day > 5 and month == 5 or day < 6 and month == 6 then
		print("小滿")
		print(hs[hrem(itg+3)]..eb[6])	
	end
	if day > 5 and month == 6 or day < 7 and month == 7 then
		print("夏至")
		print(hs[hrem(itg+4)]..eb[7])		
	end
	if day > 6 and month == 7 or day < 8 and month == 8 then
		print("大暑")
		print(hs[hrem(itg+5)]..eb[8])	
	end
	if day > 7 and month == 8 or day < 8 and month == 9 then
		print("處暑")
		print(hs[hrem(itg+6)]..eb[9])	
	end
	if day > 7 and month == 9 or day < 8 and month == 10 then
		print("秋分")
		print(hs[hrem(itg+7)]..eb[10])	
		
	end
	if day > 7 and month == 10 or day < 7 and month == 11 then
		print("霜降")
		print(hs[hrem(itg+8)]..eb[11])
	end
	if day > 6 and month == 11 or day < 7 and month == 12 then
		print("小雪")
		print(hs[hrem(itg+9)]..eb[12])
	end
	if day > 6 and month == 12 or day < 6 and month == 1 then
		print("冬至")
		print(hs[hrem(itg+10)]..eb[1])
	end
	if day > 5 and month == 1 or day < 4 and month == 2 then
		print("大寒")
		print(hs[hrem(itg+11)]..eb[2])
	end

end
function calcday(day,mnt,yer)
	local i = 0
	if mnt == 1 or mnt == 2 then
		i = 5
	end
	if yer%4 == 0 and yer%100 ~= 0 or yer%400 == 0 then
		i = 6
	end
	local y = ((((yer%400)%80)%12)*5 + (yer%400%80/4))%60
	local c = math.abs(yer/400)-math.abs(yer/100)+10
	local m = (mnt+1)%2 * 30 + ((6*(mnt+1))/10-3)-i
	return math.floor((y+c+m+day-1)%60+1)
end

-- Gregorian -> Julian Day Number (integer)
local function toJDN(y, m, d)
  if m <= 2 then
    y = y - 1
    m = m + 12
  end
  local A = math.floor(y / 100)
  local B = 2 - A + math.floor(A / 4)
  local jdn = math.floor(365.25 * (y + 4716)) + math.floor(30.6001 * (m + 1)) + d + B - 1524
  return jdn
end

-- Anchor: 1900-01-01 is 甲戌
-- Find the 0-based index in the 60-cycle that corresponds to 甲戌:
-- stems: hs[(index % 10) + 1]  -> 甲 is index 1 -> index % 10 == 0
-- branches: eb[(index % 12) + 1] -> 戌 is position 11 -> index % 12 == 10
-- Solve gives index = 10 (0-based)
local anchor_jdn = toJDN(1900, 1, 1)
local anchor_index = 10  -- 0-based index for 甲戌

-- Calculate day pillar for given y,m,d
local function calcDayPillar(y, m, d)
  local jdn = toJDN(y, m, d)
  local days = (jdn - anchor_jdn) % 60
  local idx = (anchor_index + days) % 60     -- 0..59
  local stem = hs[(idx % 10) + 1]
  local branch = eb[(idx % 12) + 1]
  return stem .. branch,  idx
end

local function calcHour(ds,h)
-- ds is daystem
-- h is hour in 24h format
-- rtr is root based on rat
	if h > 23 then
		ds = ds + 1
	end
	local rtr = 0
	if ds == 1 or ds == 6 then
		rtr = 1
	end
	if ds == 2 or ds == 7 then
		rtr = 3
	end
	if ds == 3 or ds == 8 then
		rtr = 5
	end
	if ds == 4 or ds == 9 then
		rtr = 7
	end
	if ds == 5 or ds == 10 then
		rtr = 9
	end
	if h >= 23 or h < 1 then
		return hs[rtr]..eb[1]
	elseif h >= 1 and h < 3 then
		return hs[hrem(rtr+1)]..eb[2]
	elseif h >= 3 and h < 5 then
		return hs[hrem(rtr+2)]..eb[3]
	elseif h >=5 and h <7 then
		return hs[hrem(rtr+3)]..eb[4]
	elseif h>=7 and h<9 then
		return hs[hrem(rtr+4)]..eb[5]
	elseif h>=9 and h<11 then
		return hs[hrem(rtr+5)]..eb[6]
	elseif h>=11 and h<13 then
		return hs[hrem(rtr+6)]..eb[7]
	elseif h>=13 and h<15 then
		return hs[hrem(rtr+7)]..eb[8]
	elseif h>=15 and h<17 then
		return hs[hrem(rtr+8)]..eb[9]
	elseif h>=17 and h<19 then
		return hs[hrem(rtr+9)]..eb[10]
	elseif h>=19 and h<21 then
		return hs[hrem(rtr+10)]..eb[11]
	elseif h>=21 and h<23 then
		return hs[hrem(rtr+11)]..eb[12]
	end
end

print("year")
local year = tonumber(io.read())
print("month")
local month = tonumber(io.read())
print("day")
local day = tonumber(io.read())
print("hour")
local hour = tonumber(io.read())

local pillarno = calcyear(year)
if pillarno == 0 then
	pillarno = 60
end
if month == 1 or month == 2 then
	pillarno = pillarno - 1
end
-- year
print(hs[(pillarno-1)%10+1]..eb[(pillarno-1)%12+1])
-- month with term
calcterm(day,month,(pillarno-1)%10+1)
--local dayres = calcday(day,month,year)
--print(dayres)
--print(hs[(dayres-1)%10+1]..eb[(dayres-1)%12+1])
local daypillar, index = calcDayPillar(year,month,day)
-- day
print(daypillar)
print(calcHour((index%10)+1,hour))
