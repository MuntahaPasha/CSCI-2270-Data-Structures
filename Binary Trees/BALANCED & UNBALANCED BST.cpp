Balanced vs. Unbalanced BST
          5
          /\
         3  8
        /\  /\
       2 4 7  9
       BALANCED

           5
          /\
         2  4
             \
              8
               \
               10
         UNBALANCED

Example: Tree of 1,000,000 nodes, sorted. 
n=1,000,000
My BST is very unbalances, its LL of 1,000,000
Search: O(n)
Insert: O(n)

    5    2^0 = 1
    /\
    3 10   2^1 = 2
   /\ /\
  2 4 9 11  2^2 = 4

At any level BST I can have 2-1 nodes. i=level in tree.
(2^3)-1 = 7
log_2(1,000,000) ~= 19.9    **O(log_n)**
O(log_n)<O(n). Search, find, and delete operations are much faster if tree is balances.

TREE BALANCING ALGORITHMS
- AVL tree-simple, but not used in practice.
- B-Trees (Used in data base storage algorithms)
- Red/Black Trees - (Not simple, but used in commerical applications)
(Assign properties to tree nodes, perform rotations, other actions to preserve those)