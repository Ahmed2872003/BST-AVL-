#include<iostream>

using namespace std;

template<class t>
class BST
{
    private:
        /*----------Begin creating nodes----------*/
        struct node
        {
            t data;
            node* right;
            node* left;
            node() : right(NULL) , left(NULL){}
            node(t& v) : node(){data = v;}
        };
        node* insert(node* , node*);
        node* remove(node* , t);
        void preorderShow(node*);
        void inorderShow(node*);
        void postorderShow(node*);
        t getMin(node*);
        node* getMinNode(node*);
        t getMax(node*);
        node* getMaxNode(node*);
        int BF(node*);
        node* balance(node*);
        node* RR_rotat(node*);
        node* LL_rotat(node*);
        node* LR_rotat(node*);
        node* RL_rotat(node*);
        /*----------End of creating nodes----------*/
    public:
        node* root;
        BST() : root(NULL){}
        bool empty();
        void insert(t);
        t getMax();
        t getMin();
        void remove(t);
        void inorderShow();
        void preorderShow();
        void postorderShow();
        int height(node*);
        ~BST(){}

};


template<class t>
bool BST<t>::empty()
{return !root;}
/*----------Begin inserting nodes----------*/
template<class t>
void BST<t>::insert(t value)
{
    node* newnode = new node(value);
    if(empty())
        root = newnode;
    else
        root = insert(root , newnode);
}
template<class t>
typename BST<t>::node* BST<t>::insert(node* r , node* newnode)
{
    if(!r)
        return newnode;
    if(newnode->data <= r->data)
        r->left = insert(r->left , newnode);
    else     
        r->right = insert(r->right , newnode);
    r = balance(r);
    return r;
}
/*----------End of inserting nodes----------*/
/*----------start balancing----------*/
template<class t>
typename BST<t>::node* BST<t>::balance(node* parent)
{
    if(BF(parent) < -1)
    {
        if(BF(parent->right) < 0)
            parent = RR_rotat(parent);
        else
            parent = RL_rotat(parent);
    }
    else if(BF(parent) > 1)
    {
        if(BF(parent->left) > 0)
            parent = LL_rotat(parent);
        else
            parent = LR_rotat(parent);
    }
    return parent;
}
/*----------End of balancing----------*/
/*----------Start RR_rotation----------*/
template<class t>
typename BST<t>::node* BST<t>::RR_rotat(node* parent)
{
node* bring = parent->right;
parent->right = bring->left;
bring->left = parent;
return bring;
}
/*----------End RR_rotation----------*/
/*----------Start LL_rotation----------*/
template<class t>
typename BST<t>::node* BST<t>::LL_rotat(node* parent)
{
node* bring = parent->left;
parent->left = bring->right;
bring->right = parent;
return bring;
}
/*----------End LL_rotation----------*/
/*----------Start RL_rotation----------*/
template<class t>
typename BST<t>::node* BST<t>::RL_rotat(node* parent)
{
parent->right = LL_rotat(parent->right);
parent = RR_rotat(parent);
return parent;
}
/*----------End RL_rotation----------*/
/*----------Start LR_rotation----------*/
template<class t>
typename BST<t>::node* BST<t>::LR_rotat(node* parent)
{
parent->left = RR_rotat(parent->left);
parent = LL_rotat(parent);
return parent;
}
/*----------End LR_rotation----------*/
/*----------Begin of geting max node----------*/
template<class t>
t BST<t>::getMax()
{
    if(empty())
        return -1;
    else 
    return getMax(root);

}
template<class t>
t BST<t>::getMax(node* r)
{
    if(!r->right)
        return r->data;
    else
        return getMax(r->right);

}
template<class t>
typename BST<t>::node* BST<t>::getMaxNode(node* r)
{
    if(!r->right)
        return r;
    else
        return getMaxNode(r->right);
}
/*----------End of geting max node----------*/
/*----------Begin of geting min node----------*/
template<class t>
t BST<t>::getMin()
{
    if(empty())
        return -1;
    else
        return getMin(root);
}
template<class t>
t BST<t>::getMin(node* r)
{
    if(!r->left)
        return r->data;
    else
        return getMin(r->left);

}
template<class t>
typename BST<t>::node* BST<t>::getMinNode(node* r)
{
    if(!r->left)
        return r;
    else
        return getMin(r->left);

}
/*----------End of geting min node----------*/
/*----------begin of deleting node----------*/
template<class t>
void BST<t>::remove(t target)
{
    if(empty())
        {cout <<"Empty tree\n";return;}
    else
    root = remove(root , target);
}
template<class t>
typename BST<t>::node* BST<t>::remove(node* r, t target)
{
    if(!r)
        {cout <<"NO node with that value";return root;}
    if(target > r->data)
        {r->right = remove(r->right , target);r = balance(r);}
    else if(target < r->data)
        {r->left = remove(r->left , target);r = balance(r);}
    else
    {
        t temp;
        node* bBF  = r;
        if(!r->right && !r->left)
            return NULL;
        else if(!r->right || !r->left)
        {
            if(!r->left)
            {
                temp = r->right->data; 
                r = remove(r , temp);
                bBF->data = temp;
            }
            else if(!r->right)
            {
                temp = r->left->data;
                r = remove(r , temp);
                bBF->data = temp;
            }
        }
        else
        {   
            temp = getMaxNode(r->left)->data;
            r = remove(r , temp);
            bBF->data = temp;
        }
    }
    
    return r;
}

