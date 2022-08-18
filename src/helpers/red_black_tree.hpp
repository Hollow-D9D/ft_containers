#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <memory>
#include "./utilities.hpp"
#include "../iterators/tree_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"


//RED BLACK TREE!!! SHELTER MEEE! SHEEELTER ME!
template<class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value> >
class red_black_tree
{
    public:
            //general
            typedef Value   value_type;
            typedef Compare value_compare;
            typedef Alloc   allocator_type;
            
            typedef typename Alloc::template rebind<ft::Node<Value> >::other    node_allocator;
            
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;

            typedef std::ptrdiff_t  difference_type;
            typedef std::size_t     size_type;
            
            //iterators
            typedef ft::TreeIterator<Value>                 iterator;
            typedef ft::TreeIterator<const Value>           const_iterator;
            typedef ft::reverse_iterator<iterator>          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

            //node
            typedef typename node_allocator::pointer node_pointer;

    private:
            //bread and butter
            allocator_type      _alloc_v;
            node_allocator      _alloc_n;
            value_compare       _c;
            node_pointer        _n;
            node_pointer        _h;
            node_pointer        _r;
            size_type           _s;

            //helpers
            bool is_nil(node_pointer n) const { return n == _n || n == _h; }

            void free_node(node_pointer n)
            {
                _alloc_v.destroy(n->value);
                _alloc_v.deallocate(n->value, 1);
                _alloc_n.deallocate(n, 1);
            }

            void clear_node(node_pointer n)
            {
                if (n && !is_nil(n))
                {
                    clear_node(n->right);
                    clear_node(n->left);
                    free_node(n);
                }
            }

            void init_nil_head()
            {
                _n = _alloc_n.allocate(1);
                _alloc_n.construct(_n, ft::Node<Value>());
                _n->is_black = true;
                _n->is_nil = true;
                _h = _alloc_n.allocate(1);
                _alloc_n.construct(_h, ft::Node<Value>());
                _h->value = _alloc_v.allocate(1);
                _alloc_v.construct(_h->value, Value());
                _h->is_black = true;
            }

            void transplant(node_pointer dst, node_pointer n)
            {
                if (dst == _r)
                    _r = n;
                else if (dst == dst->parent->left)
                    dst->parent->left = n;
                else
                    dst->parent->right = n;
                n->parent = dst->parent;
            }

            node_pointer    tree_min(node_pointer n) const
            {
                while (n != NULL && !is_nil(n->left))
                    n = n->left;
                return n;
            }    

            node_pointer    tree_max(node_pointer n) const
            {
                while (n != NULL && !is_nil(n->right))
                    n = n->right;
                return n;
            }

            void    _rotate_right(node_pointer n)
            {
                node_pointer p;

                p = n->left;
                n->left = p->right;
                if (!is_nil(p->right))
                    p->right->parent = n;
                p->parent = n->parent;
                if (n->parent == NULL)
                    _r = p;
                else if (n == n->parent->left)
                    n->parent->left = p;
                else
                    n->parent->right = p;
                p->right = n;
                n->parent = p;

            }

            void    _rotate_left(node_pointer n)
            {
                node_pointer p;

                p = n->right;
                n->right = p->left;
                if (!is_nil(p->left))
                    p->left->parent = n;
                p->parent = n->parent;
                if (n->parent == NULL)
                    _r = p;
                else if(n == n->parent->left)
                    n->parent->left = p;
                else
                    n->parent->right = p;
                p->left = n;
                n->parent = p;
            }

            node_pointer _insert_to_node(node_pointer r, node_pointer n)
            {
                if (_c(*n->value, *r->value))
                {
                    if (!is_nil(r->left))
                        return (_insert_to_node(r->left, n));
                    r->left = n;
                }
                else
                {
                    if (!is_nil(r->right))
                        return (_insert_to_node(r->right, n));
                    r->right = n;
                }
                n->parent = r;
                return (n);
            }

            node_pointer _insert(node_pointer n)
            {
                if (_r == _h)
                    _r = n;
                else
                    _insert_to_node(_r, n);
                return n;
            }

            node_pointer _insert_tree(node_pointer n, node_pointer dst)
            {
                if (_r == _h)
                    _r = n;
                else
                    _insert_to_node(dst, n);
                return (n);
            }

