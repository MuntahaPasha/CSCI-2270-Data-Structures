// From this data, build the BST ordered by the first letter in the movie title. For each of the nodes in the BST, there should be a sorted singly linked list // of the actual movie data. Note: the nodes should be added to the BST and Linked Lists in the order they are read in. The name of the file that contains the // movie data is Assignment6Movies.txt
#include <iostream>
#include "Assignment6.hpp"
#include <sstream>

// When the user selects this option, your program should delete the nodes in the tree and exit the program.
// When the user selects quit, the destructor for the MovieTree class should be called and in the destructor, all of the nodes in the tree and singly linked lists should be deleted.
// You need to use a postorder tree traversal for the delete or you will get segmentation fault errors.

MovieTree::MovieTree()
{
	root = NULL;
}

MovieTree::~MovieTree()
{
	DeleteAll(root);
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
    char titleLetter = title[0];
    MovieNodeBST* vader = new MovieNodeBST;
    MovieNodeLL* LL = new MovieNodeLL(ranking, title, releaseYear, quantity);
    if(root!= NULL){
        vader = root;
        while(vader != NULL){
            if(vader->letter == titleLetter){
                MovieNodeLL* foundLL = vader->head;
                while(foundLL != NULL){
                    if(title < vader->head->title){
                        MovieNodeLL* temp = vader->head;
                        LL->next = temp;
                        vader->head = LL;
                        return; 
                    }
                    else if((foundLL->next == NULL) && (title > foundLL->title)){
                        foundLL->next = LL;
                        LL->next = NULL;
                        return;
                    }
                    else if((foundLL->title < title) && (title < foundLL->next->title)){
                        LL->next = foundLL->next;
                        foundLL->next = LL;
                        return;
                    }
                    foundLL = foundLL->next;
                }
            }
            else if((vader->leftChild == NULL) && (titleLetter < vader->letter)){
                MovieNodeBST* bst = new MovieNodeBST(titleLetter);
                vader->leftChild = bst;
                bst->parent = vader;
                bst->head = LL;
                return;
            }
            else if((vader->rightChild == NULL) && (titleLetter > vader->letter)){
                MovieNodeBST* bst = new MovieNodeBST(titleLetter);
                vader->rightChild = bst;
                bst->parent = vader;
                bst->head = LL;
                return;
            }
            else if(titleLetter < vader->letter){
                vader = vader->leftChild;
            }
            else{
                vader = vader->rightChild;
            }
            
        }
    }
    else{
        MovieNodeBST* bst = new MovieNodeBST(titleLetter);
        bst->head = LL;
        root = bst;
     }
}

// Heading: Find a movie.
// When the user selects this option from the menu, they should be prompted for the name of the movie. Your program should then search the tree and singly linked lists and display all information for that movie. If the movie is not found, your program should display, “Movie not found.”

void MovieTree::findMovie(string title)
{
	MovieNodeBST* darthVader = searchBST(root, title); // Find the node in BST (Darth Vader) that contains 'key' to the given title
	//MovieNodeLL* luke = searchLL(darthVader->head, title); // Find the movie title in the associated linked list (Luke) of that BST node (Darth Vader)
    if(darthVader==NULL)
    {
        cout << "Movie not found." << endl;
		return;
    }
    MovieNodeLL* luke = searchLL(darthVader->head, title); // Find the movie title in the associated linked list (Luke) of that BST node (Darth Vader)
    
	if(luke == NULL)
	{
		cout << "Movie not found." << endl;
		return;
	}
	
	cout << "Movie Info:" << endl;
	cout << "===========" << endl;
	cout << "Ranking:" << luke->ranking << endl;
	cout << "Title:" << luke->title << endl;
	cout << "Year:" << luke->year << endl;
	cout << "Quantity:" << luke->quantity << endl;
}
// Heading : Rent a movie.
// When the user selects this option from the menu, they should be prompted for the name of the movie. If the movie is found in your data structure, your program should update the Quantity in stock property of the movie and display the new information about the movie.
// If the movie is not found, your program should display, “Movie not found.”
// When the quantity reaches 0, the movie should be deleted from the singly linked list. If that was the only node in the singly linked list, the node should also be deleted from the BST for that letter.

