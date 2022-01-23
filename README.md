# A general-purpose non-recursive tree traversal algorithm

The function `traverse(p, order, F)` takes three arguments:

- A tree node `p`,
- A traverse argument `order`,
- A function pointer `F`

`traverse` visits each node in `p` and applies `F` to it.
The traversal order is dictated by the 2nd argument `order`
which is either `PREORDER`, `INORDER` or `POSTORDER`.

`traverse` only requires one extra bit per node and runs in O(n)
time and O(1) space, i.e., no stack is required.  Instead,
tree pointers are flipped so that `traverse` can find its way back.
