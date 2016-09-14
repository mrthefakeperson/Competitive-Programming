change=tonumber(io.read())
x=io.read()
dInM={}
for x=0,12 do dInM[x]=31 end
dInM[4],dInM[6],dInM[9],dInM[11],dInM[2]=30,30,30,30,28
--for x=1,12 do dInM[x-12]=dInM[x] end
years,months,days=tonumber(x:sub(1,4)),tonumber(x:sub(6,7)),tonumber(x:sub(9,10))
hours=tonumber(x:sub(12,13))
hours=hours-change
while hours<0 do
	days,hours=days-1,hours+24
end
while days<1 do
	--print (months,days)
	months,days=months-1,days+dInM[months-1]
	if months<1 then months,years=months+12,years-1 end
end
--[[while months<1 do
	months,years=months+12,years-1
end]]
print(string.format("%d/%02d/%02d %02d%s",years,months,days,hours,x:sub(14)))