void MovieTree::rentMovie(string title) 
{
    MovieNodeBST *vader=searchBST(root,title);
    if(vader==NULL)
    {
        cout<<"Movie not found."<<endl;
    }
    else
    {
        MovieNodeLL *temp=vader->head;
        bool found=false;
        while(temp!=NULL)
        {
            if(temp->title==title)
            {
                found=true;
                break;
            }
            temp=temp->next;
        } 
        if(!found)
        {
            cout<<"Movie not found."<<endl;
        }
        else
        {
            temp->quantity--;
            cout<<"Movie has been rented."<<endl;
            cout<<"Movie info:" <<endl;
            cout<<"===========" <<endl;
            cout<<"Ranking:" <<temp->ranking<<endl;
            cout<<"Title:" <<temp->title<<endl;
            cout<<"Year:"<<temp->year<<endl;
            cout<<"Quantity:"<<temp->quantity<<endl;
            
            if(temp->quantity==0)
            {
                temp=NULL;
                delete temp;
            }
        }
    }
}

void inOrder(MovieNodeBST *n)
{
	if(n->left!=NULL)
		inOrder(n->left);
	if(n->right!=NULL)
		inOrder(n->right);
}

// Heading: Print the entire inventory.
// When the user selects this option from the menu, your program should display all movie titles and the quantity available in sorted order by title. See the lecture notes and recitation exercises on in-order tree traversal, and linked list traversals, for more information.
void MovieTree::printMovieInventory()
{
	MovieNodeBST* dv=root;
	if(dv->left!=NULL)
	{
		inOrder(dv->left);
	}
	
	MovieNodeLL* luke = dv->head;
	
	//For all movies in this node
	while(luke != NULL)
	{
		cout<<"Movie: "<<luke->title<<" "<<luke->quantity<<endl;
		luke = luke->next;
	}
	
	if(dv->right!=NULL)
	{
		inOrder(dv->right);
	}
}

// Heading: Delete a movie.
// When the user selects this option, they should be prompted for the title of the movie to delete. (Done in main)
// Your code should then search the tree for the first letter of that movie, and then search the singly linked list for the title. 
// If the title is found, delete it from the singly linked list. 
// If it was the only title for that letter in the BST, you also need to delete the node in the BST and re-assign the parent and child pointers to bypass the deleted node, and free the memory assigned to the node.
// If the movie is not found in the search process, print “Movie not found” and do not attempt to delete. A movie node should also be deleted when its quantity goes to 0.

// Heading: Count movies in the tree.
// When the user selects this option, your program should traverse the tree and singly linked lists and count the total movie nodes in the tree and print the count
void MovieTree::countMovieNodes(MovieNodeBST *node, int *c)
{
	if(node==NULL)
    {
        *c=0;
        return;
    }
	if(node->leftChild!=NULL)
	{
	    MovieNodeLL* luke = node->head;
	    while(luke != NULL)
	   {
		*c += 1;
		luke = luke->next;
	    }
		countMovieNodes(node->leftChild, c);
	}
	
    if(node->rightChild!=NULL)
	{
	    MovieNodeLL* luke = node->head;
    	while(luke != NULL)
    	{
    		*c += 1;
    		luke = luke->next;
    	}
		countMovieNodes(node->rightChild, c);
	}
}


// Private Functions

void MovieTree::DeleteAll(MovieNodeBST * node) //use this for the post-order traversal deletion of the tree
{
	if(node->left!=NULL)
		DeleteAll(node->left);
 	if(root->right!=NULL)
 		DeleteAll(node->right);
 	delete node;
}


