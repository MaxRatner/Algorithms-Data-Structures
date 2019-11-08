/*
 Реализуйте структуру данных “массив строк” на основе декартового дерева по неявному ключу со следующими методами:
 // Добавление строки в позицию position.\\
 // Все последующие строки сдвигаются на одну позицию вперед.\\
 void InsertAt( int position, const std::string& value );\\
 // Удаление строки из позиции position.\\
 // Все последующие строки сдвигаются на одну позицию назад.\\
 void DeleteAt( int position );\\
 // Получение строки из позиции position.\\
 std::string GetAt( int position );
 Все методы должны работать за O(log n) в среднем, где n – текущее количество строк в массиве.
 */
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int key;
    int value;
    Node* left;
    Node* right;
    string s;
    int size;
    
    void update();
    Node(string str);
};

void Node::update() {
    size = 1;
    
    if (left != NULL) {
        size = left->size + size;
    }
    
    if (right != NULL) {
        size = right->size + size;
    }
}

Node::Node(string str){
    s = str;
    key = 0;//////////////////
    
    left = NULL;
    right = NULL;
    
    size = 1;
}

class TreePiramid {
public:
    pair<Node*, Node*> Split(Node*, int);
    void Treap(int, int, Node*&);
    void DFSTreap(Node*, int);
    void InsertAt(int, string&);
    
    string GetAt(int);
    void DeleteAt(int);
    Node* root;
    
    /*TreePiramid() {
        root = nullptr;
    }*/
    
    Node* Merge(Node*, Node*);
    void Solver();
private:
    Node* NodeT;
};

void TreePiramid::DeleteAt(int pos) {
    pair<Node*, Node*> p1 = Split(root, pos);
    pair<Node*, Node*> p2 = Split(p1.second, 1);
    
    delete p2.first;
    root = Merge(p1.first, p2.second);
}

string TreePiramid::GetAt(int k) {
    Node* cur_node = root;
    
    do {
        int cur_left_size;
        if (cur_node->left != NULL) {
            cur_left_size = cur_node->left->size;
        } else {
            cur_left_size = 0;
        }
        
        if (cur_left_size == k) {
            break;
        }
        if (cur_left_size > k) {
            cur_node = cur_node->left;
        } else {
            k = k - cur_left_size + 1;
            cur_node = cur_node->right;
        }
        
    } while (true);
    
    return cur_node->s;
}

void TreePiramid::InsertAt(int pos, string& str) {
    Node* new_node = new Node(str);
    
    pair<Node*, Node*> node2 = Split(root, pos);
    
    Node* rtree = Merge(new_node, node2.second);
    root = Merge(node2.first, rtree);
}


pair<Node*, Node*> TreePiramid::Split(Node* curnode, int k) {
    if (curnode == NULL){
        ///curnode->left = NULL;
        //curnode->right = NULL;
        pair<Node*, Node*> temp = make_pair(nullptr, nullptr);
        return temp;
    }
    
    int left_s;
    
    if (curnode->left != NULL) {
        left_s = curnode->left->size;
    } else {
        left_s = 0;
    }
    if (left_s >= k) {
        pair<Node*, Node*> ans = Split(curnode->left, k);
        curnode->left = ans.second;
        curnode->update();
        
        return make_pair(ans.first, curnode);
    } else {
        
        pair<Node*, Node*> ans = Split(curnode->right, k - left_s - 1);
        curnode->right = ans.first;
        curnode->update();
        
        return make_pair(curnode, ans.second);
    }
}

Node* TreePiramid::Merge(Node* p1, Node* p2){
    if (p2 == nullptr) {
        return p1;
    }
    if (p1 == nullptr) {
        return p2;
    }
    
    if (p2->key < p1->key) {
        p1->right = Merge(p1->right, p2);
        p1->update();
        
        return p1;
    } else {
        p2->left = Merge(p1, p2->left);
        p2->update();
        
        return p2;
    }
}


void TreePiramid::Treap(int key, int value, Node*& root) {
    if(root == NULL){
        return;
    }
    if (root->value < value){
        return;
    }
    
    if (key <= root->key){
        Treap(key, value, root->left);
    } else {
        Treap(key, value, root->right);
    }
}

void TreePiramid::Solver() {
    
    int n;
    cin >> n;
    vector<string> answer;
    
    root = nullptr;
    
    for (int i = 0; i < n; i++) {
        string in;
        cin >> in;
        
        if (in == "+") {
            int a;
            string str;
            cin >> a >> str;
            
            InsertAt(a, str);
        }
        if (in == "-") {
            int a;
            cin >> a;
            DeleteAt(a);
        }
        if (in == "?"){
            int a;
            cin >> a;
            
            answer.push_back(GetAt(a));
        }
    }
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << endl;
    }
}

int main(){
    
    TreePiramid pir;
    
    pir.Solver();
    
    return 0;
}
