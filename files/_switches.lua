--
_n,datas=io.read(),{}
state,lastCHAR,currentP={0,finished=false,totalC=0},"0",1
for x=1,_n do
	__i=io.read()
	if lastCHAR~=__i then
		currentP=currentP+1
		state[currentP]=0
	end
	lastCHAR=__i
	state[currentP]=state[currentP]+1
	--print(currentP,lastCHAR)
end
if lastCHAR~="0" then table.insert(state,0) end
--[[
for _,x in ipairs(state) do
	print(x)
end
--]]
function tryTurningOn(n,d)
	local ret={finished=true,totalC=d.totalC}
	if d[n-1]+d[n]+d[n+1]<4 then
		for index=1,#d do
			if index==n-1 then
				table.insert(ret,d[n-1]+d[n]+d[n+1])
			elseif not(index==n or index==n+1) then
				ret.finished=false
				table.insert(ret,d[index])
			end
		end
	else
		for index=1,#d do
			if index==n-2 then
				table.insert(ret,d[n-1]+d[n]+d[n+1]+d[n-2]+d[n+2])
			elseif index~=n-1 and index~=n and index~=n+1 and index~=n+2 then
				ret.finished=false
				table.insert(ret,d[index])
			end
		end
	end
	ret.totalC=ret.totalC+d[n]
	ret.finished=#ret==1
	return ret
end
function tryTurningOff(n,d)
	local _t1,_t2=d[n-1]-1,d[n+1]-1
	if _t1==-1 then _t1=0 end
	if _t2==-1 then _t2=0 end
	if _t1+d[n]+_t2<4 then return false end
	local ret={finished=true,totalC=d.totalC}
	for index=1,#d do
		if index==n-1 then
			table.insert(ret,d[n-1]+d[n]+d[n+1])
		elseif index~=n and index~=n+1 then
			ret.finished=false
			table.insert(ret,d[index])
		end
	end
	--print("test",table.concat(ret))
	ret.totalC=ret.totalC+4-d[n]
	ret.finished=#ret==1
	return ret
end
--[[test=tryTurningOn(3,{0,1,1,5,4,3,0})
print(table.concat(test))
print(test.totalC)
--]]
--[[test=tryTurningOff(4,{0,1,1,3,4,3,0})
print(table.concat(test))
print(test.totalC)
--]]
function oneInstance(data)
	local retrieve={}
	for n=2,#data-1 do
		if n%2==0 then
			k=tryTurningOff(n,data)
		else
			k=tryTurningOn(n,data)
		end
		if type(k)=="table" then
		table.insert(retrieve,k) end
	end
	return retrieve
end
--[[test=oneInstance({0,1,1,1,4,2,1,3,0})
for _,e in ipairs(test) do
	if type(e)=="table" then
	print(table.concat(e)) end
end
--]]
function checkForFinish(data)
	for _,e2 in ipairs(data) do
		for _2,e in ipairs(e2) do
			--print("C",e.totalC)
			--print("E",table.concat(e),_2)
			--print(total)
			if e.finished and e.totalC<total then
				total=e.totalC
			elseif not e.finished and e.totalC<total then
				return false
			end
		end
	end
	return true
end
--state,datas={0,2,1,2,0,finished=false,totalC=0},{}
datas[0]={{state}}
count=0
nextD={}
total=100
repeat
	nextD[count]={}
	for _,e in ipairs(datas[count]) do
		--print(table.concat(e))
		for _2,e2 in ipairs(e) do
			--[[if type(e2)=="table" then print(table.concat(e2))
			else print(e2) end
--]]
			table.insert(nextD[count],oneInstance(e2))
		end
	end
	datas[count+1]=nextD[count]
	count=count+1
until checkForFinish(datas[count-1])
print(total)