MovieNodeLL* MovieTree::searchLL(MovieNodeLL* head, std::string title) //use this to return a pointer to a node in a linked list, given a MOVIE TITLE and the head of the linked list
{
	MovieNodeLL *temporary=head;
	bool found=false;
	while(temporary!=NULL)
	{
		if(temporary->title==title)
		{
			found=true;
			break;
		}
		temporary=temporary->next;
	}
	if(!found)
	{
		return NULL
	}
	else
	{
		return temporary;
	}
}


MovieNodeBST MovieTree::searchBST(MovieNodeBST node, string title) //use this recursive function to find a pointer to a node in the BST, given a MOVIE TITLE
{
 char firstLetter = title[0];
 if(node==NULL)
      return node;
    else
    {
      if(node->letter==firstLetter)
        return node;
      else if(node->letter > firstLetter) //saying the parent is what greater than what we're looking for, so it goes to left child.
        return searchBST(node->leftChild,title);
      else
        return searchBST(node->rightChild,title);
 }
}

void replaceNodeInParent(MovieNodeBST* n, MovieNodeBST* newValue)
{
    cout<<"ltr "<<n->letter<<"title "<<n->head->title<<endl;
    if(newValue!=NULL)
    {
        cout<<"nv ltr "<<newValue->letter<<"nv ttl "<<newValue->head->title<<endl;
    }
	if(n->parent)
	{
		if(n == n->parent->leftChild)
		{
			n->parent->leftChild = newValue;
		}
		else
		{
			n->parent->rightChild = newValue;
		}
	}
	if(newValue)
		newValue->parent = n->parent;
}

MovieNodeBST* MovieTree::treeMinimum(MovieNodeBST* node)
{
 MovieNodeBST* cn = node;
 while (cn->leftChild)
 {
  cn = cn->leftChild;
 }
 
 return cn;
}


void MovieTree::deleteMovieNode(std::string title)
{
	MovieNodeBST* n = searchBST(root, title);	
	MovieNodeLL* nLL = searchLL(n->head, title);
    cout<<"title "<<title<<endl;
	if(nLL == NULL && title.length()>1)
	{
		cout << "Movie not found." << endl;
		return;
	}
	//If it was the only title for that letter in the BST, you also need to delete the node in the BST and re-assign the parent and child pointers to bypass the deleted node, and free the memory assigned to the node.
	if(n->head->next == NULL)
	{
	    //cout<<"debug torture"<<endl;
		delete n->head;
		//cout<<"debug torture.5"<<endl;
		// Delete the move in LL and the node in BST
		// delete the key here
		// check if both children are present
		if(n->leftChild && n->rightChild)
		{
		//cout<<"debug torture2"<<endl;
			MovieNodeBST* successor = treeMinimum(n);
			//cout<<"debug 2.5"<<endl;
			string successorKey;
   			successorKey += successor->letter;
   			//cout<<"successor key"<<successorKey<<"letter "<<successor->letter<<endl;
   			//cout<<"debug 2.8"<<endl;
			deleteMovieNode(successorKey);
		//cout<<"debug torturr3"<<endl;
		}
		else if(n->leftChild)
		{
		    //cout<<"debug trture5"<<endl;
			replaceNodeInParent(n, n->leftChild);
		}
		else if(n->rightChild)
		{
		//cout<<"debug torture7"<<endl;
			replaceNodeInParent(n, n->rightChild);
		}
		else
		{
		    //cout<<"deug torture8"<<endl;
		    replaceNodeInParent(n, NULL);
		}
	}
	// If there are more nodes in LL
	else
	{
		if(nLL!=n->head)
		{
		    //cout<<"Debug one"<<endl;
		    MovieNodeLL* ll = n->head;
    		while(ll->next != nLL)
    		{
    		    //cout<<"debug two"<<endl;
    			ll = ll->next;
    		}
    	    ll->next=nLL->next;
    	    //cout<<"debug three"<<endl;
		}
		else
		{
		//cout<<"debug four"<<endl;
		    n->head=nLL->next;
		}
		//cout<<"debug 4.5"<<nLL->title<<endl;
		nLL->title;
		delete nLL;
		cout<<endl;
		//cout<<"debug 5"<<n->head->title<<endl;
	}	
}







