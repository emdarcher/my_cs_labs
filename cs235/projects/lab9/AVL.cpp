

#include "AVL.h"


AVL::AVL(){
    root = NULL;
}
AVL::~AVL(){
    clear();
}

bool AVL::rec_add(Node * &in_root, int &in_data){
    bool increase = false;
    if(in_root == NULL){
        in_root = new Node(in_data, NULL, NULL);
        increase = true;
        return true;
    } else if(in_root->getData() == in_data){
        increase = false;
        return false;
    } else if(in_data < in_root->getData()){
        bool ret_val =  rec_add(in_root->left, in_data);
        increase = ret_val;
        if(increase){
            if(in_root->getBalance() == 0){
                increase = false;
            }
            if(in_root->getBalance() < -1){
                increase = false;
                //rebalance left
                if(in_root->left->getBalance() > 0){
                    //rotate left subtree left
                    rot_left(in_root->left);
                }
                //rotate parent right
                rot_right(in_root);
            }
        } 
        return ret_val;
    } else if(in_data > in_root->getData()){
        bool ret_val = rec_add(in_root->right, in_data);
        increase = ret_val;
        if(increase){
            if(in_root->getBalance() == 0){
                increase = false;
            }
            if(in_root->getBalance() > 1){
                increase = false;
                //rebalance right
                if(in_root->right->getBalance() < 0){
                    //rotate right subtree right
                    rot_right(in_root->right);
                }
                //rotate parent left
                rot_left(in_root);
            }
        }

        return ret_val;
    }
    return false;
}

void AVL::rot_right(Node*& local_root){
    if(local_root == NULL) return;
    Node * temp = local_root->left;
    local_root->left = temp->right;
    temp->right = local_root;
    local_root = temp;
}
void AVL::rot_left(Node*& local_root){
    if(local_root == NULL) return;
    Node * temp = local_root->right;
    local_root->right = temp->left;
    temp->left = local_root;
    local_root = temp;
}
#if 0
void AVL::rec_balance(Node*& in_root){
    //if left heavy, rotate right
    //if right heavy, rotate left
    
    if(in_root == NULL) return; 

    if(in_root->getHeight() == 1){
        //this is a leaf, can't balance from it
        return;
    }
    int rh = (in_root->right != NULL) ? in_root->right->getHeight() : 0;
    int lh = (in_root->left != NULL) ? in_root->left->getHeight() : 0;
    
    //if(abs(rh - lh) > 1){
   
        //first continue the recursive chain
        //if(rh > lh){
        //    rec_balance(in_root->right);
        //} else if(rh < lh){
        //    rec_balance(in_root->left);
        //}
        if(rh > 0) rec_balance(in_root->right);
        if(lh > 0) rec_balance(in_root->left);


        //if after calling on lower children it is still unbalanced
        //then do correct rotations
        //
        //get new height values
        rh = (in_root->right != NULL) ? in_root->right->getHeight() : 0;
        lh = (in_root->left != NULL) ? in_root->left->getHeight() : 0;
        
        if((abs(rh - lh) > 1) || (in_root->getHeight() == 2)){
            if(rh > lh){
                rot_left(in_root);
            } else if(rh < lh){
                rot_right(in_root);
            }
        } 

    //}     
    
}
#endif
#if 0
void AVL::rec_balance(Node*& in_root){
    if(in_root == NULL) return; 

    if(in_root->getHeight() == 1){
        //this is a leaf, can't balance from it
        return;
    }
    int rh = (in_root->right != NULL) ? in_root->right->getHeight() : 0;
    int lh = (in_root->left != NULL) ? in_root->left->getHeight() : 0;

    int balance =  0;
    
}
#endif

