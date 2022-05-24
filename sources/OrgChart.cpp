#include <iostream>
#include <vector>
#include "OrgChart.hpp"
using namespace std;
namespace ariel{
            string& OrgChart::level_order_iterator::operator*() const{
                return this->q.front()->name;
            }      
            string* OrgChart::level_order_iterator::operator->() const{
                return &(this->q.front()->name);
            }  
            OrgChart::level_order_iterator OrgChart::level_order_iterator::operator++(){
                if(q.empty()){ //end of chart
                    return *this;
                }
                for(unsigned long i = 0; i < this->q.front()->subs.size(); i++){
                    q.push(this->q.front()->subs[i]); //push all subs into queue
                }
                q.pop(); //delete from queue
                return *this;
            }
            const OrgChart::level_order_iterator OrgChart::level_order_iterator::operator++(int){
                level_order_iterator tmp= *this;
                if(q.empty()){ //end of chart
                    return tmp;
                }
                for(unsigned long i = 0; i < this->q.front()->subs.size(); i++){
                    q.push(this->q.front()->subs[i]); //push all subs into queue
                }
                q.pop(); //delete from queue
			    return tmp;
            }
            bool OrgChart::level_order_iterator::operator==(const OrgChart::level_order_iterator& rhs) const{
                if((this->q.empty() && !rhs.q.empty()) || (!this->q.empty() && rhs.q.empty())){
                    return false;
                }
                if(this->q.empty() && rhs.q.empty()){
                    return true;
                }
                return this->q.front() == rhs.q.front();
            }
            bool OrgChart::level_order_iterator::operator!=(const OrgChart::level_order_iterator& rhs) const{
                return !(*this == rhs); 
            }
            OrgChart::level_order_iterator& OrgChart::level_order_iterator::operator=(const OrgChart::level_order_iterator& other){
                        if(this==&other){
                            return *this;
                        }
                        this->q = other.q;
                        return *this;
            }
            
            string& OrgChart::reverse_order_iterator::operator*() const{
                return this->reverse_stk.top()->name;
            }
            string* OrgChart::reverse_order_iterator::operator->() const{
                return &(this->reverse_stk.top()->name);
            }
            OrgChart::reverse_order_iterator OrgChart::reverse_order_iterator::operator++(){
                reverse_stk.pop();
                return *this;
            }
            const OrgChart::reverse_order_iterator OrgChart::reverse_order_iterator::operator++(int){
                reverse_order_iterator tmp = *this;
                reverse_stk.pop();
                return tmp;                
            }
            bool OrgChart::reverse_order_iterator::operator==(const OrgChart::reverse_order_iterator& rhs) const{
                if((this->reverse_stk.empty() && !rhs.reverse_stk.empty()) || (!this->reverse_stk.empty() && rhs.reverse_stk.empty())){
                    return false;
                }
                if(this->reverse_stk.empty() && rhs.reverse_stk.empty()){
                    return true;
                }
                return this->reverse_stk.top() == rhs.reverse_stk.top();
            }

            bool OrgChart::reverse_order_iterator::operator!=(const OrgChart::reverse_order_iterator& rhs) const{
                return !(*this == rhs);
            }
            OrgChart::reverse_order_iterator& OrgChart::reverse_order_iterator::operator=(const reverse_order_iterator& other){
                if(this==&other){
                    return *this;
                }
                this->reverse_stk = other.reverse_stk;
                return *this;
            }

            string& OrgChart::preorder_order_iterator::operator*() const{
                return this->stk.top()->name;
            }
            string* OrgChart::preorder_order_iterator::operator->() const{
                return &(this->stk.top()->name);
            }

            OrgChart::preorder_order_iterator OrgChart::preorder_order_iterator::operator++(){
                // cout << "++" << endl;
                if(stk.empty()){
                    return *this;
                }
                Node* top = stk.top();
                //Node* top = new Node(stk.top()->name, stk.top()->subs);
                stk.pop(); //delete from stk
                if(!(top->subs.empty())){ //sub exists
                    for(unsigned long i = top->subs.size() - 1; i >= 0 && i < top->subs.size(); i--){
                        // cout << i << endl;
                        // cout << "before push: " << top->subs.at(i)->name << endl;
                        stk.push(top->subs.at(i));
                        // cout << "after push top: " << stk.top()->name << endl;
                    }
                }
                return *this;
            }
            
