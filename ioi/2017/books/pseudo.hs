-- disjoint sets in a vector that maps numbers from the same set
-- to the same number (si if disjoint_sets[i] == disjoint_sets[j]
-- then i and j asre in the same set
--
-- This procedure returns a list of operations of the
-- form (i, j), such that applying them makes the thing
-- I want
recursive procedure(Disjoint_sets, N)
    create an empty hash table Hash from Ints to Vec Ints
    for (elem, index) in disjoint_sets
        add elem to the end of the vector Hash[index], create it if it doesn't exist
    
    -- Now each vector Hash[i] is sorted. We will do the following

    check if for any Vec in Hash
        the maximum of the distances between two
        consecutive elements is less than N/2

        and

        N - (the distance between the extremes) is less than N/2

        -- This means the polygon representing this set
        -- contains the center
    
    if such Vec exists
        split the Disjoint_sets vector into pieces separated
        by elements of Vec. you get a vector of vectors that
        represents the pieces called Pieces
        -- This can be done efficiently by noting that you
        -- can tell that the ith number is an element of Vec
        -- iff Disjoint_sets[i] == Disjoint_sets[some element Vec]
        
        call procedure for each Piece in Pieces (copy it into a
        vector first) and contatenate their results in Concat

        for Piece in Pieces
            attach to it a HashSet of all the Disjoint_set[i] where i is in Piece

        join the HashSets pairwise and check wether an element is repeated
        for each repeated element i
            append to Concat the pair (i, j) where j is the index of Vec in Hash

        return Concat

    else
        every Vec in Hash has a pair (i, j) of consecutive (or extreme)
        elements shuch that (if i < j then j - i < N/2 else N - (i - j) < N/2)
        -- otherwise the other condition would have held
        let Hash'[index of Vec] represent that pair

        let List be the pairs in Hash' but sorted by ending element

        traverse the list with pointer Ptr
            while the ending pos if Ptr.prev is greater than the begin pos of Ptr
                Ptr.begin min = Ptr.prev.end_pos
                delete Ptr.prev

        then do that over the edge of the list (from the last to the first)

        -- Now List contains non-overlapping intervals in then circle
        
        Take the biggest interval in List
        if its smaller than N/2
            do the recursion on each interval

        else 

        
