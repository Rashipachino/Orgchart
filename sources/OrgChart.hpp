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
                }; 
            Node* root; //head of OrgChart

        public:
            class level_order_iterator{
                private:
                    queue <Node*> q;
                public:
                    level_order_iterator(Node* ptr){
                        if(ptr != nullptr){
                            q.push(ptr);
                        }
                    }
                    Node* get_top(){
                        return this->q.front();
                    }
                    string& operator*() const;
                    string* operator->() const;
                    level_order_iterator operator++();
                    level_order_iterator operator++(int);
                    bool operator==(const level_order_iterator& lit) const;
                    bool operator!=(const level_order_iterator& lit) const;
            };
            class reverse_order_iterator{
                    private:
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
                        reverse_order_iterator operator++(int);
                        bool operator==(const reverse_order_iterator& rit) const;
                        bool operator!=(const reverse_order_iterator& rit) const;
                        
            };
            class preorder_order_iterator{
                    private:
                        stack<Node*> stk;
                    public:
                        preorder_order_iterator(Node* ptr){
                            if(ptr != nullptr){
                                stk.push(ptr);
                            }
                        }
                        Node* get_top(){
                            return stk.top();
                        }
                        string& operator*() const;
                        string* operator->() const;
                        preorder_order_iterator operator++();
                        preorder_order_iterator operator++(int);
                        bool operator==(const preorder_order_iterator& pit) const;
                        bool operator!=(const preorder_order_iterator& pit) const;
            };
            OrgChart(){ //constructor
                this->root = nullptr;
            }
            ~OrgChart(){ //deconstructor
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
            OrgChart(const OrgChart& other){ //copy constructor
                this->root = other.root;
            }
            OrgChart& operator=(const OrgChart& other){
                if(this != &other){ //to avoid recursion
                    this->root = other.root;
                }
                return *this;
                
            }
            OrgChart(OrgChart&& other) noexcept : root(nullptr) { //move constructor
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
            OrgChart& add_root(string const& name);
            OrgChart& add_sub(string const& higher, string const& lower);
            level_order_iterator begin_level_order() const;
            level_order_iterator end_level_order() const;
            reverse_order_iterator begin_reverse_order();
            reverse_order_iterator reverse_order();
            preorder_order_iterator begin_preorder();
            preorder_order_iterator end_preorder();
            friend ostream& operator<< (ostream& output, const OrgChart& o);
            static void print_Org(ostream& output, Node* root, int count);
            level_order_iterator begin() const;
            level_order_iterator end() const;
    };
}
#endif