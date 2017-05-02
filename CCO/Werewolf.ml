open Scanf
open Printf
open Int64
let ppl,suspects,accusations=scanf "%i %i %i\n" (fun a b c->(a,b,c));;
let connect=Array.init (ppl+1) (fun _->[])
let used=Array.init (ppl+1) (fun _->false);;
for e=1 to accusations do
	scanf "%c %i %i\n" (fun q a b->
		if q='A'
		 then connect.(a)<-(b,true)::connect.(a)
		 else connect.(a)<-(b,false)::connect.(a);
		used.(b)<-true
	)
done;;
for e=1 to ppl do
	if not used.(e) then connect.(0)<-(e,true)::connect.(0)
done;;

let (|>) n f=f n
let cn b=if b then 1 else 0
let visited=Array.init (ppl+1) (fun _->[|None;None|]);;
let subtree=Array.make (ppl+1) 0
let rec fill node=
	let ss=ref 0 in
	(
	match connect.(node) with
	|[]->ss:=1
	|_->
		List.iter (fun (e,_)->ss:= !ss+fill e) connect.(node)
		);
	if suspects< !ss then ss:=suspects;
	subtree.(node)<- !ss+1;
	!ss+1;;
fill 0
let rec help node bw=
	match visited.(node).(cn bw) with
	|None->
		let ways=Array.make (subtree.(node)+1) 0 in
		ways.(cn bw)<-1;
		let ll=
			if bw
			 then
				List.map (fun (e,flip)->
					if flip then help e (not bw) else help e bw
				) connect.(node)
			 else
				List.map (fun (e,_)->
					let a1,a2,a3=help e bw,help e (not bw),Array.make (subtree.(e)+1) 0 in
					Array.iteri (fun i e->a3.(i)<-rem (add (of_int e)(of_int a2.(i))) 1000000007L |> to_int) a1;
					a3
				) connect.(node)
		in
		let n_squared=ref 0 in (*optimization*)
		List.iteri (fun i eee->
			let buffer=Array.make (subtree.(node)+1) 0 in
			for e=0 to Array.length eee-1 do
				let itm=if i=0 then Array.length eee-1 else !n_squared in
				for ee=0 to itm do
					if e+ee<=subtree.(node) then
					 buffer.(e+ee)<-rem (add (of_int buffer.(e+ee))(mul (of_int eee.(e))(of_int ways.(ee)))) 1000000007L |> to_int
				done
			done;
			Array.iteri (fun i e->
				ways.(i)<-e
			) buffer;
			n_squared:= !n_squared+Array.length eee-1;
		) ll;
		visited.(node).(cn bw)<-Some(ways);
		ways
	|Some(ways)->ways;;
if suspects=0
 then printf "1\n"
 else
  printf "%i\n" ((help 0 false).(suspects));;