            void _insert_recover(node_pointer n)
            {
                if (n != _r && n->parent != _r)
                {
                    while(n != _r && !n->parent->is_black)
                    {
                        if (n->parent == n->parent->parent->left)
                        {
                            node_pointer u = n->parent->parent->right;
                            if (!u->is_black)
                            {
                                n->parent->is_black = true;
                                u->is_black = true;
                                n->parent->parent->is_black = false;
                                n = n->parent->parent;
                            }
                            else
                            {
                                if (n == n->parent->right)
                                {
                                    n = n->parent;
                                    _rotate_left(n);
                                }
                                n->parent->is_black = true;
                                n->parent->parent->is_black = false;
                                _rotate_right(n->parent->parent);
                            }
                        }
                        else
                        {
                            node_pointer u = n->parent->parent->left;
                            if (!u->is_black)
                            {
                                n->parent->is_black = true;
                                u->is_black = true;
                                n->parent->parent->is_black = false;
                                n = n->parent->parent;
                            }
                            else
                            {
                                if (n == n->parent->left)
                                {
                                    n = n->parent;
                                    _rotate_right(n);
                                }
                                n->parent->is_black = true;
                                n->parent->parent->is_black = false;
                                _rotate_left(n->parent->parent);
                            }
                        }
                    }
                }
                _r->is_black = true;
            }

            public:

                //getters
                size_type size() const { return (_s); }
                size_type max_size() const { return (_alloc_v.max_size()); }
                bool empty() const { return (_s == 0); }
                value_compare value_comp() const { return (_c); }
                allocator_type get_allocator() const { return (_alloc_v); }

