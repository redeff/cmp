fn is_sq(n: i64) -> bool {
}

fn main() {
    let n = 0i64;
    loop {
        n += 1;
        if is_sq(5 * n * n + 2 * n + 1) {
            println!("{}", n);
        }
    }
}
