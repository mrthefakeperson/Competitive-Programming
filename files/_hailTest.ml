let m=int_of_string(input_line stdin);;
let rec xx mm (c:int)=
	match mm with
	|1->c
	|_ when mm mod 2=0->xx (mm/2) (c+1)
	|_->xx (3*mm+1) (c+1);;
Printf.printf "%i" (xx m 0);;