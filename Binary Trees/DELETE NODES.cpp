DELETING NODES FROM A BINARY SEARCH TREE

     15
     /\
    6  24   Delete 6, Delete 15
   /\
  4 8

Need to remove the node, update the parent/child pointers. The node might need to be replaced by another node in the tree. Preserve BST properties.

3 Cases to Consider
-------------------
1. Node has no children. 
 15
 /\
6 20  Delete (6)

The treee becomes:
 15
  \
  20

Delete(value)
{
  Node *n=search(value) //n is node we want to delete after have searched for it.
  if(n!=root)
  {
    if(n->leftChild==NULL && n->rightChild==NULL) //means the node has no children
    {
      if(n==n->parent->leftChild) //way of saying is n equal to the left child of its parent?
      {
        n->parent->leftChild=NULL
      }
      else
      {
        n->parent->rightChild=NULL;
      }
      delete n;
    }
  }
}

2. Node has one child. (Slightly complex)
 15
 /\
6 20  (Delete 20) 20 is its parent right child, and the 20 has one child that is the left child. So 20 is n. and x is 21.
   /
  21
  ** We need to assign a new parent to 21. And a new right child to the 15 **
  *Replacement child in 2 child code.
   - Max value in left subtree is uncommon. Delete 15 and Replace with 13. This is UNCOMMON.
   - MOST TIMES the min value is in the right subtree.
   - 2 Cases.
    * Replacement node is deleted node's right child'. 15
                                                       /\
                                                      6 21
                                                         \
                                                         24
                                              (Delete 15 replace with 21) 21
                                                                          /\
                                                                         6 24
    *Replacement is NOT the right child. 15
                                         /\
                                        6 21
                                           /\
                                          20 24
                                             /\
                                            23 26
    If we replace 15 with 21, 20 is out of place. So We need to replace node with min value in its right subtree. (Delete 15) 20
                                                                                                                              /\
                                                                                                                             6 21
                                                                                                                                \
                                                                                                                                24
                                                                                                                                /\
                                                                                                                              23 26
Example: 15
         /\
        6 30
          /\
         28 32
         /
        27
Delete 15. What replaces it? the 27.

First we ned to find the minimum in the subtree.
Node *min = treeMinimum(n->rightChild) //input to tree minimum is right child of node to delete.
treeMinimum(n) //n is a node pointer.
Node *x=n;
while(x->leftChild !=NULL)
  x=x->leftChild;
return x;

If you wanna delete 15
n=search(15) //some search routine which returns a pointer to that.
treeMinimum(n->rightChild)      15 n
                                 \
                                 21 n->right child
                                 /\
Returns pointer to 18          19 24
                                /\
                              18 20

If min is right child of node to delete...
   (Delete 15)                15
                              /\
                            14 21
                                \
                                26
min=treeMinimum(15->rightChild); //assuming that there are numbers above 15 and 15 isn't necessarily the root.
if(min==n->rightChild)
  n->parent->leftChild=min; //who the child is for the parent
  min->parent=n->parent //who the parent is for the child
  min->leftChild=n->leftChild
  min->leftChild->parent=min;

How does this code change is n is a right child?
if(n==n->parent->leftChild)
  n->parent->leftChild=min;
else
  n->parent->rightChild=min;
else //condition where min is not right cild.
-----------------------------------------------------------------------
 //nodes involved - min right child, and min parent gets new left child.            15
 // n left child, right child, and parent all have to be updated.                   /\
                                                                                    6 18
                   16 is min                                                          /\
                                                                                    17 19
                                                                                    /
                                                                                   16
                                                                                   \
                                                                                   16.5
min->parent->leftChild=min->rightChild (this is the 16.5)
17->leftChild=16.5
min->rightChild->parent=min->parent
16.5->parent=17
min->parent=n->parent
min->parent=n->parent What this does -> (16->parent=15->parent)
n->parent->leftChil=min (moving the 16 into place)
min->leftChild=n->leftChild What this does -> (16->leftchild=15->leftChild)   16
                                                                              /\
                                                                             6  18
                                                                                /\
                                                                              17 19
                                                                              /
                                                                              16.5
min->rightChild=n->rightChild What this does -> (16 ->rightChild = 15->rightChild)
n->rightChild->parent=min
n->leftChild->parent=min
delete n
----------------------------------------------------------------------

else //where left is not equal null or right is not equal null, but not both. This is after #3. 
{
  Node *x=n->leftChild
  n->parent->rightChild=x; //sets pointer from 15 to 21. 
  x->parent=n->parent; //sets pointer from 21 to 15. Canceling 20 out of the equation.
}

3. Node has 2 children. (Most complex)
 15
 /\
6 20  (Delete 20)
   /\
  16 21
  - Max value in left subtree or min value in right truee will preserve BST properties.
  - Convention is to use min in right subtree.

else if(n->leftChild!=NULL && n->rightChild!=NULL)