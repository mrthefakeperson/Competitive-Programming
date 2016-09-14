
_side,box=io.read(),{}
if _side%2==1 then
	for _=0.5-_side/2.0,_side/2 do
		box[_]={}
		_row,rowdex=io.read(),1
		for i=0.5-_side/2.0,_side/2 do
			box[_][i]=_row:sub(rowdex,rowdex)
			--print(_row:sub(rowdex,rowdex),i,_)
			rowdex=rowdex+1
		end
	end
else
	for _=-_side/2,_side/2 do
		box[_]={}
		if _~=0 then
			_row,rowdex=io.read(),1
			for i=-_side/2,_side/2 do
				if i~=0 then
					box[_][i]=_row:sub(rowdex,rowdex)
					--print(_row:sub(rowdex,rowdex),i,_)
					rowdex=rowdex+1
				else box[_][i]="+"
				end
			end
		else
			for i=-_side/2,_side/2 do box[_][i]="+" end
		end
	end
end
vx=math.floor(_side/2)
--[[
for y=-vx,vx do
	temp=""
	for x=-vx,vx do
		--print(y,x)
		--print(box[y][x])
		temp=temp..box[y][x]
	end
	print(temp)
end
--]]
function voxInBox(list)
	local horizontal={"OO","..",[[\/]],[[/\]],"((","))","++"}

	for _,e in ipairs(list) do
		eIn=false
		for _2,e2 in ipairs(horizontal) do
			if e==e2 then eIn=true end
		end
		if not eIn then return false end
	end
	return true
end
function vox_inbox(list)
	local vertical={"OO","..",[[/\]],[[\/]],"()",")(","++"}

	for _,e in ipairs(list) do
		eIn=false
		for _2,e2 in ipairs(vertical) do
			if e==e2 then eIn=true end
		end
		if not eIn then return false end
	end
	return true
end
function boxingVox(list)
	local diagonal={"OO","..",[[//]],[[\\]],[[++]]}
	for _,e in ipairs(list) do
		eIn=false
		for _2,e2 in ipairs(diagonal) do
			if e==e2 then eIn=true end
		end
		if not eIn then return false end
	end
	return true
end
list1,list2,list3,list4={},{},{},{}
for y=-vx,vx do
	for x=-vx,vx do
		_tp=box[y][x]
		if y>=0 then table.insert(list1,_tp..box[-y][x]) end
		if x>=0 then table.insert(list2,_tp..box[y][-x]) end
		table.insert(list3,_tp..box[x][y])
		table.insert(list4,_tp..box[-x][-y])
	end
end
final=0
if voxInBox(list1) then final=final+1 end
if vox_inbox(list2) then final=final+1 end
if boxingVox(list3) then final=final+1 end
if boxingVox(list4) then final=final+1 end
print(final)
