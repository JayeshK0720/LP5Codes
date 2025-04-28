#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

class TreeNode{
    public:
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val){
            data = val;
            left = right = NULL;
        }
};

class Tree{
    public:
        TreeNode* root;

        Tree(){
            root = NULL;
        }

        void insert(int val){
            TreeNode* newNode = new TreeNode(val);
            if(root == NULL){
                root = newNode;
                return; 
            }

            queue<TreeNode*> q;
            q.push(root);

            while(!q.empty()){
                TreeNode* temp = q.front();
                q.pop();

                if(temp -> left == NULL){
                    temp->left = newNode;
                    return;
                } else{
                    q.push(temp->left);
                }

                if(temp -> right == NULL){
                    temp->right = newNode;
                    return;
                } else{
                    q.push(temp->right);
                }
            }
        }

        void parallelBFS(){
            if(!root) return;

            vector<TreeNode*> currentLevel = {root};

            while(!currentLevel.empty()){
                vector<TreeNode*> nextLevel;

                #pragma omp parallel for
                for(int i=0; i<currentLevel.size(); i++){
                    TreeNode* node = currentLevel[i];

                    #pragma omp critical
                    cout<< node->data << " | ";

                    #pragma omp critical
                    {
                        if(node -> left) nextLevel.push_back(node->left);
                        if(node -> right) nextLevel.push_back(node->right);
                    }
                }

                currentLevel = nextLevel;
            }
            cout<<endl;
        }

        void parallelDFS() {
            if(!root) return;

            stack<TreeNode*> s;
            s.push(root);

            while(!s.empty()) {
                TreeNode* node;

                #pragma omp critical
                {
                    if (!s.empty()) {
                        node = s.top();
                        s.pop();
                        cout << node->data << " | ";
                    }
                }

                #pragma omp parallel sections
                {
                    #pragma omp section
                    {
                        if (node->right) {
                            #pragma omp critical
                            s.push(node->right);
                        }
                    }
                    #pragma omp section
                    {
                        if (node->left) {
                            #pragma omp critical
                            s.push(node->left);
                        }
                    }
                }
            }
            cout << endl << endl;
        }
};

int main(){
    Tree* t = new Tree();

    while(true){
        int choice;
        cout<<"\nEnter 1-Insert | 2-Parallel BFS | 3-Parallel DFS | 0-Exit : ";
        cin>>choice;

        if(choice == 1){
            int val;
            cout<<"Enter a number : ";
            cin>>val;
            t->insert(val);
        } else if(choice==2){
            auto start = high_resolution_clock::now();
            cout<<"\nParallel BFS Traversal : ";
            t->parallelBFS();
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout<< "Execution Time : " << duration.count() << " ms\n";
        } else if(choice == 3){
            auto start = high_resolution_clock::now();
            cout<<"\nParallel DFS Traversal : ";
            t->parallelDFS();
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout<< "Execution Time : " << duration.count() << " ms\n";
        } else if(choice == 0){
            cout<< "Exited Successfully .."<<endl;
            break;
        } else{
            cout<< "Invalid input. Try Again..."<<endl;
        }
    }
    return 0;
}