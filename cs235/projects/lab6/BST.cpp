

#include "BST.h"


BST::BST(){
    root = NULL;
}
BST::~BST(){}
NodeInterface * BST::getRootNode(){
    return root;
}
bool BST::rec_add(Node * &in_root, int &in_data){
    if(in_root == NULL){
        in_root = new Node(in_data);
        return true;
    } else if(in_root->getData() == in_data){
        return false;
    } else if(in_data < in_root->getData()){
        return rec_add(in_root->left, in_data);
    } else if(in_data > in_root->getData()){
        return rec_add(in_root->right, in_data);
    }
    return false;
}

bool BST::add(int data){
    return rec_add(root, data);
}


bool BST::rec_remove(Node * &in_root, int &in_data){

    if(in_root == NULL){
        return false;
    } else if(in_root->getData() == in_data){
        //if a match is found
        Node * tmp_root = in_root;
        if(in_root->left == NULL){
            in_root = in_root->right;
        } else if(in_root->right == NULL){
            in_root = in_root->left;
        } else {
            rec_replace_parent(tmp_root, in_root->left);          
            delete tmp_root;
            return true;
        }
        return true;
    } else if(in_data < in_root->getData()){
        return rec_remove(in_root->left, in_data);
    } else if(in_data > in_root->getData()){
        return rec_remove(in_root->right, in_data);
    }
    return false;
}

void BST::rec_replace_parent(Node * &old_root, Node * &local_root){
    if(local_root->right != NULL){
        rec_replace_parent(old_root, local_root->right);
    } else {
        old_root->data = local_root->data;
        old_root = local_root;
        local_root = local_root->left;
    }
}

bool BST::remove(int data){
    return rec_remove(root, data);
}
void BST::clear(){}
