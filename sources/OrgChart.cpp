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
            OrgChart::level_order_iterator OrgChart::level_order_iterator::operator++(int){
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
            bool OrgChart::level_order_iterator::operator==(const OrgChart::level_order_iterator& lit) const{
                //must check if q is empty to avoid segmentation fault
                if((this->q.empty() && !lit.q.empty()) || (!this->q.empty() && lit.q.empty())){
                    return false;
                }
                if(this->q.empty() && lit.q.empty()){
                    return true;
                }
                return this->q.front() == lit.q.front();
            }
            bool OrgChart::level_order_iterator::operator!=(const OrgChart::level_order_iterator& lit) const{
                return !(*this == lit); 
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
            OrgChart::reverse_order_iterator OrgChart::reverse_order_iterator::operator++(int){
                reverse_order_iterator tmp = *this;
                reverse_stk.pop();
                return tmp;                
            }
            bool OrgChart::reverse_order_iterator::operator==(const OrgChart::reverse_order_iterator& rit) const{
                if((this->reverse_stk.empty() && !rit.reverse_stk.empty()) || (!this->reverse_stk.empty() && rit.reverse_stk.empty())){
                    return false;
                }
                if(this->reverse_stk.empty() && rit.reverse_stk.empty()){
                    return true;
                }
                return this->reverse_stk.top() == rit.reverse_stk.top();
            }

            bool OrgChart::reverse_order_iterator::operator!=(const OrgChart::reverse_order_iterator& rit) const{
                return !(*this == rit);
            }

            string& OrgChart::preorder_order_iterator::operator*() const{
                return this->stk.top()->name;
            }
            string* OrgChart::preorder_order_iterator::operator->() const{
                return &(this->stk.top()->name);
            }

            OrgChart::preorder_order_iterator OrgChart::preorder_order_iterator::operator++(){
                if(stk.empty()){
                    return *this;
                }
                Node* top = stk.top();
                stk.pop(); //delete from stk
                for(unsigned long i = top->subs.size() - 1; i >= 0 && i < top->subs.size(); i--){
                    stk.push(top->subs.at(i)); //push all subs in
                }
                return *this;
            }
            
            OrgChart::preorder_order_iterator OrgChart::preorder_order_iterator::operator++(int){
                preorder_order_iterator tmp = *this;
                if(stk.empty()){
                    return tmp;
                }
                 Node* top = stk.top();
                 stk.pop(); //delete from stk
                for(unsigned long i = top->subs.size() - 1; i >= 0 && i < top->subs.size(); i--){
                    stk.push(top->subs[i]); //push all subs in
                }
                return tmp;
            }
            bool OrgChart::preorder_order_iterator::operator==(const preorder_order_iterator& pit) const{
                if((this->stk.empty() && !pit.stk.empty()) || (!this->stk.empty() && pit.stk.empty())){
                    return false;
                }
                if(this->stk.empty() && pit.stk.empty()){
                    return true;
                }
                return this->stk.top() == pit.stk.top();
            }

            bool OrgChart::preorder_order_iterator::operator!=(const preorder_order_iterator& pit) const{
                return !(*this == pit);
            }


            OrgChart& OrgChart::add_root(string const& name){
                if(this->root == nullptr){
                    this->root = new Node(name); //create a new node and make it the root
                    return *this;
                }
                this->root->name = name; //simply change the name of the root
                return *this;
            }
            OrgChart& OrgChart::add_sub(string const& higher, string const& lower){
                if(this->root == nullptr){
                    throw invalid_argument("can't add sub before adding root");
                }
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
                it.get_top()->subs.push_back(new Node(lower)); //add lower to the vector subs or higher
                return *this; //return chart once updates have finished
            }

            OrgChart::level_order_iterator OrgChart::begin_level_order() const{
                if(this->root == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return level_order_iterator(this->root);
            }
            OrgChart::level_order_iterator OrgChart::end_level_order() const{
                if(this->root == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return level_order_iterator(nullptr);
            }
            
            OrgChart::reverse_order_iterator OrgChart::begin_reverse_order(){
                if(this->root == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return reverse_order_iterator(this->root);
            }
            OrgChart::reverse_order_iterator OrgChart::reverse_order(){
                if(this->root == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return reverse_order_iterator(nullptr);
            }
            OrgChart::preorder_order_iterator OrgChart::begin_preorder(){
                if(this->root == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return preorder_order_iterator(this->root);
            }
            OrgChart::preorder_order_iterator OrgChart::end_preorder(){
                if(this->root == nullptr){
                    throw invalid_argument("chart is empty");
                }
                return preorder_order_iterator(nullptr);
            }
            std::ostream& operator<< (std::ostream& output, const OrgChart& o){
                OrgChart::print_Org(output, o.root, 0); //calls helper function to print 
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
            OrgChart::level_order_iterator OrgChart::begin() const{
                return begin_level_order();
            }
            OrgChart::level_order_iterator OrgChart::end() const{
                return end_level_order();
            }
    };
