use std::mem;

struct Divisor {
    p: i64,
    a: isize,
}

fn factor(mut n: i64) -> Vec<Divisor> {
    let ds = Vec::new();
    let i = 2i64;
    while i * i <= n {
        if n % i == 0 {
            ds.push(Divisor {p: i, i: 0});
            while n % i == 0 {
                ds[ds.len()].a += 1;
                n /= i;
            }
        }
    }

    if n != 1 {
        ds.push(Divisor {p: n, i: 1});
    }

    ds
}

fn gcd(mut a: i64, mut b: i64) -> i64 {
    if a < b {
        mem::swap(&mut a, &mut b)
    }

    while b != 0 {
        a = a % b;
        mem::swap(&mut a, &mut b);
    }

    a
}

fn factor_divisor(n: i64, ds : &Vec<Divisor>) {
    let mut my = ds.copy();
    for i in 0..my.len() {
        my[i].a = 0;
        let pa = 1;
        while n % pa == 0 && my[i].a <= ds[i].a {
            pa *= my[i].p;
            my[i].a += 1;
        }

        my[i].a -= 1;
    }

    my
}

fn mexp(b: i64, e: i64, m: i64) -> i64 {
    if e == 0 { 1 }
    else {
        let rec = mexp(b, e/2, m);
        rec * rec % m * if e % 2 != 0 { b } else { 1 } % m
    }
}

fn proot(p: i64, Vec<Divisor> &ds) {
    (2..p).filter(|r: i64| ds .all(|d| mexp(r, (p-1) / d.p, p) != 1)).next().unwrap();
}

fn main() {
    
}
