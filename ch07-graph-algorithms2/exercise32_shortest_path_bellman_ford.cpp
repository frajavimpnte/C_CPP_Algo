/*
We can use the Bellman-Ford algorithm to handle graphs with negative weights. It
replaces Dijkstra's method of greedy selection with an alternative approach of iterating
across every edge in the graph V – 1 times (where V is equal to the total number of
vertices) and finding progressively optimal distance values from the source node across
each iteration. Naturally, this gives it a higher asymptotic complexity than Dijkstra's
algorithm, but it also allows it to produce correct results for graphs that Dijkstra's
algorithm would misinterpret. The following exercise shows how to implement the
Bellman-Ford algorithm.
*/