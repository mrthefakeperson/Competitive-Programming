let getLine()=int_of_string (input_line stdin)
let desired=getLine()
let k=getLine()
let clubs=Array.init k (fun _->getLine())
let searchList,counter,visited=ref [0],ref 0,Array.init (desired+101) (fun _->false);;
while List.length (!searchList)>0 && not(List.exists ((=) desired) !searchList) do
	counter:= !counter+1;
	let nList=ref [] in
	List.iter (fun e->Array.iter (fun ee->
		if not(visited.(e+ee)) && e+ee<=desired then
			nList:=(e+ee):: !nList;visited.(e+ee)<-true
		) clubs) !searchList;
	(*List.iter (fun e->if e=desired then poss:=true) !searchList;*)
	(*List.iter (Printf.printf "%i ") !searchList;Printf.printf "\n";*)
	searchList:= !nList
done;;
if List.exists ((=) desired) !searchList then Printf.printf "Roberta wins in %i strokes." !counter else Printf.printf "Roberta acknowledges defeat."