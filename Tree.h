#ifndef KEYTREE_H_H
#define KEYTREE_H_H
#include <map>
#include <stack>
#include <queue>
#include <stdio.h>
using namespace std;
template<class K,class V>
class KeyTree{
    typedef typename map<K,KeyTree*>::iterator Child_Iter;
    typedef pair<Child_Iter,Child_Iter> Iter_Val;
    V _value;
    map<K,KeyTree*> _child;
    KeyTree* _parent;
    int _depth;
    void delete_child(KeyTree*);
    class _iterator{
        friend class KeyTree;
        protected:
            KeyTree* tree;
            bool ended;
            Child_Iter ptr;
            Child_Iter end;
            KeyTree* _ptr(){
                if(tree) return tree;
                else return ptr->second;
            }
        public:
            _iterator():tree(NULL),ended(false){}
            _iterator(KeyTree* kt):tree(kt),ended(false){}
            operator bool(){return !ended;}
            operator KeyTree*(){ return _ptr(); }
            KeyTree& operator*(){ return *_ptr();}
            KeyTree* operator->(){ return _ptr(); }
            _iterator& operator=(KeyTree* t){
                tree = t;ended=false;
                return *this;
            }
            const K key(){
                if(tree) return K();
                return ptr->first;
            }
    };
    public:
    class depth_iterator:public _iterator{
        friend class KeyTree;
        stack<Iter_Val> kept;
        public:
        depth_iterator():_iterator(){}
        depth_iterator(KeyTree* t):_iterator(t){}
        depth_iterator& operator++();
        depth_iterator operator++(int){
            depth_iterator ite = *this;
            this->operator++();
            return ite;
        }
    };
    class wide_iterator:public _iterator{
        friend class KeyTree;
        deque<Iter_Val> kept;
        public:
        wide_iterator():_iterator(){}
        wide_iterator(KeyTree* t):_iterator(t){}
        wide_iterator& operator++();
        wide_iterator operator++(int){
            wide_iterator ite = *this;
            this->operator++();
            return ite;
        }
    };
    typedef depth_iterator iterator;
    iterator iter(){ return depth_iter(); }
    depth_iterator depth_iter(){ return depth_iterator(this); }
    wide_iterator wide_iter(){ return wide_iterator(this); }
    KeyTree():_depth(0),_parent(NULL){}
    ~KeyTree();
    V& v(){return _value;}
    V& operator*(){return _value;}
    V* operator->(){return &_value;}
    KeyTree* add_child(const K& key,const V& value);
    KeyTree* get_child(const K& key){return _child[key];}
    KeyTree* operator[](const K& key){return _child[key];}
    int depth(){return _depth;}
    KeyTree* parent(){return _parent;}
    bool has_key(const K& key){ return _child.find(key) != _child.end(); }
};

template<class K,class V>
KeyTree<K,V>*
KeyTree<K,V>::add_child(const K& key,const V& value)
{
    KeyTree* n = new KeyTree();
    n->_parent = this;
    n->_value = value;
    n->_depth = _depth+1;
    _child[key] = n;
    return n;
}

template<class K,class V>
void KeyTree<K,V>::delete_child(KeyTree* tree)
{
    Child_Iter ite;
    for(ite = tree->_child.begin();ite != tree->_child.end();ite++){
        delete ite->second;
    }
    _child.clear();
}

template<class K,class V>
KeyTree<K,V>::~KeyTree()
{
    delete_child(this);
}

template<class K,class V>
typename KeyTree<K,V>::depth_iterator& 
KeyTree<K,V>::depth_iterator::operator++(){
    bool& ended = this->ended;
    Child_Iter& ptr = this->ptr;
    Child_Iter& end = this->end;
    KeyTree*& tree = this->tree;
    

    if(ended) return *this;
    if((*this)->_child.empty()){
        this->ptr++;
        if(ptr!=end){
            return *this;
        }
        do{
            if(kept.empty()){
                ended = true;
                return *this;
            }
            Iter_Val v = kept.top();
            kept.pop();
            ptr = v.first;
            end = v.second;
            ptr++;
        }while(ptr == end);
        return *this;
    }
    if(tree){
        ptr = tree->_child.begin();
        end = tree->_child.end();
        tree = NULL;
    }else{
        kept.push(Iter_Val(ptr,end));
        end = ptr->second->_child.end();
        ptr = ptr->second->_child.begin();
    }
    return *this;
}
template<class K,class V>
typename KeyTree<K,V>::wide_iterator& 
KeyTree<K,V>::wide_iterator::operator++(){
    bool& ended = this->ended;
    Child_Iter& ptr = this->ptr;
    Child_Iter& end = this->end;
    KeyTree*& tree = this->tree;

    if(tree){
        ptr = tree->_child.begin();
        end = tree->_child.end();
        tree = NULL;
        return *this;
    }
    kept.push_back(Iter_Val((*this)->_child.begin(),(*this)->_child.end()));
    ptr++;
    if(ptr!=end){
    }else{
        do{
            if(kept.empty()){
                ended = true;
                return *this;
            }
            ptr = kept.front().first;
            end = kept.front().second;
            kept.pop_front();
        }while(ptr == end);
        return *this;
    }
}
#endif
