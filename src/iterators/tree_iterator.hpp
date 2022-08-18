/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 11:30:32 by tharutyu          #+#    #+#             */
/*   Updated: 2022/08/12 11:30:32 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iostream>
#include "./iterator_traits.hpp"
#include "../helpers/utilities.hpp"
//Defining Node
namespace ft
{

template <class V>
struct Node
{
    public:
        V       *value;
        Node*   parent;
        Node*   left;
        Node*   right;
        bool    is_black;
        bool    is_nil;
        
        explicit Node(V *src = 0) : value(src), parent(0), left(0), right(0), is_black(false), is_nil(0) {}
        Node(Node const& copy) : value(copy.value), parent(copy.parent), left(copy.left), right(copy.right), is_black(copy.is_black), is_nil(copy.is_nil) {}
        
        Node& operator=(const Node& rhs)
        {
            this->value = rhs.value;
            this->parent = rhs.parent;
            this->left = rhs.left;
            this->right = rhs.right;
            this->is_black = rhs.is_black;
            this->is_nil = rhs.is_nil;
            return *this;
        }
        virtual ~Node(){}
};

//Iterator for tree

template<typename T>
class TreeIterator 
{
    public:
            typedef std::bidirectional_iterator_tag                     iterator_category;
            typedef typename ft::iterator_traits<T*>::value_type        value_type;
            typedef typename ft::iterator_traits<T*>::reference         reference;
            typedef typename ft::iterator_traits<T*>::pointer           pointer;
            typedef typename ft::iterator_traits<T*>::difference_type   difference_type;
            typedef Node<typename ft::remove_const<value_type>::type>*  node_pointer;

    private:
            node_pointer _n;
            
            node_pointer tree_min(node_pointer n) const 
            {
                while(n->left != NULL && !n->left->is_nil)
                    n = n->left;
                return n; 
            }

            node_pointer tree_max(node_pointer n) const 
            {
                while (!n->right->is_nil)
                    n = n->right;
                return n;
            }
    public:
            //getter
            node_pointer node() const { return _n; }

            //constructors
            TreeIterator() {}
            TreeIterator(void *node): _n(static_cast<node_pointer>(node)) {}
            TreeIterator(const TreeIterator<typename ft::remove_const<value_type>::type > & copy) { *this = copy; }
            TreeIterator& operator=(const TreeIterator<typename ft::remove_const<value_type>::type>& rhs)
            {
                this->_n = rhs.node();
                return *this;
            }
            reference operator*() const { return *(_n->value); }
            pointer operator->() const { return (_n->value); }
            TreeIterator& operator++()
            {
                if(_n->right && !_n->right->is_nil)
                {
                    _n = tree_min(_n->right);
                }
                else
                {
                    node_pointer p = _n->parent;
                    while (p != NULL && _n == p->right)
                    {
                        _n = p;
                        p = p->parent;
                    }
                    _n = p;
                }
                return *this;
            }
            TreeIterator operator++(int)
            {
                TreeIterator<value_type> temp = *this;
                if (!_n->right->is_nil)
                    _n = tree_min(_n->right);
                else
                {
                    node_pointer p = _n->parent;
                    while(p != NULL && _n == p->right)
                    {
                        _n = p;
                        p = p->parent;
                    }
                    _n = p;
                }
                return *this;
            }

            TreeIterator& operator--()
            {
                if (_n->left && !_n->left->is_nil)
                    _n = tree_max(_n->left);
                else
                {
                    node_pointer p = _n->parent;
                    while (p != NULL && _n == p->left)
                    {
                        _n = p;
                        p = p->parent;
                    }
                    _n = p;
                }
                return *this;
            }
            
            TreeIterator operator--(int)
            {
                TreeIterator<value_type> temp = *this;
                if (_n->left && !_n->left->is_nil)
                    _n = tree_max(_n->left);
                else
                {
                    node_pointer p = _n->parent;
                    while (p != NULL && _n == p->left)
                    {
                        _n = p;
                        p = p->parent;
                    }
                    _n = p;
                }
                return temp;
            }
};

template<typename A, typename B>
bool operator==(const TreeIterator<A> &lhs, const TreeIterator<B> &rhs) { return (lhs.node() == rhs.node()); }

template<typename A, typename B>
bool operator!=(const TreeIterator<A> &lhs, const TreeIterator<B> &rhs) { return (lhs.node() != rhs.node()); }

}


#endif