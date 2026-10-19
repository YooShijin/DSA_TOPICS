# Tree Traversals and Euler Tours (CP)

## 1. Preorder / DFS Entry Order

Visit a node when entering it, then recursively visit its children.

- Each node appears exactly once.
- `tin[u]`: index when node `u` is first visited.
- `tout[u]`: exclusive index immediately after its subtree in preorder.

### Main property

The subtree of `u` occupies a contiguous range:

`[tin[u], tout[u])`

### Uses

- Subtree sum, minimum, maximum queries using a segment tree or Fenwick tree.
- Subtree updates using lazy propagation.
- Flattening a tree into an array.
- Checking whether `u` is an ancestor of `v`:

  `tin[u] <= tin[v] && tin[v] < tout[u]`

- Subtree size:

  `size[u] = tout[u] - tin[u]`

### How to think

DFS visits an entire subtree before leaving it, so all nodes in that subtree become contiguous in preorder.

---

## 2. Entry/Exit Euler Tour (2N Events)

Record a node twice:

- On entering the node.
- On leaving the node after processing all its children.

Store entry and exit times, often called `tin` and `tout`.

### Main property

For a rooted tree, `u` is an ancestor of `v` iff:

`tin[u] <= tin[v] && tout[v] <= tout[u]`

This assumes inclusive entry/exit timestamps from the same DFS clock.

### Uses

- Ancestor checks.
- Subtree queries when using entry events to store values and exit events as zero.
- Tree difference techniques and subtree accumulation.
- Some offline tree-query techniques.

### Important

This is not the same as preorder flattening: every node has both an entry and an exit event.

---

## 3. Full Euler Tour for LCA (2N - 1 Entries)

Record a node:

- When entering it.
- Again whenever DFS returns to it from a child.

For a tree with `N` nodes, the tour contains `2N - 1` entries.

Also store:

- `euler[i]`: node at position `i`.
- `depthEuler[i]`: depth of that occurrence.
- `first[u]`: first occurrence of node `u`.

### LCA using RMQ

For nodes `u` and `v`:

1. Let `l = first[u]`, `r = first[v]`.
2. Ensure `l <= r`.
3. Find the position of minimum depth in `depthEuler[l...r]`.
4. Return the corresponding node from `euler`.

### Uses

- Lowest Common Ancestor (LCA).
- Distance between two nodes:

  `dist(u,v) = depth[u] + depth[v] - 2 * depth[LCA(u,v)]`

### Data structures

- Sparse table: `O(N log N)` preprocessing, `O(1)` per query.
- Segment tree: `O(N)` build, `O(log N)` per query.

### How to think

To travel from `u` to `v` during DFS, you must backtrack to their LCA before entering the other branch. The shallowest node in that Euler interval is their LCA.

---

## 4. Level Order / BFS Traversal

Visit nodes level by level using a queue.

### Uses

- Shortest paths in unweighted graphs.
- Finding minimum distance from the root.
- Finding nodes at a particular depth.
- Level-wise tree processing.

### How to think

When edges have equal cost, BFS explores nodes in increasing distance from the source.

---

## 5. Postorder DFS

Process children first, then process the current node.

### Uses

- Subtree size and subtree DP.
- Computing height.
- Tree DP where the answer for a node depends on its children.
- Bottom-up aggregation.

### How to think

If a node's answer depends on its children's answers, calculate the children first.

---

## 6. Preorder + Postorder: Rerooting DP

Use two DFS passes:

1. Postorder: compute subtree information.
2. Preorder: propagate information from parent to children.

Example: Sum of distances from every node to all other nodes.

If `ans[u]` is known and `v` is a child of `u`:

`ans[v] = ans[u] + N - 2 * size[v]`

### Uses

- Sum of distances from every node.
- Best answer for every possible root.
- Tree DP involving both subtree and outside-subtree information.

### How to think

First calculate what is inside each subtree, then use the parent's answer to account for everything outside it.

---

## 7. Heavy-Light Decomposition (HLD)

Not a traversal type by itself, but a tree decomposition built using subtree sizes and DFS.

It splits tree paths into a logarithmic number of heavy-chain segments.

### Uses

- Path sum/min/max queries.
- Path updates.
- Combining segment trees with tree paths.
- More advanced tree-query problems.

### Complexity

Usually `O(log^2 N)` per path query with a segment tree.

### How to think

Flattening makes subtrees contiguous, but a path between arbitrary nodes is not generally contiguous. HLD breaks that path into a few contiguous ranges.

---

# Quick Selection Guide

| Problem asks for...                      | Technique                                 |
| ---------------------------------------- | ----------------------------------------- |
| Subtree sum or update                    | Preorder flattening                       |
| Is `u` an ancestor of `v`?               | Entry/exit timestamps                     |
| LCA with many queries                    | Full Euler tour + RMQ, or binary lifting  |
| K-th ancestor                            | Binary lifting                            |
| Shortest distance in an unweighted graph | BFS                                       |
| Subtree DP                               | Postorder DFS                             |
| Answer for every possible root           | Rerooting DP                              |
| Path queries and updates                 | Heavy-Light Decomposition                 |
| Distance between two tree nodes          | LCA + depths                              |
| Subtree size                             | Postorder DFS or preorder interval length |

# Final Mental Model

- **Preorder:** Which nodes belong to this subtree? Flatten the subtree into an array.
- **Entry/exit:** Is one node an ancestor of another?
- **Full Euler tour:** Which common ancestor connects two nodes? Use minimum depth for LCA.
- **BFS:** How far away is a node in an unweighted graph?
- **Postorder:** How do children contribute to their parent?
- **Rerooting:** How can I reuse one root's answer to calculate answers for other roots?
- **HLD:** How can I turn a tree path into a small number of array ranges?

Always identify what the query asks for before choosing a traversal.
