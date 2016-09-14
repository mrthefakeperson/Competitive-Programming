let n=Scanf.scanf "%i" (fun e->e);;
type node=
|Gray of node*node*node*node
|Black
|White
let rec buildTree()=
 Scanf.scanf "%c" (function
  |'p'->Gray(buildTree(),buildTree(),buildTree(),buildTree())
  |'f'->Black
  |'e'->White
  |_->buildTree()
 )
let rec combine tr1 tr2=
 match (tr1,tr2) with
 |(Black,_)|(_,Black)->Black
 |(White,a)|(a,White)->a
 |(Gray(a,b,c,d),Gray(e,f,g,h))->
  Gray(combine a e,combine b f,combine c g,combine d h)
let rec traverse tr value=
 match tr with
 |Black->value
 |White->0
 |Gray(a,b,c,d)->
  traverse a (value/4)+traverse b (value/4)+traverse c (value/4)+traverse d (value/4)
let oneCase()=
 (*Scanf.scanf "%c" (fun e->());*)
 let tr1= buildTree() in
 (*Scanf.scanf "%c" (fun e->());*)
 let tr2=buildTree() in
 Printf.printf "There are %i black pixels.\n" (traverse (combine tr1 tr2) 1024);;

for e=1 to n do oneCase() done;;