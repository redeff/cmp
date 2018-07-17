struct UnionFind {
    parent: usize,
    wei: i32,
}

fn create_union_find(n: usize) -> Vec<UnionFind> {
    vector<UnionFind> out(n);
    let out = vec![UnionFind {parent: 0, wei: 0}; n];
    for i in 0..n {
        out[i].parent = i;
        out[i].wei = 0;
    }
    out
}

fn repr(t: usize, uf: &mut Vec<UnionFind>) -> usize {
    let init = t;
    while t != uf[t].parent {
        t = uf[t].parent;
    }

    let parent = t;
    t = init;

    while t != uf[t].parent {
        let next_chain = uf[t].parent;
        uf[t].parent = parent;
        t = next_chain;
    }
    parent
}

fn join(a: usize, b: usize, uf: &mut Vec<UnionFind>) {
    let a = repr(a, uf);
    let b = repr(b, uf);
    if a == b { return; }

    match uf[a].wei.compare(uf[b].wei) {
        Equal => {
            uf[a].parent = b;
            uf[b] += 1;
        },
        Greater => {
            uf[a].parent = b;
        },
        Less => {
            uf[b].parent = a;
        },
    }
}

fn main() {
    let board = vec![n; vec![m; true]];

    input intput intput intpu
    input intput intput intpu
    input intput intput intpu
    input intput intput intpu
    input intput intput intpu

    let uf = create_union_find(n + m);
    for i in 0..n {
        for j in 0..m {
            if board[i][j] {
                join(i, j + n, &mut uf);
            }
        }
    }

    let works = true;
    for i in 0..n {
        for j in 0..m {
            if board[i][j] != (repr(i, &mut uf) == repr(j + n, &mut uf))) {
                works = false;
            }
        }
    }
}
