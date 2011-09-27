use std;
import std::io;
import std::vec; 
import std::getopts;

type config = {ninjas: bool, pirates: bool};


fn main(args: [str]) {

	let opt_args = vec::slice(args, 1u, vec::len(args));

	/* Is this a comment */ 
	let opts = [getopts::optflag("ninjas")];


	alt getopts::getopts(opt_args, opts) {
		getopts::success(m) { let x = { ninjas: getopts::opt_present(m, "ninjas"), pirates: getopts::opt_present(m, "pirates } }
		getopts::failure(_) { let config x = { ninjas: false, pirates: false } }
	}


}
