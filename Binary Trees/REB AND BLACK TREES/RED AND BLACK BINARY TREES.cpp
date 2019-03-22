RED-BLACK TREES
(Still a BST, just adding stuff to it)
- Each node in BST is assigned a color (red or black).

**Properties of RB tree**
1) A node is either red or black.
2) Root node is black.
3) Every leaf node is black. (Leaf nodes at bottom of tree)
4) If a node is red, both children must be back.
5) For each path through the tree, all paths to leaf nodes contain same number of black nodes.

**Other facts**
1)Operations on balanced tree are much more efficient than on unbalanced.
2)Red-Black Trees - R,B Nodes.
 - Same number of B nodes on every path from a node to a leaf. 
 - Use recoloring rotation to reconstruct the tree as nodes added and deleted.
3) Left, Right Rotations are inverses of eachothers.

**Leaf Nodes**
- In BST, leaf node are left, right, and NULL children.
- In RB tree, leaf nodes are empty nodes.
- Instead of pointing to NULL, we point to empty NULL node (Empty node).

     |R|       R = Red
     / \        B= Black
   |B| |B|
   /
  |R|
What if you delete the left B-node?
Well you get...
   |R|
  /  \
|R|  |B|
We have a tree that violates the conditions that every red must have two black children, because it only has one black child.

**How to fix Violations*
 - Recolor it. (Change the node color. Red->black, or Black->red)
 - Rotation. (Change the height of the sub-tree)
   1
   \
    2
     \
      3
1 is root, 2 is right child.
Rotate on 2, so that 2 is new root.
(Height of tree has changed)
  2
 / \
1   3

**Left and Right Rotations**
 - Inverses of eachother.
       y
      / \
     x   c
    / \
   a   b
 - x, y are nodes
 - a, b, c are nodes or roots to subtrees.
 - a < x
 - x <= b < y
 - c >= y
 -Whatever we do to the tree, we need to maintain those relationships.                          
