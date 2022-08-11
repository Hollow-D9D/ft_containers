/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:36:32 by tharutyu          #+#    #+#             */
/*   Updated: 2022/08/11 06:36:32 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include "./vector.hpp"

namespace ft
{

template<class T, class Container = ft::vector<T> >
class stack
{
    public:
        typedef T value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef Container container_type;
        typedef typename Container::size_type size_type;
    
    private:
        container_type _c;

    public:
        //constructors
        explicit stack(const container_type& container = container_type()) : _c(container) {};

        stack(const stack& copy) : _c(copy._c) {}

        stack& operator=(const stack& rhs)
        {
            _c = rhs._c;
            return (*this);
        }

        //base 
        bool empty() const { return (_c.empty()); }
        size_type size() const { return (_c.size()); }
        value_type& top() { return (_c.back()); }
        const value_type& top() const { return (_c.back()); }
        void push (const value_type& val) { _c.push_back(val); }
        void pop () { _c.pop_back(); }

        template <class X, class Cont>
            friend bool operator== (const stack<X,Cont>& lhs, const stack<X,Cont>& rhs) { return (lhs._c == rhs._c); }
        template <class X, class Cont>
            friend bool operator!= (const stack<X,Cont>& lhs, const stack<X,Cont>& rhs) { return (lhs._c != rhs._c); }
        template <class X, class Cont>
            friend bool operator< (const stack<X,Cont>& lhs, const stack<X,Cont>& rhs) { return (lhs._c < rhs._c); }
        template <class X, class Cont>
            friend bool operator<= (const stack<X,Cont>& lhs, const stack<X,Cont>& rhs) { return (lhs._c <= rhs._c); }
        template <class X, class Cont>
            friend bool operator> (const stack<X,Cont>& lhs, const stack<X,Cont>& rhs) { return (lhs._c > rhs._c); }
        template <class X, class Cont>
            friend bool operator>= (const stack<X,Cont>& lhs, const stack<X,Cont>& rhs) { return (lhs._c >= rhs._c); }

    };

}


#endif