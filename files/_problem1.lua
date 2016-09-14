n=tonumber(io.read())
r=tonumber(io.read())
c=tonumber(io.read())
plan={}
plan[0]={}
for _=1,c do plan[0][_]="I" end
for _=1,r do
	local k=io.read()
	plan[_]={}
	plan[_][0]="I"
	for chr=1,#k do
		plan[_][chr]=k:sub(chr,chr)
	end
end
roomN,rooms,r_=0,{},0
for y=1,r do
	for x=1,c do
		if plan[y][x]=="." then
			if plan[y-1][x]~="." and plan[y-1][x]~="I" then
				plan[y][x]=plan[y-1][x]

			elseif plan[y][x-1]~="." and plan[y][x-1]~="I" then
				plan[y][x]=plan[y][x-1]
			else
				roomN=roomN+1
				plan[y][x]=roomN
			end
		end
	end
	for x=c-1,1,-1 do
		if plan[y][x]~="." and plan[y][x]~="I" and plan[y][x+1]~="." and plan[y][x+1]~="I" and plan[y][x]~=plan[y][x+1] then
			plan[y][x]=plan[y][x+1]
		end
	end
end
for y=r-1,1,-1 do
	for x=1,c do
		if plan[y][x]~="." and plan[y][x]~="I" and plan[y+1][x]~="." and plan[y+1][x]~="I" and plan[y+1][x]~=plan[y][x] then
			plan[y][x]=plan[y+1][x]
		end
	end
	for x=c-1,1,-1 do
		if plan[y][x]~="." and plan[y][x]~="I" and plan[y][x+1]~="." and plan[y][x+1]~="I" and plan[y][x]~=plan[y][x+1] then
			plan[y][x]=plan[y][x+1]
		end
	end
end
function replaceAll(replacer,replacee)
	for y=1,r do
		for x=1,c do
			if plan[y][x]==replacee then plan[y][x]=replacer end
		end
	end
end
for y=1,r-1 do
	for x=1,c-1 do
		if plan[y-1][x]~="I" and plan[y][x]~="I" and plan[y][x]~=plan[y-1][x] then
			replaceAll(plan[y-1][x],plan[y][x])
		elseif plan[y+1][x]~="I" and plan[y][x]~="I" and plan[y][x]~=plan[y+1][x] then
			replaceAll(plan[y+1][x],plan[y][x])
		elseif plan[y][x-1]~="I" and plan[y][x]~="I" and plan[y][x-1]~=plan[y][x] then
			replaceAll(plan[y][x-1],plan[y][x])
		elseif plan[y][x+1]~="I" and plan[y][x]~="I" and plan[y][x+1]~=plan[y][x] then
			replaceAll(plan[y][x+1],plan[y][x])
		end
	end
end
for x=1,roomN do rooms[x]=0 end
for x=1,r do
	--_y=""
	for y=1,c do
		--_y=_y..plan[x][y]
		if plan[x][y]~="I" then
			rooms[plan[x][y]]=rooms[plan[x][y]]+1
		end
	end
	--print(_y)
end
table.sort(rooms)
--for _,l in ipairs(rooms) do print(l) end
for x=roomN,1,-1 do
	if n>=rooms[x] and rooms[x]~=0 then
		n,r_=n-rooms[x],r_+1
	end
end
phv="s"
if r_==1 then phv="" end
print(r_.." room"..phv..", "..n.." square metre(s) left over")
