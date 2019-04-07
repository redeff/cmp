#!/usr/bin/env python3
t = readline_int()           
n, b, f = readline_int_list()
printline 01101 to stdout
                           // the problem statement.
flush stdout
response = readline_str()    // Reads 111 into response. (At this point, we
                           // could determine the answer; the remaining
                           // queries are just examples!)
printline 00110 to stdout
flush stdout
response = readline_str()    // Reads 010 into response
printline 01010 to stdout
flush stdout
response = readline_str()    // Reads 100 into response
printline 11010 to stdout
flush stdout
response = readline_str()    // Reads 100 into response
printline 0 3 to stdout      // Guesses the answer. Notice that we were
                           // not required to use all 10 of our allowed
                           // queries.
flush stdout
verdict = readline_int()     // Reads 1 into verdict. We got that test case
                           // right!
n, b, f = readline_int_list()  // Reads 2, 1, 10 into n, b, f.
printline 01 to stdout       // 01 is a query, not a guess at the final
                           // answer (if we wanted to guess that just
                           // worker 1 were broken, we would have to
                           // send 1 as we do below)
flush stdout
response = readline_str()    // Reads 1 into response.
printline 1 to stdout        // Makes a (bad) wild guess.
verdict = readline_str()     // Reads -1 into verdict.
exit                         // exits to avoid an ambiguous TLE error
