**Inserting a node into a RB Tree*
- Same as inserting into a BST with a few additional steps.
 1) Replace NULL with NULL node.
 2) Set the color of the new node to Red.
 3) Resolve violations of RB Properties using recoloring and rotation.

**Example of Violations**
 - Add a new node to empty tree.
   rule :  New node is red.                  |5|
  VIOLATION : root of tree MUST be black.
  SOLUTION : Recolor to be black.
 
 - Add a red 4 to the tree.             |5B|
   rule : all new nodes are red.         / \
  VIOLATION : NONE                     |4R|

 - Add a red 3 to the tree.
   rule : both children must be black       |5B|
  VIOLATION : Red node has a Red child.      /\
  SOLUTION : Recolor the 3 to black.      |4R|
  (But this crreates violation of # of     /
  black nodes from root to leaf) 
  So you can rotate on 4 then recolor.

**Algorithm to insert node into RB Tree**
- 6 possible configurations that RB can take.
 - 3 configurations symmetric to other 3 depending on whether parent of new node is right or left child.
 - 3 configurations where parent is left Child.

1) Identify the "Uncle" node in tree.
               |~| 
               / \              - x is new node
(x-Parent)-->|~| |y| "Uncle"    - y is uncle
             /
            |x|                            

CASE ONE: "Uncle" is red
           |18|
           /  \                 - x is new node
        |15|  |21| "Uncle"      - x is red because it's new
        /  \     \              - VIOLATION: Red parent has red child 
 x -->|11| |16|  |29|

CASE TWO: New Node is right child and "uncle" is black
           |18|
           /  \                 - x is new node
        |15|  |21| "Uncle"      - 21 is uncle
        /  \                     
      |11| |16|<-- x

CASE THREE: New node is left child and "uncle" is black
           |18|
           /  \                 - x is new node
        |15|  |21| "Uncle"      - 21 is uncle
        /  \                     
 x -->|11| |16|

Algorithm for RB insert:
redBlackInsert(value)
{
  Node *x=insert(value) //insert puts node into BST but could create violation
  while(x!=root && x->parent->color!='red')
  {
    if(x->parent==x->parent->parent->left)
      Node *uncle = x->parent->parent->right
      if(uncle->color=='red') //CASE ONE
      {
        x->parent->color='black'
        uncle->color='black'
        x->parent->parent->color='red'
        x=x->parent->parent
      }
      else 
      {
        if(x==x->parent->right)
        { //CASE TWO
          x=x->parent
          leftRotate(x)
        }
        x->parent->color='black' //CASE THREE
        x->parent->parent->color='red'
        rightRotate(x->parent->parent) //right rotate on grandparent
      }
      else
      {
        //x's parent is a right child
        //exchange left and right
      }
  }
  root->color='black'
}

ex: add 4 to tree          |11|
                           / \
                          |2||14|
                          / \  \
                        |1| |7| |15|
                            / \
                x-parent->|5| |8| <--Uncle
                           /
                          |4| <-- x
After insert line executes
x is the 4 node.
So x's parent's, parent's right is 8, which is the UNCLE
5 changes color
uncle becomes black
7 becomes red

Deleting a Node from a RB Tree
- Point of 
 - RB Trees to maintain height balance of subtrees.
IMPORTANT: HAVE AN UNDERSTANDING OF TREE MANIPULTIONS.

BST delete 
 - No children - Delete node
 - One Child - replace node w/ child
 - Two Children - replace with minimum in right subtree.
Violation
 - Violation occurs if the node's replacement is black. (Can change # of black nodes on a path)
ex: 15
    / \
   10 20  Delete (10) -> Replaced by (12) -> replaced by (14)   15
  / \                                                           /
 5  12                                                         12
    / \                                                        /
      14                                                      5
       \                                               Violation: Chain of black nodes