#include "ACN.h"
#include <iostream>
typedef KeyTree<char,NodeData> TreeType;
ACN::ACN()
{
    head->state= 0;
    size = 1;
}
void ACN::add_pattern(const char* pat)
{
    TreeType::iterator ite;
    ite = head.iter();
    const char* read = pat;
    NodeData ins;
    while(*read!=0){
        if(!ite->has_key(*read)){
            ins.state = size++;
            ite = ite->add_child(*read, ins);
            invalid = true;
        }else{
            ite = (*ite)[*read];
        }
        read++;
    }
    output[ite->v().state].push_back(pat);
}
TreeType* ACN::_goto(TreeType* from,char key)
{
    if(from == &head){
        if(head.has_key(key)) return head[key];
        else return &head;
    }else{
        if(from->has_key(key)) return (*from)[key];
        return failure[from->v().state];
    }
}
void ACN::caculate_failure()
{
    if(!invalid) return;
    failure.resize(size);
    TreeType::wide_iterator ite;
    for(ite = head.wide_iter();ite!=false;ite++){
        if(ite->depth()<=1) 
            failure[(*ite)->state]=&head;
        else{
            TreeType* to = _goto(failure[ite->parent()->v().state],ite.key());
            failure[ite->v().state] = to;
            if(!output[to->v().state].empty()){
                vector<string>::iterator ins,end,ins_pos;
                ins = output[to->v().state].begin();
                end = output[to->v().state].end();
                ins_pos = output[ite->v().state].end();
                output[ite->v().state].insert(ins_pos,ins,end);
            }
        }
    }
    invalid = false;
}
void ACN::open_buffer(const char* buff)
{
    document = buff;
    caculate_failure();
    clear();
}
void ACN::clear()
{
    read_ptr = document;
    tree_ptr = &head;
    last_result = NULL;
}

bool ACN::fetch(string& res,int& pos)
{
    if(invalid) caculate_failure();
    char read;
    if(last_result){
        res = (*last_result)[last_idx];
        pos = read_ptr-document-res.size();
        last_idx++;
        if(last_idx==last_result->size()) last_result = NULL;
        return true;
    }
    while(*read_ptr){
        read = *read_ptr;
        tree_ptr = _goto(tree_ptr,read);
        vector<string>& c = output[tree_ptr->v().state];
        if(!c.empty()){
            res = c[0];
            read_ptr++;
            pos = read_ptr-document-res.size();
            tree_ptr = _goto(tree_ptr,read);
            if(c.size()>1){
                last_result = &c;
                last_idx = 1;
            }
            return true;
        }
        read_ptr++;
    }
    return false;
}