            const OrgChart::preorder_order_iterator OrgChart::preorder_order_iterator::operator++(int){
                preorder_order_iterator tmp = *this;
                if(stk.empty()){
                    return tmp;
                }
                for(unsigned long i = this->stk.top()->subs.size() - 1; i >= 0; i--){
                    stk.push(this->stk.top()->subs[i]);
                }
                stk.pop(); //delete from stk
                return tmp;
            }
            bool OrgChart::preorder_order_iterator::operator==(const preorder_order_iterator& rhs) const{
                if((this->stk.empty() && !rhs.stk.empty()) || (!this->stk.empty() && rhs.stk.empty())){
                    return false;
                }
                if(this->stk.empty() && rhs.stk.empty()){
                    return true;
                }
                return this->stk.top() == rhs.stk.top();
            }

            bool OrgChart::preorder_order_iterator::operator!=(const preorder_order_iterator& rhs) const{
                // cout << "!=" << endl;
                return !(*this == rhs);
            //    if(!this->stk.empty() && rhs.stk.empty()){
            //        cout << "inside if" << endl;
            //         return true;
            //     }
            //     if(this->stk.empty() && rhs.stk.empty()){
            //         return false;
            //     }
            //     return this->stk.top() != rhs.stk.top(); 
            }
            OrgChart::preorder_order_iterator& OrgChart::preorder_order_iterator::operator=(const preorder_order_iterator& other){
                if(this==&other){
                    return *this;
                }
                this->stk = other.stk;
                return *this;
            }


            OrgChart OrgChart::add_root(string name){
                if(this->root != nullptr){
                    throw invalid_argument("root already exists in this chart");
                }
                Node* new_root = new Node(name); //node with name and no subs yet
                this->root = new_root;
                return *this;
            }
            OrgChart OrgChart::add_sub(string higher, string lower){
                level_order_iterator it = begin_level_order();
                while(it != end_level_order()){
                    if(*it == higher){
                        break;
                    }
                    it++;
                }
                if(it == end_level_order()){
                    throw invalid_argument("higher person does not exist");
                }
                Node* sub =  new Node(lower);
                it.get_top()->subs.push_back(sub); //add lower to the vector subs or higher
                return *this; //return chart once updates have finished
            }

            OrgChart::level_order_iterator OrgChart::begin_level_order() const{
                return level_order_iterator(this->root);
            }
            OrgChart::level_order_iterator OrgChart::end_level_order() const{
                return level_order_iterator(nullptr);
            }
            
            OrgChart::reverse_order_iterator OrgChart::begin_reverse_order(){
                return reverse_order_iterator(this->root);
            }
            OrgChart::reverse_order_iterator OrgChart::reverse_order(){
                return reverse_order_iterator(nullptr);
            }
            OrgChart::preorder_order_iterator OrgChart::begin_preorder(){
                return preorder_order_iterator(this->root);
            }
            OrgChart::preorder_order_iterator OrgChart::end_preorder(){
                return preorder_order_iterator(nullptr);
            }
            std::ostream& operator<< (std::ostream& output, const OrgChart& o){
                OrgChart::print_Org(output, o.root, 0);
                return output;
            }
            void OrgChart::print_Org(ostream& output, Node* root, int count){
                if(root != nullptr){
                    for(int i = 0; i < count; i++){
                        output << "|-----";
                    }
                    output << root->name << endl;
                    for(unsigned long i = 0; i < root->subs.size(); i++){
                        print_Org(output, root->subs[i], count+1);
                    }
                }
            }
            OrgChart::level_order_iterator OrgChart::begin(){
                return begin_level_order();
            }
            OrgChart::level_order_iterator OrgChart::end(){
                return end_level_order();
            }
    };