bool AVL::rec_remove(Node * &in_root, int &in_data){

    if(in_root == NULL){
        return false;
    } else if(in_root->getData() == in_data){
        //if a match is found
        Node * tmp_root = in_root;
        if(in_root->left == NULL){
            Node * tmp_right = in_root->right;
            delete in_root;
            in_root = tmp_right;
        } else if(in_root->right == NULL){
            Node * tmp_left = in_root->left;
            delete in_root;
            in_root = tmp_left;
        } else {
            rec_replace_parent(tmp_root, in_root->left);          
            delete tmp_root;
            return true;
        }
        return true;
    } else if(in_data < in_root->getData()){
        bool ret_val = rec_remove(in_root->left, in_data);
        bool decrease = ret_val;
        if(decrease){
            if(in_root->getBalance() == 0){
                decrease = false;
            }
            if(in_root->getBalance() > 1){
                decrease = false;
                //rebalance right
                if(in_root->right->getBalance() < 0){
                    //rotate right subtree right
                    rot_right(in_root->right);
                }
                //rotate parent left
                rot_left(in_root);
            }
        }

        return ret_val;
    } else if(in_data > in_root->getData()){
        bool ret_val = rec_remove(in_root->right, in_data);
        bool decrease = ret_val;
        if(decrease){
            if(in_root->getBalance() == 0){
                decrease = true;
            }
            if(in_root->getBalance() < -1){
                decrease = false;
                //rebalance left
                if(in_root->left->getBalance() > 0){
                    //rotate left subtree left
                    rot_left(in_root->left);
                }
                //rotate parent right
                rot_right(in_root);
            }
        } 
        return ret_val;
    }
    return false;
}

bool AVL::rec_replace_parent(Node * &old_root, Node * &local_root){
    static Node * tmp_node = NULL;
    static int back_cnt = 0;
    if(local_root->right != NULL){
        tmp_node = local_root;
        bool ret_val = rec_replace_parent(old_root, local_root->right);
        if(ret_val){
            if(local_root->getBalance() < -1){
                rot_right(local_root);
            }    
        }
#if 0
        //if(back_cnt > 0) back_cnt++;
        if(ret_val 
                //&& (back_cnt == 1)
                ){
            if(tmp_node->getBalance() < -1){
                //if(tmp_node->left != NULL){
                //    if(tmp_node->left->getBalance() > 0){
                //        //rotate left subtree left
                //        rot_left(tmp_node->left);
                //    }
                //}
#if DEBUG
                cout << "rotating right around node w/ val " << tmp_node->getData() << endl;
                cout << "left val: " << 
                    ((tmp_node->left != NULL)? tmp_node->left->getData() : 0) 
                    << "right val: " << 
                    ((tmp_node->right != NULL)? tmp_node->right->getData() : 0) << endl;
                cout << "back_cnt = " << back_cnt << endl;
#endif
                back_cnt = 0;
                rot_right(tmp_node);
#if DEBUG
                cout << "new node w/ val " << tmp_node->getData() << endl;
                cout << "left val: " << 
                    ((tmp_node->left != NULL)? tmp_node->left->getData() : 0) 
                    << "right val: " << 
                    ((tmp_node->right != NULL)? tmp_node->right->getData() : 0) << endl;
                cout << "back_cnt = " << back_cnt << endl;
#endif
            }
            back_cnt = 0;
            return false;
        } else {
            //return true; 
            return false;
        }
#endif
        return false;
    } else {
        old_root->data = local_root->data;
        old_root = local_root;
        local_root = local_root->left;
#if 0 
        tmp_node->right = local_root;
        if(tmp_node->getBalance() < -1){
            rot_right(tmp_node);
        }
#endif

        //back_cnt = 1;
        return true;
    }
}

NodeInterface * AVL::getRootNode(){
    return root;
}
bool AVL::add(int data){
    bool add_ret = rec_add(root, data);
    if(!add_ret) return false;
    //rec_balance(root);
    return true; 
    
}
bool AVL::remove(int data){
    return rec_remove(root, data);
}
void AVL::clear(){
    while(root != NULL){
        remove(root->data);
    }
}
