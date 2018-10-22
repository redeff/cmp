use std::io;
use std::mem;
const BOUND: usize = 200005;

struct PreCalc {
    mu: Vec<i32>,
    radical: Vec<i32>,
    // squarefrees: Vec<i32>,
    divisors: Vec<Vec<i32>>,
    // exists: [bool; BOUND],
}

fn find_match(pre : &PreCalc, target: &Vec<bool>, exists: &Vec<bool>) -> Vec<usize> {
    // let mut partials = [Vec::new(); BOUND];
    let partials : Vec<Vec<i32>> = (0..BOUND).map(|m| {
        if m == 0 {
            Vec::new()
        } else if pre.radical[m] as usize != m {
            Vec::new()
        } else {
            // m is squarefree
            let mut v = vec![0; (BOUND + m - 1) / m];
            let siz = (BOUND + m - 1) / m;
            for i in 1..siz {
                v[i] = v[i-1] + if target[i * m] { 1 } else { 0 };
            }

            v
        }
    }).collect();

    /*
    for p in partials.iter() {
        for i in p {
            print!(" {}", i);
        }
        println!("");
    }
    */

    let out = (0..BOUND).map(|i| {
        if i == 0 || !exists[i] || pre.radical[i] != i as i32 {
            BOUND
        } else {
            let mut lo = 0;
            let mut hi = BOUND;
            while hi - lo > 1 {
                let mid = (hi + lo) / 2;
                if pre.divisors[i].iter().map(|d| {
                    let d = d.clone();
                    if pre.radical[d as usize] == d {
                        // println!("Debug {} {}", d, mid);
                        let mid = mid / d as usize;
                        // println!("Debug {} {}", d, mid);
                        pre.mu[d as usize] * partials[d as usize][mid]
                    } else {
                        0
                    }
                }).sum::<i32>() != 0 {
                    hi = mid;
                } else {
                    lo = mid;
                }
            }
            hi
        }
    }).collect();

    out
}

fn init() -> PreCalc {
    let mut pre = PreCalc {
        mu: vec![1; BOUND],
        radical: vec![1; BOUND],
        divisors: vec![vec![]; BOUND],
    };

    for d in 1..BOUND {
        let is_prime = pre.radical[d] == 1;
        for m in 1..((BOUND + d - 1)/d) {
            if is_prime {
                pre.mu[d * m] *= -1;
                pre.radical[d * m] *= d as i32;
            }

            pre.divisors[d * m].push(d as i32);
        }
    }

    for i in 0..BOUND {
        if pre.radical[i] != i as i32 {
            pre.mu[i] = 0;
        }
    }

    pre
}

struct Uf {
    color: Vec<usize>,
    sets: Vec<Vec<usize>>,
}

impl Uf {
    fn new (n: usize) -> Uf {
        let mut color = vec![0; n];
        let mut sets = vec![Vec::new(); n];
        for i in 0..n {
            color[i] = i;
            sets[i].push(i);
        }
        Uf {
            color: color,
            sets: sets,
        }
    }

    fn merge(&mut self, a: usize, b: usize) -> bool {
        let cap = self.color[a];    
        let cbp = self.color[b];    
        if cap == cbp {
            false
        } else {
            let p = self.sets[cap].len() < self.sets[cbp].len();
            let ca = if p { cbp } else { cap };
            let cb = if p { cap } else { cbp };

            for i in self.sets[cb].iter() {
                self.color[i.clone()] = ca;
            }

            let mut v = Vec::new();
            mem::swap(&mut self.sets[cb], &mut v);
            // mem::swap(&mut self.sets[ca], &mut v);
            for i in v {
                self.sets[ca].push(i.clone());
            }

            true
        }
    }

    fn color(&self, a: usize) -> usize {
        self.color[a]
    }
}

fn lg(n: u32) -> u32 {
    let mut i = 0;
    let mut p = 1;
    while p <= n {
        p *= 2;
        i += 1;
    }

    i
}

fn step(pre: &PreCalc, exists: &Vec<bool>, uf: &mut Uf) -> bool {
    let n = exists.len();
    let mut changed = false;
    for e in 0..lg(n as u32) {
        for b in vec![true, false] {
            let mut target = vec![false; BOUND];
            for i in 0..BOUND {
                if exists[i] && ((uf.color(i) as u32 & (1u32 << e) == 0) ^ b) {
                    target[i] = true;
                }
            }

            let v = find_match(&pre, &target, exists);
            for (a, b) in v.iter().enumerate() {
                let a = a.clone();
                let b = b.clone();
                if a < BOUND && b < BOUND {
                    changed = changed || uf.merge(a, b);
                }
            }
        }
    }

    changed
}

fn main() {
    let mut exists = vec![false; BOUND];
    let pre = init();

    {
        let mut tmp = String::new();
        io::stdin().read_line(&mut tmp).unwrap();
    }
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    for x in line.split_whitespace() {
        let x = x.parse::<usize>().unwrap();
        // println!("{}", x);
        exists[x] = true;
    };

    /*
    for x in pre.mu.iter() {
        print!(" {}", x);
    }
    println!("");
    */

    

    let mut uf = Uf::new(BOUND);
    while step(&pre, &exists, &mut uf) {
        for i in 0..BOUND {
            println!("{} {}", i, uf.color(i));
        }
    }

    /*
    for i in 0..BOUND {
        println!("{} {}", i, uf.color(i));
    }
    */
    println!("Done");
    // println!();
}
