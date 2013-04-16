use std;
import std::io;
import std::vec; 
import std::getopts;

type config = {stress: bool};
fn parse_opts(argv: [str]) -> config {

    let opts = [getopts::optflag("stress")];

    let opt_args = vec::slice(argv, 1u, vec::len(argv));

    alt getopts::getopts(opt_args, opts) {
      getopts::success(m) { ret {stress: getopts::opt_present(m, "stress")} }
      getopts::failure(_) { fail; }
    }

}

fn main(args: [str]) {


	let opts = parse_opts(args);

        let out = io::stdout();
        out.write_line(#fmt["Opts.stress is programatically set to: %b", opts.stress]);


}