                //Iterators
                iterator begin() { return (iterator(_s == 0 ? _h : iterator(tree_min(_r)))); }
                iterator end() { return (iterator(_h)); }
                const_iterator begin() const { return (const_iterator(_s == 0 ? _h : const_iterator(tree_min(_r)))); }
                const_iterator end() const { return const_iterator(_h); }
                reverse_iterator rbegin() { return (reverse_iterator(end())); }
                reverse_iterator rend() { return reverse_iterator(begin()); }
                const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
                const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }


                //Copy and creation
                pointer create_value(const value_type & value)
                {
                    pointer rtn = _alloc_v.allocate(1);
                    _alloc_v.construct(rtn, value);
                    return rtn;
                }

                node_pointer copy_node(node_pointer other)
                {
                    node_pointer rtn = _alloc_n.allocate(1);
                    _alloc_n.construct(rtn, ft::Node<Value>());
                    rtn->is_black = other->is_black;
                    rtn->is_nil = other->is_nil;
                    if (other->value)
                    {
                        rtn->value = _alloc_v.allocate(1);
                        _alloc_v.construct(rtn->value, *other->value);
                    }
                    return (rtn);
                }

                void copy_child(node_pointer my_node, node_pointer other)
                {
                    if (other->left->is_nil)
                        my_node->left = _n;
                    else
                    {
                        my_node->left = copy_node(other->left);
                        my_node->left->parent = my_node;
                        copy_child(my_node->left, other->left);
                    }
                    if(other->right->is_nil)
                        my_node->right = _n;
                    else if (other->right->right == NULL)
                    {
                        my_node->right = _h;
                        _h->parent = my_node;
                    }
                    else
                    {
                        my_node->right = copy_node(other->right);
                        my_node->right->parent = my_node;
                        copy_child(my_node->right, other->right);
                    }
                }

                //Search/Find
                node_pointer search(const value_type &value, node_pointer node) const
                {
                    if (!node || is_nil(node))
                        return NULL;
                    if (_c(value, *node->value))
                        return search(value, node->left);
                    if (_c(*node->value, value))
                        return search(value, node->right);
                    return node;
                }

                iterator find(const value_type& value)
                {
                    node_pointer find_res = search(value, _r);
                    return (find_res == NULL ? end() : iterator(find_res));
                }

                const_iterator find(const value_type& value) const
                {
                    node_pointer find_res = search(value, _r);
                    return (find_res == NULL ? end() : const_iterator(find_res));
                }

                //Insert
                ft::pair<iterator, bool> insert(value_type const &value)
                {
                    node_pointer find_val = search(value, _r);
                    if (find_val)
                        return ft::pair<iterator, bool>(iterator(find_val), false);
                    node_pointer new_node = _alloc_n.allocate(1);
                    _alloc_n.construct(new_node, ft::Node<value_type>(create_value(value)));
                    new_node->left = _n;
                    new_node->right = _n;
                    _insert_tree(new_node, _r);
                    ft::pair<iterator, bool> res(iterator(new_node), true);
                    _insert_recover(new_node);
                    _s++;
                    new_node = tree_max(_r);
                    new_node->right = _h;
                    _h->parent = new_node;
                    return res;
                }

                iterator insert(iterator position, const value_type& value)
                {
                    node_pointer new_node = search(value, _r);
                    if (new_node)
                        return (iterator(new_node));
                    new_node = _alloc_n.allocate(1);
                    _alloc_n.construct(new_node, ft::Node<value_type>(create_value(value)));
                    new_node->left = _n;
                    new_node->right = _n;
                    if (position == begin())
                    {
                        if (position != end() && _c(value, *position))
                            _insert_tree(new_node, tree_min(_r));
                        else
                            _insert_tree(new_node, _r);
                    }
                    else if (position == end())
                    {
                        if (position != begin() && _c(*(--position), value))
                            _insert_tree(new_node, _h->parent);
                        else
                            _insert_tree(new_node, _r);
                    }
                    else
                        _insert_tree(new_node, _r);
                    _insert_recover(new_node);
                    _s++;
                    node_pointer max_of_tree = tree_max(_r);
                    max_of_tree->right = _h;
                    _h->parent = max_of_tree;
                    return (iterator(new_node));
                }

                template<class IT>
                void insert(typename ft::enable_if<!ft::is_integral<IT>::value, IT>::type first, IT last)
                {
                    while( first != last)
                    {
                        insert(*first);
                        ++first;
                    }
                }

                //Erase

                void clear()
                {
                    clear_node(_r);
                    _r = _h;
                    _h->parent = NULL;
                    _s = 0;
                }
                void erase_fixup(node_pointer x)
                {
                    node_pointer brother;
                    while (x != _r && x->is_black){
                        if (x == x->parent->left){
                            brother = x->parent->right;
                            //case 1
                            if (!brother->is_black){
                                brother->is_black = true;
                                x->parent->is_black = false;
                                _rotate_left(x->parent);
                                brother = x->parent->right;
                            }
                            //case 2
                            if (brother->left->is_black && brother->right->is_black){
                                brother->is_black = false;
                                x = x->parent;
                            }
                            else{
                            //case 3
                                if (brother->right->is_black){
                                    brother->left->is_black = true;
                                    brother->is_black = false;
                                    _rotate_right(brother);
                                    brother = x->parent->right;
                                }
                            //case 4
                                brother->is_black = x->parent->is_black;
                                x->parent->is_black = true;
                                brother->right->is_black = true;
                                _rotate_left(x->parent);
                                x = _r;
                            }
                        }
                        else{
                            brother = x->parent->left;
                            //case 1
                            if (!brother->is_black){
                                brother->is_black = true;
                                x->parent->is_black = false;
                                _rotate_right(x->parent);
                                brother = x->parent->left;
                            }
                            //case 2
                            if (brother->right->is_black && brother->left->is_black){
                                brother->is_black = false;
                                x = x->parent;
                            }
                            else{
                            //case 3
                                if (brother->left->is_black){
                                    brother->right->is_black = true;
                                    brother->is_black = false;
                                    _rotate_left(brother);
                                    brother = x->parent->left;
                                }
                            //case 4
                                brother->is_black = x->parent->is_black;
                                x->parent->is_black = true;
                                brother->left->is_black = true;
                                _rotate_right(x->parent);
                                x = _r;
                            }
                        }
                    }
                }

                void erase(iterator pos)
                {
                    node_pointer y = pos.node(), x, for_free = y;
                    bool y_original_is_black = y->is_black;
                    if (is_nil(y->left)){
                        x = y->right;
                        transplant(y, y->right);
                    }
                    else if (is_nil(y->right)){
                        x = y->left;
                        transplant(y, y->left);
                    }
                    else {
                        node_pointer z = y;
                        y = tree_min(z->right);
                        y_original_is_black = y->is_black;
                        x = y->right;
                        if (y->parent != z){
                            transplant(y, y->right);
                            y->right = z->right;
                            z->right->parent = y;
                        }
                        transplant(z, y);
                        y->left = z->left;
                        y->left->parent = y;
                        y->is_black = z->is_black;
                    }
                    free_node(for_free);
                    if (y_original_is_black)
                        erase_fixup(x);
                    _s--;
                    _n->parent = NULL;
                    if (_s == 0)
                        _r = _h;
                    else{
                        if (_s != 1)
                            x = tree_max(_r);
                        else
                            x = _r;
                        x->right = _h;
                        _h->parent = x;
                    }
                }

                size_type erase(const value_type& value)
                {
                    node_pointer res = search(value, _r);
                    if (res)
                        erase(iterator(res));
                    return (res != NULL);
                }

                void erase(iterator first, iterator last)
                {
                    while (first != last)
                        erase(first++);
                }

                //Constructors
                red_black_tree(const Compare &c, const allocator_type& a = allocator_type()) : _alloc_v(a), _alloc_n(node_allocator()), _c(c), _r(0), _s(0)
                {
                    init_nil_head();
                    _r = _h;
                }

                red_black_tree() : _alloc_v(allocator_type()), _alloc_n(node_allocator()), _c(value_compare()), _r(0), _s(0)
                {
                    init_nil_head();
                    _r = _h;
                }

                template<class IT>
                red_black_tree(typename ft::enable_if< !ft::is_integral<IT>::value, IT>::type first, IT last, const value_compare& c, const allocator_type& a = allocator_type()) : _alloc_v(a), _alloc_n(node_allocator()), _c(c)
                {
                    init_nil_head();
                    _r = _h;
                    for (; first != last; ++first)
                        insert(*first);
                }

                red_black_tree(const red_black_tree& copy) : _c(copy._c), _r(NULL) { *this = copy; }

                red_black_tree& operator=(const red_black_tree& rhs)
                {
                    if (this == &rhs)
                        return *this;
                    this->_alloc_n = rhs._alloc_n;
                    this->_alloc_v = rhs._alloc_v;
                    this->_c = rhs._c;
                    if (this->_r == NULL)
                        init_nil_head();
                    else
                        clear_node(_r);
                    if (rhs._s == 0)
                        this->_r = this->_h;
                    else
                    {
                        this->_r = copy_node(rhs._r);
                        copy_child(this->_r, rhs._r);
                    }
                    this->_s = rhs._s;
                    return *this;
                }

                ~red_black_tree() 
                {
                    clear_node(_r);
                    _alloc_v.destroy(_h->value);
                    _alloc_v.deallocate(_h->value, 1);
                    _alloc_n.deallocate(_n, 1);
                    _alloc_n.deallocate(_h, 1);
                }

                iterator upper_bound(const value_type& value)
                {
                    iterator last = end();
                    for (iterator first = begin(); first != last; ++first)
                        if (_c(value, *first))
                            return (first);
                    return(last);
                }

                iterator lower_bound(const value_type& value)
                {
                    iterator last = end();
                    for (iterator first = begin(); first != last; ++first)
                        if (!_c(*first, value))
                            return (first);
                    return (last);
                }

                const_iterator upper_bound(const value_type& value) const
                {
                    const_iterator last = end();
                    for (const_iterator first = begin(); first != last; ++first)
                        if (!_c(value, *first))
                            return (first);
                    return last;
                }

                const_iterator lower_bound(const value_type& value) const 
                {
                    const_iterator last = end();
                    for (const_iterator first = begin(); first != last; ++first)
                        if (!_c(*first, value))
                            return (first);
                    return last;
                }

                size_type count(const value_type& value) const { return (find(value) != end()); }
                void swap (red_black_tree &rhs)
                {
                    std::swap(this->_r, rhs._r);
                    std::swap(this->_n, rhs._n);
                    std::swap(this->_h, rhs._h);
                    std::swap(this->_s, rhs._s);
                    std::swap(this->_alloc_n, rhs._alloc_n);
                    std::swap(this->_alloc_v, rhs._alloc_v);
                    std::swap(this->_c, rhs._c);
                }    
                
                ft::pair<iterator, iterator> equal_range(const value_type& value) { return (ft::make_pair(lower_bound(value), upper_bound(value))); }


};

//logic operators
template <class T, class Compare, class Alloc>
bool operator<(const red_black_tree<T, Compare, Alloc>& lhs, const red_black_tree<T, Compare, Alloc>& rhs)
{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template <class T, class Compare, class Alloc>
bool operator>(const red_black_tree<T, Compare, Alloc>& lhs, const red_black_tree<T, Compare, Alloc>& rhs)
{ return (lhs < rhs); }

template <class T, class Compare, class Alloc>
bool operator==(const red_black_tree<T, Compare, Alloc>& lhs, const red_black_tree<T, Compare, Alloc>& rhs)
{ return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

template <class T, class Compare, class Alloc>
void swap(const red_black_tree<T, Compare, Alloc>& lhs, const red_black_tree<T, Compare, Alloc>& rhs)
{ lhs.swap(rhs); }
#endif