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
                _alloc_n.construct(_n, Node<Value>());
                _n->is_black = true;
                _n->is_nil = true;
                _h = _alloc_n.allocate(1);
                _alloc_n.construct(_h, Node<Value>());
                _h->value = _alloc_v.allocate(1);
                _alloc_v.construct(_h->value, Value());
                _h->is_black = true;
            }

            void put(node_pointer dst, node_pointer n)
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
                                _rotate_right(node->parent->parent);
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
};

#endif