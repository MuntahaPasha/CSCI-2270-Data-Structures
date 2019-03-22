RB Delete(value)
{
  node=search(value)
  nodeColor=node.color //node color is color of node to delete
  if(node!=root)
  {
    if(!leftChild && !rightChild) //node has no children. Can be written also as leftChild==NULL && rightChild==NULL
    {
      x=node.parent->left //assuming node is left child
    }
    else if(leftChild!=NULL && rightChild!=NULL)
    {
      min=treeMin(node->rightChild)
      nodeColor=min.color //node color is color of replacement
      x=min.rightChild -|  (x could be null node)
      x.parent=min     -|
      //code to replace node with min from BST delete
      min.color=node.color //change color of replacement
    }
    else //one child
      x=node.left         -|
      node.parent.left=x  -|  (x is nodes replacement)
      x.parent=node.parent-|
  }
  else
    //handle root
  if(nodeColor==black)
  {
    rbBalance(x); //x can be null node, min's right child, or node's replacement.
  }
}

RBBalance(x)
{
  while(x!=root && x.color==black)
  {
    if(x==x.parent.leftChild)
    {
      s=x.parent.rightChild
      if(s.color==red)
      {
        s.color=black
        x.parent.color=red
        leftRotate(x.parent)
        s=x.parent.rightChild
      }
      else if(s.leftChild.color==black && s.rightchild.color==black) // s is black, children are black
      {
        s.color=red
        x=x.parent
      }
      else if(s.leftChild.color==red && s.rightChild==black)
      {
        s.leftchild.color=black
        s.color=red
        rightRotate(s)
        s=x.parent.rightChild
      }
      else
      {
        s.color=x.parent.color
        x.parent.color=black
        s.rightchild.color=black
        leftRotate(x.parent)
        x=root
      }
      else
      {
        //x is a right child
        //exchange left and right
      }
    }
  }
  x.color=black;
}