/*----------End of deleting node----------*/
/*----------Displaying----------*/
/*----------begin of showing elements(inorder)----------*/
template<class t>
void BST<t>::inorderShow()
{
    if(empty())
        {cout << "No elements in the tree\n";return;}
    else
        inorderShow(root);
}
template<class t>
void BST<t>::inorderShow(node* r)
{
    if(!r)
        return;
    inorderShow(r->left);
    cout << r->data << "   ";
    inorderShow(r->right);
}
/*----------end of showing elements(inorder)----------*/
/*----------begin of showing elements(preorder)----------*/
template<class t>
void BST<t>::preorderShow()
{
    if(empty())
        {cout << "No elements in the tree\n";return;}
    else
        preorderShow(root);
}
template<class t>
void BST<t>::preorderShow(node* r)
{
    if(!r)
        return;
    cout << r->data << "   ";
    preorderShow(r->left);
    preorderShow(r->right);

}
/*----------end of showing elements(preorder)----------*/
/*----------begin of showing elements(postorder)----------*/
template<class t>
void BST<t>::postorderShow()
{
    if(empty())
        {cout << "No elements in the tree\n";return;}
    else
        postorderShow(root);
}
/*----------End displaying----------*/
template<class t>
void BST<t>::postorderShow(node* r)
{
    if(!r)
        return;
    postorderShow(r->left);
    postorderShow(r->right);
    cout << r->data << "   ";
}
/*----------End of showing elements(postorder)----------*/
/*----------Start tree height----------*/
template<class t>
int BST<t>::height(node* r)
{
    if(!r)
        return -1;
    int hlt = height(r->left) + 1; 
    int hrt = height(r->right) + 1;
    return hlt >= hrt ? hlt : hrt;
}
/*----------End tree height----------*/
/*----------start calculating BF----------*/
template<class t>
int BST<t>::BF(node* r)
{
return height(r->left) - height(r->right);
}
/*----------start calculating BF----------*/
int main()
{
    BST<int>btree;
    btree.insert(5);
    btree.insert(2);
    btree.insert(1);
    btree.insert(3);
    btree.insert(4);
    btree.insert(8);
    btree.insert(7);
    btree.insert(6);
    btree.insert(20); 
    btree.insert(9);
    btree.insert(25);  
    btree.insert(30);  
    btree.remove(1);
    btree.inorderShow();
    //2   3   4   5   6   7   8   9   20   25   30
    return 0;
}
