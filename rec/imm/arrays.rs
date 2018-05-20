struct Edge<Ds, Delta> {
    delta: Delta,
    ptr: Rc<VersionGraph>,
}

trait DataDelta {
    fn opposite(self) -> Self;
}

trait DataStructure<Delta> where Delta : DataDelta {
    fn apply(&mut self, delta: Delta);
    fn copy(self) -> Self;
}

enum VersionGraph<Ds, Delta> 
where 
{
    Leaf {
        ns: Ds,
        prv: Edge<Ds, Delta>,
    },
    Joint {
        ns: Ds,
        conn: Rc<Vec<Edge<Ds, Delta>>>,
    },
    Mid {
        prv: Edge<Ds, Delta>,
        nxt: Edge<Ds, Delta>,
    }
}

impl VersionGraph<Ds, Delta> {
    fn data(self) -> Option<Ds> {
        match(self) {
            Leaf {ns, ..} => Some(ns),
            Joint {ns, ..} => Some(ns)
            Mid {..} => None,
        }
    }

    fn modify
}
