_side,box,final=io.read(),{},0
h,v,cnst=true,true,math.ceil(_side/2)
function vert(strg)
	for x=1,cnst do
		local _tp=strg:sub(x,x)..strg:sub(_side+1-x,_side+1-x)
		if not(_tp=="OO" or _tp==".." or _tp==[[\/]] or _tp==[[/\]] or _tp=="()" or _tp==")(") then
			return false
		end
	end
	return true
end
function horz(lst,index)
	for x=1,_side do
		local _tp=lst[index]:sub(x,x)..lst[_side+1-index]:sub(x,x)
		if not (_tp=="OO" or _tp==".." or _tp==[[\/]] or _tp==[[/\]] or _tp=="((" or _tp=="))") then
			return false
		end
	end
	return true
end
function dg1(lst)
	for x=_side,1,-1 do
		for y=1,x do
			local _tp=lst[x]:sub(y,y)..lst[y]:sub(x,x)
			--print(_tp,x,y)
			if not (_tp=="OO" or _tp==".." or _tp==[[\\]] or _tp==[[//]]) then
				return false
			end
		end
	end
	return true
end
function dg2(lst)
	for x=1,_side do
		for y=1,x do
			local _tp=lst[x]:sub(y,y)..lst[_side+1-y]:sub(_side+1-x,_side+1-x)
			--print(_tp,x,y)
			if not (_tp=="OO" or _tp==".." or _tp==[[\\]] or _tp==[[//]]) then
				return false
			end
		end
	end
	return true
end
for _=1,_side do
	_tp=io.read()
	table.insert(box,_tp)
	if not vert(_tp) then v=false end
	if (_side%2==1 and _>=cnst) or (_side%2==0 and _>cnst) then
		if not horz(box,_) then h=false end
	end
end
if v then final=final+1 end
if h then final=final+1 end
if dg1(box) then final=final+1 end
if dg2(box) then final=final+1 end
print(final)
