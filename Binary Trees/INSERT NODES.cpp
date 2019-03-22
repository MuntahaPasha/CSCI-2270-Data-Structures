INSERT A NEW NODE

Insert(value)
{
  //value is node info, data. It's not a pointer it's the thing we wanna add.
  Node *parent=NULL;
  Node *temp=root; //root is a private pointer stored in node class.
  Node *n=new Node(value, NULL,NULL,NULL)
                          ^parent^leftchild^rightchild-->(all stored as NULL)
  while(temp!=NULL){
    parent=temp; //setting the parent to the root.
    if(n->key < temp->key){ //it means we want to go to the left child.
      temp=temp->leftChild;
    }
    else{
      temp=temp->rightChild
    }
  }
  if(parent==NULL)
    root=n; //true when tree is empty.
  else if(n->key < parent->key)
  {
    //set to left child
    parent->leftChild=n;
    n->parent=parent;
  }
  else
  {
    //set to right child
    parent->rightChild=n;
    n->parent=parent; //setting the pointer both ways. Both the parent points to child but after this, the child points to the parent.
  }
}

Ex: |10|
     / \
    |5| |15|
    /
  |4|
 - Add a 7 to the tree.
 - So let's walk through algorithm.
 - So temp is 10, and n is node of value of 7.
 - While temp is not null, that's true, so parent equals temp, which means 10 is now root.
 - n key is 7, and temp key is 10. After we run that temp is gonna be 5.
 -Go back to while, pointing at 5, but parent is still pointing to 10. So now we say parent equals temp, so now parent is 5.
 - If n key is less than temp key and n key is 7 and temp key is 5 then that is false, so we go down to else.
 - Temp becomes NULL