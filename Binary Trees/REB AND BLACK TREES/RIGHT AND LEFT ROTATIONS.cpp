RIGHT ROTATION OF THE TREE ABOVE
      x 
     / \
    a   y
       / \
      b   c
 - x is the new root
 - y > x, y is the new right child of x.
 - x <= b < y
 - a is still left child of x
 - c is still right child of y

LEFT ROTATION OF TREE ABOVE WILL GIVE US THE ORIGINAL TREE

**Example of Left Rotate:**                |x|
leftRotate(x)                              / \
y=x->rightChild                          |a| |y|
x->rightChild=y->leftChild                   / \
if(y->leftChild!=nullNode)                  |b||c|
  y->leftChild->parent=x
y->parent=x->parent
if(x->parent==nullNode)
  root=y
else
  if(x==x->parent->leftChild) //checking to see if x was the left child of the parent
    x->parent->leftChild=y //parent has new left child
  else
    x->parent->rightChild=y
  y->leftChild=x
  x->parent=y
Don't need to update pointers.
for x->leftchild or y->rightChild, They don't change.

      |y|
      / \
    |x| |c|
    / \
  |a| |b|



**Example of Right Rotate:**              |y|     
  rightRotate(y)                          / \
  x=y->leftChild                        |x| |c|
  y->leftChild=x->rightChild            / \
  if(x->rightChild!= nullNode)        |a| |b|
    x->right->parent=y
  x->parent=y->parent
  if(y->parent==nullNode)
    root=x
  else(y==y->parent->leftChild)
    y->parent->leftChild=x
  else
    y->parent->rightChild=x
  x->right=y
  y->parent=x

      |x|
      / \
    |a| |y|
        / \
      |b| |c|