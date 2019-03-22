SEARCHING A BST

*2 Versions - Recursive and iterative version.
  1. Recursive Search Algorithm
  Search(node, searchKey) //search key is the value we are looking for.
  { 
    if(node==NULL)
      return node;
    else
    {
      if(node ->key==searchKey)
        return node;
      else if(node->key > searchKey) //saying the parent is what greater than what we're looking for, so it goes to left child.
        return Search(node->leftChild,searchKey)
      else
        return Search(node->rightChild,searchKey)
    }
    //what does search return? Returns pointer to node that we're finding the key value for if its found, else it will return NULL.
    //BASE CASE - Node equals NULL or node found. Anything that stops recursion from happening.
  }

  2. Iterative Search Algorithm
  Search(searchKey)
  {
    Node *n = root //create a pointer to the root.
    while(n!=NULL)
    {
      if(n->key > searchKey)
        n=n->leftChild
      else if(n->key < searchKey)
        //do do less than equal, because if it's equal to... (look at else statement)
        n=n->rightChild;
      else
        return n;
    }
    return NULL;
    //returns ponter to node where search key is found, and returns NULL if search key is NOT found.
  }


EXAMPLE PROBLEM
You have been given a recursive function to sum the values of all keys in a BST:

int findSum(TreeNode * root, int depth)
{
    if(root != NULL)
    {
       int leftSum = findSum(root->left, depth + 1);
       int rightSum = findSum(root->right, depth + 1);
       cout << root->key;
       if (depth != 0)
       {
          cout << " ";
       }
       return leftSum + rightSum + root->key;
    }
    else
       return 0;
}



Consider following binary search tree:
                                15
                              /    \
                            12      17
                           /          
                          4            
                        /   \   
                       2     5
                              \
                               8


The following code is called:

findSum(root, 0);

Root is a pointer to the TreeNode whose key is 15. What is the output from cout? Note that there is a single space between values that are printed to the terminal. 
Note, there are no intended errors in the code.

//When it's first called, we are starting at the 15. FindSum(15,0)
//We are gonna call the left child of 15. FindSum(12,1)
//We are gonna call it again on the left child FindSum(4,2)
//Call left child again FindSum(2,3)
//go down to else, we return to call at 2
//Next line that executes is cout of root->key which is the 2, so we print the 2. First thing printed.
//then that call pops off the stack. FindSum(2,3) pops off.
//Evaluate right children of 4. Right child of 4 goes to 5, left child of 5 is NULL, that pops off, we call the right child of the 5, which is the 8 
//8 children are null so it prints 8
//then prints 5, then 4, then 12, then 17, then 15.


