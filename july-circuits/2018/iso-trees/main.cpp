#include <bits/stdc++.h>
using namespace std;

struct WeightedBipartiteEdge {
    const int left;
    const int right;
    const int cost;

    WeightedBipartiteEdge() : left(), right(), cost() {}
    WeightedBipartiteEdge(const int left, const int right, const int cost) : left(left), right(right), cost(cost) {}
};


#define fo(i, n) for(int i = 0, _n = (n); i < _n; ++i)
#define range(i, a, b) for(int i = (a), _n = (b); i < _n; ++i)

static const int oo = std::numeric_limits<int>::max();
static const int UNMATCHED = -1;

struct LeftEdge {
    int right;
    int cost;

    LeftEdge() : right(), cost() {}
    LeftEdge(int right, int cost) : right(right), cost(cost) {}

    const bool operator < (const LeftEdge& otherEdge) const {
        return right < otherEdge.right || (right == otherEdge.right && cost < otherEdge.cost);
    }
};

const std::vector<int> hungarianMinimumWeightPerfectMatching(const int n, const std::vector<WeightedBipartiteEdge> allEdges) {

    // Edge lists for each left node.
    const std::unique_ptr<std::vector<LeftEdge>[]> leftEdges(new std::vector<LeftEdge>[n]);

    {
        int leftEdgeCounts[n], rightEdgeCounts[n];
        std::fill_n(leftEdgeCounts, n, 0);
        std::fill_n(rightEdgeCounts, n, 0);

        fo(edgeIndex, allEdges.size()) {
            const WeightedBipartiteEdge& edge = allEdges[edgeIndex];
            if (edge.left >= 0 && edge.left < n) {
                ++leftEdgeCounts[edge.left];
            }
            if (edge.right >= 0 && edge.right < n) {
                ++rightEdgeCounts[edge.right];
            }
        }

        fo(i, n) {
            if (leftEdgeCounts[i] == 0 || rightEdgeCounts[i] == 0) {
                // No matching will be possible.
                return std::vector<int>();
            }
        }

        // Probably unnecessary, but reserve the required space for each node, just because?
        fo(i, n) {
            leftEdges[i].reserve(leftEdgeCounts[i]);
        }
    }
    // Actually add to the edge lists now.
    fo(edgeIndex, allEdges.size()) {
        const WeightedBipartiteEdge& edge = allEdges[edgeIndex];
        if (edge.left >= 0 && edge.left < n && edge.right >= 0 && edge.right < n) {
            leftEdges[edge.left].push_back(LeftEdge(edge.right, edge.cost));
        }
    }

    // Sort the edge lists, and remove duplicate edges (keep the edge with smallest cost).
    fo(i, n) {
        std::vector<LeftEdge>& edges = leftEdges[i];
        std::sort(edges.begin(), edges.end());

        int edgeCount = 0;
        int lastRight = UNMATCHED;
        fo(edgeIndex, edges.size()) {
            const LeftEdge& edge = edges[edgeIndex];
            if (edge.right == lastRight) {
                continue;
            }
            lastRight = edge.right;
            if (edgeIndex != edgeCount) {
                edges[edgeCount] = edge;
            }
            ++edgeCount;
        }

        edges.resize(edgeCount);
    }

    int leftPotential[n], rightPotential[n];

    fo(i, n) {
        const std::vector<LeftEdge>& edges = leftEdges[i];
        int smallestEdgeCost = edges[0].cost;
        range(edgeIndex, 1, edges.size()) {
            if (edges[edgeIndex].cost < smallestEdgeCost) {
                smallestEdgeCost = edges[edgeIndex].cost;
            }
        }

        // Set node potential to the smallest incident edge cost.
        // This is as high as we can take it without creating an edge with zero reduced cost.
        leftPotential[i] = smallestEdgeCost;
    }

    std::fill_n(rightPotential, n, oo);

    fo(edgeIndex, allEdges.size()) {
        const WeightedBipartiteEdge& edge = allEdges[edgeIndex];
        int reducedCost = edge.cost - leftPotential[edge.left];
        if (rightPotential[edge.right] > reducedCost) {
            rightPotential[edge.right] = reducedCost;
        }
    }

    int leftTightEdgesCount[n];
    std::fill_n(leftTightEdgesCount, n, 0);

    //region Tight edge initialization

    // Here we find all tight edges, defined as edges that have zero reduced cost.
    // We will be interested in the subgraph induced by the tight edges, so we partition the edge lists for
    // each left node accordingly, moving the tight edges to the start.

    fo(i, n) {
        std::vector<LeftEdge>& edges = leftEdges[i];
        int tightEdgeCount = 0;
        fo(edgeIndex, edges.size()) {
            const LeftEdge& edge = edges[edgeIndex];
            int reducedCost = edge.cost - leftPotential[i] - rightPotential[edge.right];
            if (reducedCost == 0) {
                if (edgeIndex != tightEdgeCount) {
                    std::swap(edges[tightEdgeCount], edges[edgeIndex]);
                }
                ++tightEdgeCount;
            }
        }
        leftTightEdgesCount[i] = tightEdgeCount;
    }

    //endregion Tight edge initialization


    // Now we're ready to begin the inner loop.

    // We maintain an (initially empty) partial matching, in the subgraph of tight edges.
    int currentMatchingCardinality = 0;
    int leftMatchedTo[n], rightMatchedTo[n];
    std::fill_n(leftMatchedTo, n, UNMATCHED);
    std::fill_n(rightMatchedTo, n, UNMATCHED);

    //region Initial matching (speedup?)

    // Because we can, let's make all the trivial matches we can.
    fo(i, n) {
        const std::vector<LeftEdge>& edges = leftEdges[i];
        fo(edgeIndex, leftTightEdgesCount[i]) {
            int j = edges[edgeIndex].right;
            if (rightMatchedTo[j] == UNMATCHED) {
                ++currentMatchingCardinality;
                rightMatchedTo[j] = i;
                leftMatchedTo[i] = j;
                break;
            }
        }
    }

    if (currentMatchingCardinality == n) {
        // Well, that's embarassing. We're already done!
        return std::vector<int>(leftMatchedTo, leftMatchedTo + n);
    }

    int rightMinimumSlack[n], rightMinimumSlackLeftNode[n], rightMinimumSlackEdgeIndex[n];

    std::deque<int> leftNodeQueue;
    bool leftSeen[n];
    int rightBacktrack[n];

    // Note: the above are all initialized at the start of the loop.

    //endregion Inner loop state variables

    while (currentMatchingCardinality < n) {

        //region Loop state initialization

        // Clear out slack caches.
        // Note: We need to clear the nodes so that we can notice when there aren't any edges available.
        std::fill_n(rightMinimumSlack, n, oo);
        std::fill_n(rightMinimumSlackLeftNode, n, UNMATCHED);

        // Clear the queue.
        leftNodeQueue.clear();

        // Mark everything "unseen".
        std::fill_n(leftSeen, n, false);
        std::fill_n(rightBacktrack, n, UNMATCHED);

        //endregion Loop state initialization

        int startingLeftNode = UNMATCHED;

        //region Find unmatched starting node

        // Find an unmatched left node to search outward from.
        // By heuristic, we pick the node with fewest tight edges, giving the BFS an easier time.
        // (The asymptotics don't care about this, but maybe it helps. Eh.)
        {
            int minimumTightEdges = oo;
            fo(i, n) {
                if (leftMatchedTo[i] == UNMATCHED && leftTightEdgesCount[i] < minimumTightEdges) {
                    minimumTightEdges = leftTightEdgesCount[i];
                    startingLeftNode = i;
                }
            }
        }

        //endregion Find unmatched starting node

        assert(startingLeftNode != UNMATCHED);

        assert(leftNodeQueue.empty());
        leftNodeQueue.push_back(startingLeftNode);
        leftSeen[startingLeftNode] = true;

        int endingRightNode = UNMATCHED;
        while (endingRightNode == UNMATCHED) {

            //region BFS until match found or no edges to follow

            while (endingRightNode == UNMATCHED && !leftNodeQueue.empty()) {
                // Implementation note: this could just as easily be a DFS, but a BFS probably
                // has less edge flipping (by my guess), so we're using a BFS.

                const int i = leftNodeQueue.front();
                leftNodeQueue.pop_front();

                std::vector<LeftEdge>& edges = leftEdges[i];
                // Note: Some of the edges might not be tight anymore, hence the awful loop.
                for(int edgeIndex = 0; edgeIndex < leftTightEdgesCount[i]; ++edgeIndex) {
                    const LeftEdge& edge = edges[edgeIndex];
                    const int j = edge.right;

                    assert(edge.cost - leftPotential[i] - rightPotential[j] >= 0);
                    if (edge.cost > leftPotential[i] + rightPotential[j]) {
                        // This edge is loose now.
                        --leftTightEdgesCount[i];
                        std::swap(edges[edgeIndex], edges[leftTightEdgesCount[i]]);
                        --edgeIndex;
                        continue;
                    }

                    if (rightBacktrack[j] != UNMATCHED) {
                        continue;
                    }

                    rightBacktrack[j] = i;
                    int matchedTo = rightMatchedTo[j];
                    if (matchedTo == UNMATCHED) {
                        // Match found. This will terminate the loop.
                        endingRightNode = j;

                    } else if (!leftSeen[matchedTo]) {
                        // No match found, but a new left node is reachable. Track how we got here and extend BFS queue.
                        leftSeen[matchedTo] = true;
                        leftNodeQueue.push_back(matchedTo);
                    }
                }

                //region Update cached slack values

                // The remaining edges may be to nodes that are unreachable.
                // We accordingly update the minimum slackness for nodes on the right.

                if (endingRightNode == UNMATCHED) {
                    const int potential = leftPotential[i];
                    range(edgeIndex, leftTightEdgesCount[i], edges.size()) {
                        const LeftEdge& edge = edges[edgeIndex];
                        int j = edge.right;

                        if (rightMatchedTo[j] == UNMATCHED || !leftSeen[rightMatchedTo[j]]) {
                            // This edge is to a node on the right that we haven't reached yet.

                            int reducedCost = edge.cost - potential - rightPotential[j];
                            assert(reducedCost >= 0);

                            if (reducedCost < rightMinimumSlack[j]) {
                                // There should be a better way to do this backtracking...
                                // One array instead of 3. But I can't think of something else. So it goes.
                                rightMinimumSlack[j] = reducedCost;
                                rightMinimumSlackLeftNode[j] = i;
                                rightMinimumSlackEdgeIndex[j] = edgeIndex;
                            }
                        }
                    }
                }

                //endregion Update cached slack values
            }

            //endregion BFS until match found or no edges to follow

            //region Update node potentials to add edges, if no match found

            if (endingRightNode == UNMATCHED) {
                // Out of nodes. Time to update some potentials.
                int minimumSlackRightNode = UNMATCHED;

                //region Find minimum slack node, or abort if none exists

                int minimumSlack = oo;
                fo(j, n) {
                    if (rightMatchedTo[j] == UNMATCHED || !leftSeen[rightMatchedTo[j]]) {
                        // This isn't a node reached by our BFS. Update minimum slack.
                        if (rightMinimumSlack[j] < minimumSlack) {
                            minimumSlack = rightMinimumSlack[j];
                            minimumSlackRightNode = j;
                        }
                    }
                }

                if (minimumSlackRightNode == UNMATCHED || rightMinimumSlackLeftNode[minimumSlackRightNode] == UNMATCHED) {
                    // The caches are all empty. There was no option available.
                    // This means that the node the BFS started at, which is an unmatched left node, cannot reach the
                    // right - i.e. it will be impossible to find a perfect matching.

                    return std::vector<int>();
                }

                //endregion Find minimum slack node, or abort if none exists

                assert(minimumSlackRightNode != UNMATCHED);

                // Adjust potentials on left and right.
                fo(i, n) {
                    if (leftSeen[i]) {
                        leftPotential[i] += minimumSlack;
                        if (leftMatchedTo[i] != UNMATCHED) {
                            rightPotential[leftMatchedTo[i]] -= minimumSlack;
                        }
                    }
                }

                // Downward-adjust slackness caches.
                fo(j, n) {
                    if (rightMatchedTo[j] == UNMATCHED || !leftSeen[rightMatchedTo[j]]) {
                        rightMinimumSlack[j] -= minimumSlack;

                        // If the slack hit zero, then we just found ourselves a new tight edge.
                        if (rightMinimumSlack[j] == 0) {
                            const int i = rightMinimumSlackLeftNode[j];
                            const int edgeIndex = rightMinimumSlackEdgeIndex[j];

                            //region Update leftEdges[i] and leftTightEdgesCount[i]

                            // Move it in the relevant edge list.
                            if (edgeIndex != leftTightEdgesCount[i]) {
                                std::vector<LeftEdge>& edges = leftEdges[i];
                                std::swap(edges[edgeIndex], edges[leftTightEdgesCount[i]]);
                            }
                            ++leftTightEdgesCount[i];

                            //endregion Update leftEdges[i] and leftTightEdgesCount[i]

                            // If we haven't already encountered a match, we follow the edge and update the BFS queue.
                            // It's possible this edge leads to a match. If so, we'll carry on updating the tight edges,
                            // but won't follow them.
                            if (endingRightNode == UNMATCHED) {
                                // We're contemplating the consequences of following (i, j), as we do in the BFS above.
                                rightBacktrack[j] = i;
                                int matchedTo = rightMatchedTo[j];
                                if (matchedTo == UNMATCHED) {
                                    // Match found!
                                    endingRightNode = j;
                                } else if (!leftSeen[matchedTo]) {
                                    // No match, but new left node found. Extend BFS queue.
                                    leftSeen[matchedTo] = true;
                                    leftNodeQueue.push_back(matchedTo);
                                }
                            }
                        }
                    }
                }
            }

            //endregion Update node potentials to add edges, if no match found
        }

        // At this point, we've found an augmenting path between startingLeftNode and endingRightNode.
        // We'll just use the backtracking info to update our match information.

        ++currentMatchingCardinality;

        //region Backtrack and flip augmenting path

        {
            int currentRightNode = endingRightNode;
            while (currentRightNode != UNMATCHED) {
                const int currentLeftNode = rightBacktrack[currentRightNode];
                const int nextRightNode = leftMatchedTo[currentLeftNode];

                rightMatchedTo[currentRightNode] = currentLeftNode;
                leftMatchedTo[currentLeftNode] = currentRightNode;

                currentRightNode = nextRightNode;
            }
        }

        //endregion Backtrack and flip augmenting path
    }

    // Oh look, we're done.
    return std::vector<int>(leftMatchedTo, leftMatchedTo + n);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ntree(n);
    fo(i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        ntree[a].push_back(b);
        ntree[b].push_back(a);
    }
    fo(i, n) {
        ntree[i].push_back(n);
        sort(ntree[i].begin(), ntree[i].end());
    }

    vector<vector<int>> mtree(m);
    fo(i, m - 1) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        mtree[a].push_back(b);
        mtree[b].push_back(a);
    }
    fo(i, m) {
        mtree[i].push_back(m);
        sort(mtree[i].begin(), mtree[i].end());
    }

    vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(m));
    for(int ni = 0; ni < n; ++ni) for(int mi = 0; mi < m; ++mi) {
        dp[ni][mi] = vector<vector<int>>(ntree[ni].size(), vector<int>(mtree[mi].size(), -1));
    }

    function<int(int, int, int, int)> solve = [&](int ni, int mi, int ne, int me) {
        if(ni == n || mi == m) return 0;
        // cout << "(" << ni << ", " << mi << ", " << ne << ", " << me << endl;
        int nei = lower_bound(ntree[ni].begin(), ntree[ni].end(), ne) - ntree[ni].begin();
        assert(nei >= 0);
        assert(nei < ntree[ni].size());
        int mei = lower_bound(mtree[mi].begin(), mtree[mi].end(), me) - mtree[mi].begin();
        assert(mei >= 0);
        assert(mei < mtree[mi].size());

        if(dp[ni][mi][nei][mei] != -1) {
            return dp[ni][mi][nei][mei];
            // cout << ")" << endl;
        }
        else {
            int k = max(ntree[ni].size(), mtree[mi].size());
            // cout << k << endl;
            // cout << nei << endl;
            // cout << mei << endl;
            vector<WeightedBipartiteEdge> es;
            for(int nic = 0; nic < k; ++nic) {
                for(int mic = 0; mic < k; ++mic) {
                    if(nic == nei || mic == mei || nic >= ntree[ni].size() || mic >= mtree[mi].size()) {
                        es.emplace_back(nic, mic, -0);
                    } else {
                        // cout << nic << endl;
                        // cout << mic << endl;
                        es.emplace_back(nic, mic, -solve(ntree[ni][nic], mtree[mi][mic], ni, mi));
                    }
                }
            }

            auto v = hungarianMinimumWeightPerfectMatching(k, es);
            int t = 0;
            for(int i = 0; i < v.size(); ++i) {
                if(i < ntree[ni].size() && v[i] < mtree[mi].size()) {
                    if(ntree[ni][i] != ne && mtree[mi][v[i]] != me)
                        t += solve(ntree[ni][i], mtree[mi][v[i]], ni, mi);
                }
            }
            dp[ni][mi][nei][mei] = t + 1;
            // cout << ")" << endl;
            return t + 1;
        }
    };


    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cout << n + m - 2 * solve(i, j, n, m) << " ";
        }
        cout << endl;
    }
}
