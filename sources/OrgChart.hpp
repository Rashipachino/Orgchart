#ifndef ORGCHART_HPP
#define ORGCHART_HPP
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
namespace ariel{
    class OrgChart
    {
        private:
            struct Node{
                    string name;
                    vector <Node*> subs;
                    Node(const string& name){ //constructor for node
                        this->name = name;
                    }
                    Node(const string& name, vector <Node*> subs){
                        this->name = name;
                        this->subs = subs;
                    }
                }; 
                // : name(name){
                //     }
                // };
            //fields
            Node* root; //head of OrgChart

        public:
            class level_order_iterator{
                private:
                    //Node* pointer_to_curr;
                    queue <Node*> q;
                public:
                    level_order_iterator(Node* ptr){
                        if(ptr != nullptr){
                            q.push(ptr);
                        }
                    }
                    level_order_iterator(const level_order_iterator& other){
                        this->q = other.q;
                    }
                    
                    Node* get_top(){
                        return this->q.front();
                    }
                    string& operator*() const;
                    string* operator->() const;
                    level_order_iterator operator++();
                    const level_order_iterator operator++(int);
                    bool operator==(const level_order_iterator& rhs) const;
                    bool operator!=(const level_order_iterator& rhs) const;
                    level_order_iterator& operator=(const level_order_iterator& other);
            };
            class reverse_order_iterator{
                    private:
                        //Node* pointer_to_curr;
                        stack<Node*> reverse_stk;
                        queue<Node*> reverse_q;
                    public:
                        reverse_order_iterator(Node* ptr){
                            if(ptr != nullptr){
                                reverse_q.push(ptr);
                                while(!reverse_q.empty()){
                                    Node* top = reverse_q.front();
                                    reverse_stk.push(top);
                                    reverse_q.pop();
                                    for(unsigned long i = top->subs.size() - 1; i >=0 && i < top->subs.size(); i--){
                                        reverse_q.push(top->subs[i]);
                                    }
                                }
                            } 
                        }        
                        string& operator*() const;
                        string* operator->() const;
                        reverse_order_iterator operator++();
                        const reverse_order_iterator operator++(int);
                        bool operator==(const reverse_order_iterator& rhs) const;
                        bool operator!=(const reverse_order_iterator& rhs) const;
                        reverse_order_iterator& operator=(const reverse_order_iterator& other);
                        
            };
            class preorder_order_iterator{
                    private:
                        //Node* pointer_to_curr;
                        stack<Node*> stk;
                    public:
                        preorder_order_iterator(Node* ptr){
                            if(ptr != nullptr){
                                stk.push(ptr);
                            }
                        }
                        preorder_order_iterator(const preorder_order_iterator& other){
                            this->stk = other.stk;
                        }
                        Node* get_top(){
                            return stk.top();
                        }
                        string& operator*() const;
                        string* operator->() const;
                        preorder_order_iterator operator++();
                        const preorder_order_iterator operator++(int);
                        bool operator==(const preorder_order_iterator& rhs) const;
                        bool operator!=(const preorder_order_iterator& rhs) const;
                        preorder_order_iterator& operator=(const preorder_order_iterator& other);
            };
            OrgChart(){
                this->root = nullptr;
            }
            ~OrgChart(){
                if(this->root != nullptr){
                    queue<Node*> del_q;
                    del_q.push(this->root);
                    while(!del_q.empty()){
                        Node* top = del_q.front();
                        for(unsigned long i = 0; i < top->subs.size(); i++){
                            del_q.push(top->subs[i]);
                        }
                        del_q.pop();
                        delete top;
                    }
                }
            }
            OrgChart(const OrgChart& other){
                this->root = other.root;
            }
            OrgChart& operator=(const OrgChart& other){
                if(this != &other){
                    this->root = other.root;
                }
                return *this;
                
            }
            OrgChart(OrgChart&& other) noexcept : root(nullptr) {
                this->root = other.root;
                other.root = nullptr;
            }
            OrgChart& operator=(OrgChart&& other) noexcept {
                if (this != &other) {
                    this->root = other.root;
                    other.root = nullptr;
                }
                return *this;
            }
            OrgChart add_root(string name);
            OrgChart add_sub(string higher, string lower);
            level_order_iterator begin_level_order() const;
            level_order_iterator end_level_order() const;
            reverse_order_iterator begin_reverse_order();
            reverse_order_iterator reverse_order();
            preorder_order_iterator begin_preorder();
            preorder_order_iterator end_preorder();
            friend ostream& operator<< (ostream& output, const OrgChart& o);
            static void print_Org(ostream& output, Node* root, int count);
            level_order_iterator begin();
            level_order_iterator end();
    };
}
#endif