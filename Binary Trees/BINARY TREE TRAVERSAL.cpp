BINARY TREE TRAVERSAL
 - Differebt ordering for processing tree info.
 - Traverse tree and print values in order
 - We know left < parent <= right
 - To print in order we need to print left, parent, right.

inOrder(node *n) ((lowest -> highest))   |n|
{                                        / \
	if(n->left!=NULL)                  |c| |s|    **What gets printed - a, c, d, g, h, n, s, t, x.**
		inOrder(n->left)               / \   \
	cout<<n->key<<endl;              |a| |g| |t|
	if(n->right!=NULL)                   / \   \
		inOrder(n->right)              |d| |h| |x|
}

preOrder(node *n) (process parent before child) |n|
{                                        		/ \
	cout<<n->key<<endl;                	 	  |c| |s|    **What gets printed - n, c, a, g, d, h, s, t, x.**
	if(n->left!=NULL);             	     	  / \   \
		preOrder(n->left);			   		|a| |g| |t|
	if(n->right!=NULL);                   		/ \   \
		preOrder(n->right);          	  	  |d| |h| |x|
}

postOrder(node *n) (process child then parent) 	|n|
{                                        	 	/ \
	if(n->left!=NULL);                	  	  |c| |s|    **What gets printed - a, d, h, g, c, x, t, s, n.**
		preOrder(n->left);             	      / \   \
	if(n->right !=NULL); 		  		    |a| |g| |t|
		preOrder(n->right);                  	/ \   \
	cout<<n->key<<endl;            	 	      |d| |h| |x|
}

