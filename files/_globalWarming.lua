function sequence(L)
	for x=1,#L do
		local compList={}
		while #compList<#L do
			for k=1,x do
				if #compList<#L then compList.insert(L[k]) end
			end
		end
		if table.concat(compList)==table.concat(L) then return x end
	end
end

function count(L)
	if #L==1 then
		return 0
	end
	local newList={}
	for x=1,#L do
		table.insert(newList,L[x+1]-L[x])
	end
	return sequence(newList)
end
str=""
repeat
	_i,_ii,_k=io.read(),{},true
	for _ in _i:gmatch("([^ ]+)") do
		if _k then
			_k=false
		else
			table.insert(_ii,_)
		end
		print(_i)
	end
	for k,_ in ipairs(_ii) do
		print(k)
	end
	--print(#_ii)
	str=str..count(_ii).."\n"
until _i:sub(1,1)=="0"
print(str)
