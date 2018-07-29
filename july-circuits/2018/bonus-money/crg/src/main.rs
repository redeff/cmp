use std::io;
use std::io::prelude::*;
const p : i64 = 1000000007;

fn conv(a : &[i64], b: &[i64]) -> Vec<i64> {
    let t = a.len();
    let k = a.len()/2;

    if t == 1 {
        vec![(a[0] * b[0]) % p, 0]
    } else {
        
        let aa: Vec<_> = (0..k).map(|i| (a[i] + a[k + i]) % p).collect();
        let bb: Vec<_> = (0..k).map(|i| (b[i] + b[k + i]) % p).collect();

        let x = conv(&a[..k], &b[..k]);
        let y = conv(&aa[..], &bb[..]);
        let z = conv(&a[k..], &b[k..]);

        let mut out = vec![0; 2*t];
        for i in 0..t {
            out[i] += x[i];
            out[k + i] += p + p + y[i] - x[i] - z[i];
            out[t + i] += z[i];
        }

        out.iter().map(|x| x % p).collect()
    }
}

const big : usize = 64;

fn mult(
    rec: &[i64],
    a: &[i64],
    b: &[i64],
) -> Vec<i64> {

    let mut c = conv(a, b);

    let top = conv(&c[3*big..], rec);
    for i in 0..2*big {
        c[i + big] += top[i];
        c[i + big] %= p;
    }

    let bot = conv(&c[2*big..3*big], rec);
    for i in 0..2*big {
        c[i] += bot[i];
        c[i] %= p;
    }

    return c.iter().take(2*big).map(|x| x.clone()).collect();
}

fn sq(rec: &[i64]) -> Vec<i64> {
    let mut buffa = conv(rec, rec);

    for i in 0..big {
        let c = 2*big - 1 - i;
        for j in 0..big {
            buffa[c - big + j] += (buffa[c] * rec[j]) % p;
            buffa[c - big + j] %= p;
        }
    }

    buffa.iter().take(big).map(|x| x.clone()).collect()
}

fn pw(rec: &[i64], a: &[i64], e: usize) -> Vec<i64> {
    if e == 0 {
        let mut out = vec![0; 2*big];
        out[0] = 1;
        out
    } else if e == 1 {
        a.iter().map(|x| x.clone()).collect()
    } else if e == 2 {
        mult(rec, a, a)
    } else {
        let mut r = pw(rec, a, e/2);
        r = mult(rec, &r[..2*big], &r[..2*big]);
        if e % 2 != 0 {
            r = mult(rec, &r[..], a);
        }

        r
    }
}



fn main() {
    let coeff = vec![
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, -1, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, -1, -1, 1, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, -2, 0, 0, 1, 1, -1, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 1, 1, 0, 0, -1, -1, -1, 1, 1, 1, 0, 0, -1, -1, 1, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 0, 0, -1, 0, -2, 0, 1, 1, 1, 1, 0, -2, 0, -1, 0, 0, 1, 1, -1, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, -1, 0, -1, -1, 0, 1, 1, 2, 0, 0, 0, -2, -1, -1, 0, 1, 1, 0, 1, 0, 0, -1, -1, 1, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, -1, 0, -1, 0, -1, 0, 1, 2, 1, 0,
1, -1, -1, -2, -1, -1, 1, 0, 1, 2, 1, 0, -1, 0, -1, 0, -1, 0, 0, 1, 1, -1, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 2, 1, 1, 1, 0, -1, -1, -1, -2, -1, -1, 1, 1, 2, 1, 1, 1, 0, -1, -1, -1, -2, 0, 1, 0, 0, 1, 0, 1, 0, 0, -1, -1, 1, ],
vec![0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, -1, 0, -1, 0, 0, 0, -1, 1, 1, 1, 2, 0, 0, -1, -1, -1, -1, -3, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, -3, -1, -1, -1, -1, 0, 0, 2, 1, 1, 1, -1, 0, 0, 0, -1, 0, -1, 0, 0, 1, 1, -1, ],
    ];

    let mut dp = vec![vec![0; 2*big + 11]; 11];
    dp[0][0] = 1;

    for k in 1..11 {
        for n in 1..2*big + 11 {
            if n >= k {
                dp[k][n] += dp[k][n - k];
                dp[k][n] %= p;
            }

            if k >= 1 && n >= 1 {
                dp[k][n] += dp[k - 1][n - 1];
                dp[k][n] %= p;
            }
        }
    }

    let t : usize = {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let v: Vec<_> = input.split_whitespace().collect();
        v[0].parse::<usize>().unwrap().clone()
    };

    for _ in 0..t {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let (k, m) : (usize, _) = {
            let v : Vec<_> = input.split_whitespace().collect();
            (v[0].parse::<usize>().unwrap(), v[1])
        };
        /*
        let k = 10;
        let m = "01";
        */

        // let rec = vec![0; big];

        let rec: Vec<_> = coeff[k].iter().map(|x| (x + p) % p).collect();
        let rec = sq(&rec[..]);

        let mut total = vec![0; 2*big];
        total[0] = 1;

        let mut curr = vec![0; 2*big];
        curr[1] = 1;

        for b in m.as_bytes().iter().rev() {
            total = mult(&rec[..], &total[..], &pw(&rec[..], &curr[..], (b - b'0') as usize)[..]);
            curr = pw(&rec[..], &curr[..], 10);
        }
        
        let mut fin = 0;
        for i in 0..2*big {
            fin += (total[i] * dp[k][i + k]) % p;
            fin %= p;
        }

        println!("{}", fin);
    }

    // conv(&a[..], &b[..], &mut c[..], &mut d[..], &mut e[..]);

}
