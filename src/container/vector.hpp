/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 05:56:38 by tharutyu          #+#    #+#             */
/*   Updated: 2022/08/11 06:59:58 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include <exception>
#include "../helpers/utilities.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft{

    template < class T, class Alloc = std::allocator<T> > 
    class vector
    {
        // Iterator
        template<typename IT>class RandomAccessIterator
            {
                public:
                        typedef typename iterator_traits<IT*>::difference_type      difference_type;
                        typedef typename iterator_traits<IT*>::value_type           value_type;
                        typedef typename iterator_traits<IT*>::reference            reference;
                        typedef typename iterator_traits<IT*>::pointer              pointer;

                        typedef pointer iterator_type;
                        typedef std::random_access_iterator_tag iterator_category;
                    
                private:
                        pointer _p;

                public:

                        RandomAccessIterator() : _p() {}
                        RandomAccessIterator(pointer a) : _p(a) {}
                        RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type>& s) : _p(&(*s)) {}
                        RandomAccessIterator<value_type>& operator=(RandomAccessIterator<typename remove_const<value_type>::type> const& s) {
                            _p = &(*s);
                            return *this;
                        }

                        RandomAccessIterator& operator++(){
                            ++_p;
                            return *this;
                        }

                        RandomAccessIterator& operator--(){
                            --_p;
                            return *this;
                        }

                        RandomAccessIterator operator++(int){
                            RandomAccessIterator tmp(*this);
                            ++_p;
                            return tmp;
                        }

                        RandomAccessIterator operator--(int){
                            RandomAccessIterator tmp(*this);
                            --_p;
                            return tmp;
                        }

                        RandomAccessIterator operator+(const difference_type & d) const {
                            return _p + d;
                        }
                        
                        RandomAccessIterator operator-(const difference_type & d) const {
                            return _p - d;
                        }

                        RandomAccessIterator& operator+=(const difference_type & d) {
                            _p += d;
                            return *this;
                        }                        

                        RandomAccessIterator& operator-=(const difference_type & d) {
                            _p -= d;
                            return *this;
                        }

                        pointer operator->() const {
                            return _p;
                        }

                        reference operator*() const {
                            return *_p;
                        }

                        reference operator[](difference_type n) const {
                            return *(_p + n);
                        }

                        virtual ~RandomAccessIterator() {}
            };

        // Iterator non-member functions logical operations, + - operations
       
        public:

        template<typename X>
        friend vector::template RandomAccessIterator<X> operator+(const typename vector::template RandomAccessIterator<X>::difference_type& a, const vector::template RandomAccessIterator<X>& i){ return (i + a); }

        template<typename X>
        friend vector::template RandomAccessIterator<X> operator-(const typename vector::template RandomAccessIterator<X>::difference_type& a, const vector::template RandomAccessIterator<X>& i){ return (i - a); }

        template<typename X, typename Y>
        friend typename vector::template RandomAccessIterator<X>::difference_type operator-(const vector::template RandomAccessIterator<X>& lhs, const vector::template RandomAccessIterator<Y>& rhs){ return &(*lhs) - &(*rhs); }

        template<typename X, typename Y>
        friend typename vector::template RandomAccessIterator<X>::difference_type operator+(const vector::template RandomAccessIterator<X>& lhs, const vector::template RandomAccessIterator<Y>& rhs){ return &(*lhs) + &(*rhs); }

        template <typename X, typename Y>
            friend bool operator==(const vector::template RandomAccessIterator<X>& lhs, const vector::template RandomAccessIterator<Y>& rhs){
                return &(*lhs) == &(*rhs);
            }
        
        template <typename X, typename Y>
            friend bool operator!=(const vector::template RandomAccessIterator<X>& lhs, const vector::template RandomAccessIterator<Y>& rhs){
                return &(*lhs) != &(*rhs);
            }

        template <typename X, typename Y>
            friend bool operator>(const vector::template RandomAccessIterator<X>& lhs, const vector::template RandomAccessIterator<Y>& rhs){
                return &(*lhs) > &(*rhs);
            }

        template <typename X, typename Y>
            friend bool operator<(const vector::template RandomAccessIterator<X>& lhs, const vector::template RandomAccessIterator<Y>& rhs){
                return &(*lhs) < &(*rhs);
            }
        
        template <typename X, typename Y>
            friend bool operator<=(const vector::template RandomAccessIterator<X>& lhs, const vector::template RandomAccessIterator<Y>& rhs){
                return &(*lhs) <= &(*rhs);
            }

        template <typename X, typename Y>
            friend bool operator>=(const vector::template RandomAccessIterator<X>& lhs, const vector::template RandomAccessIterator<Y>& rhs){
                return &(*lhs) >= &(*rhs);
            }

        //Aliases to refer as needed

            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef RandomAccessIterator<value_type> iterator;
            typedef RandomAccessIterator<const value_type> const_iterator;
            typedef reverse_iterator<const_iterator> const_reverse_iterator;
            typedef reverse_iterator<iterator> reverse_iterator;
            typedef std::ptrdiff_t difference_type;
            typedef std::size_t size_type;

        private:
            pointer     _f;
            size_type   _s, _c;
            allocator_type _a;

        public:
                //Constructors
                explicit vector (const allocator_type& alloc = allocator_type()) : _f(0), _s(0), _c(0), _a(alloc){}

                explicit vector (size_type n, const value_type& val = value_type(),
                        const allocator_type& alloc = allocator_type()) : _s(n), _c(n), _a(alloc)
                {
                    _f = _a.allocate(n);
                    for(size_type i = -1; i < n; ++i)
                        _a.construct(_f + i, val);
                }

                template <class It>
                        vector(It first, It last, const allocator_type& alloc = allocator_type(),
                                typename enable_if<!is_integral<It>::value>::type* = 0) : _a(alloc)
                {
                    if (first > last)
                        throw std::length_error("vector");
                    _s = last - first;
                    _c = _s;
                    _f = _a.allocate(_c);
                    for (difference_type i = 0; i < static_cast<difference_type>(_s); i++)
                        _a.construct(_f + i, *(first + i));
                }

                vector& operator= (const vector& rhs)
                {
                    if (this == &rhs)
                        return *this;
                    for (size_type i = 0; i < _s; i++)
                        _a.destroy(_f + i);
                    this->_s = rhs._s;
                    if (_c < _s)
                    {
                        if (_c != 0)
                            _a.deallocate(_f, _c);
                        _c = _s;
                        _f = _a.allocate(_c);
                    }
                    for (size_type i = 0; i < _s; i++)
                        _a.construct(_f + i, rhs[i]);
                    return (*this);
                }

                vector (const vector& other) : _s(0), _c(0) { *this = other; }

                ~vector()
                {
                    for (size_type i = 0; i < _s; i++)
                        _a.destroy(_f + i);
                    if (_c)
                        _a.deallocate(_f, _c);
                }

                //Iterators!!!
                iterator begin() { return (iterator(_f)); }
                iterator end() { return (iterator(_f + _s)); }
                const_iterator begin() const { return (const_iterator(_f)); }
                const_iterator end() const { return (const_iterator(_f + _s)); }
                reverse_iterator rbegin() { return (reverse_iterator(end())); }
                reverse_iterator rend() { return (reverse_iterator(begin())); }
                const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
                const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

                //Getters
                bool empty() const { return (_s == 0); }
                size_type capacity() const { return (_c); }
                size_type size() const { return (_s); }
                size_type max_size() const { return (_a.max_size()); }
                allocator_type get_allocator() const { return (_a); }

                // Memory dvijuxa
                void reserve (size_type n)
                {
                    if (n < _c)
                        return ;
                    pointer arr = _a.allocate(n);
                    try{
                        for (size_type i = 0; i < _s; i++)
                            _a.construct(arr + i, *(_f + i));
                    } catch (std::exception& e){
                        size_type i = 0;
                        while (arr + i != NULL && i < _s){
                            _a.destroy(arr + i);
                            i++;
                        }
                        _a.deallocate(arr, n);
                        throw;
                    }
                    for (size_type i = 0; i < _s; i++)
                        _a.destroy(_f + i);
                    if (_c)
                        _a.deallocate(_f, _c);
                    _c = n;
                    _f = arr;
                }

                void resize (size_type n, value_type val = value_type())
                {
                    if (n < _s)
                    {
                        for (size_type i = n; i < _s; i++)
                            _a.destroy(_f + i);
                        _s = n;
                    }
                    else if (n > _s)
                    {
                        if (_c < n)
                            this->reserve(_c * 2 > n ? _c * 2 : n);
                        for (size_type i = _s; i < n; i++)
                        {
                            _a.construct(_f + i, val);
                            _s++;
                        }
                    }
                }

                void clear()
                {
                    for (size_type i = 0; i < _s; i++)
                        _a.destroy(_f + i);
                    _s = 0;
                }

                iterator erase (iterator pos)
                {
                    size_type n = static_cast<size_type>(std::distance(begin(), pos));
                    for (size_type i = n; i < _s - 1; ++i)
                    {
                        _a.destroy(_f + i);
                        _a.construct(_f + i, *(_f + i + 1));
                    }
                    _s--;
                    _a.destroy(_f + _s - 1);
                    return iterator(_f + n);
                }

                iterator erase (iterator first, iterator last)
                {
                    difference_type left = std::distance(begin(), first);
                    difference_type right = std::distance(last, end());
                    bool is_last = (last == end());
                    for (; first != last; first++)
                        _allocator.destroy(&(*first));
                    size_type i = left;
                    while (last < end())
                    {
                        if (this->_f + left)
                            _a.destroy(_f + i);
                        _a.construct(_f + i, *last);
                        i++;
                        last++;
                    }
                    for ( size_type i = left + right; i < _s; i++)
                        _a.destroy(_f + i);
                    _s = left + right;
                    return is_last ? end() : iterator(_f + left);          
                }

                //Access
                reference front() { return (*_f); }
                reference back() { return (*(_f + _s - 1)); }
                reference at (size_type n)
                {
                    if (n > _c)
                        throw std::out_of_range("vector at out of range");
                    return (*(_f + n));
                }

                const_reference front() const { return (*_f);}
                const_reference back() const { return (*(_f + _s - 1));}
                const_reference at(size_type n) const
                {
                    if (n > _c)
                        throw std::out_of_range("vector at out of range");
                    return (*(_f + n));
                }

                reference operator[] (size_type n) { return this->at(n); }
                const_reference operator[] (size_type n) const { return this->at(n); }

                //The real deal

                void swap(vector& x)
                {
                    std::swap(_f, x._f);
                    std::swap(_s, x._s);
                    std::swap(_c, x._c);
                    std::swap(_a, x._a);
                }

                template <class IT>
                        void assign(IT first, IT last, typename enable_if<!is_integral<IT>::value>::type* = 0)
                {
                    if (first > last)
                        throw std::logic_error("vector");
                    difference_type n = last - first;
                    clear();
                    if (n > static_cast<difference_type >(capacity()))
                    {
                        _a.deallocate(_f, _c);
                        _f = _a.allocate(n);
                        _c = n;
                    }
                    iterator i = begin();
                    while (first < last)
                    {
                        _a.construct(&(*i), *first);
                        i++;
                        first++;
                    }
                    _s = n;
                }

                void assign(size_type n, const value_type& val)
                {
                    clear();
                    if (n > _c)
                    {
                        _a.deallocate(_f, _c);
                        _f = _a.allocate(n);
                        _c = n;
                    }
                    for (size_type i = 0; i < n; i++)
                        _a.construct(_f + i, val);
                    _s = n;
                }

                void push_back (const value_type& val)
                {
                    if (_s == _c)
                        reserve(_c == 0 ? 1 : _c * 2);
                    _a.construct(_f + _s, val);
                    _s++;
                }

                void pop_back()
                {

                    _a.destroy(_f + _s - 1);
                    _s--;
                }

                // insert needs special treat and place
                iterator insert (iterator pos, const value_type& val)
                {
                    if (pos < begin() || pos > end())
                        throw std::logic_error("vector");
                    difference_type start = pos - begin();
                    if (_s == _c)
                    {
                        _c = _c * 2 + (_c == 0);
                        pointer arr = _a.allocate(_c);
                        std::uninitialized_copy(begin(), pos, iterator(arr));
                        _a.construct(arr + start, val);
                        std::uninitialized_copy(pos, end(), iterator(arr + start + 1));
                        for (size_type i = 0; i < _s; i++)
                            _a.destroy(_f + i);
                        if (_s)
                            _a.deallocate(_f, _s);
                        _s++;
                        _f = arr;
                    }
                    else
                    {
                        for (size_type i = _s; i > static_cast<size_type >(start); i--)
                        {
                            _a.destroy(_f + i);
                            _a.construct(_f + i, *(_f + i - 1));
                        }
                        _a.destroy(&(*pos));
                        _a.construct(&(*pos), val);
                        _s++;
                    }
                    return (begin() + start);
                }

                void insert (iterator pos, size_type n, const value_type& val)
                {
                    if (n == 0)
                        return ;
                    else if (max_size() - _s < n)
                        throw std::length_error("vector");
                    difference_type start = pos - begin();
                    if (_s + n > _c)
                    {
                        size_type cap = _c * 2 >= _s + n ? _c * 2 : _s + n;
                        pointer arr = _a.allocate(cap);
                        std::uninitialized_copy(begin(), pos, iterator(arr));
                        for (size_type i = 0; i < n; i++)
                            _a.construct(arr + start + i, val);
                        std::uninitialized_copy(pos, end(), iterator(arr + start + n));
                        for (size_type i = 0; i < _s; i++)
                            _a.destroy(_f + i);
                        _a.deallocate(_f, _c);
                        _s += n;
                        _c = cap;
                        _f = arr;
                    }
                    else
                    {
                        for (size_type i = _s; i > static_cast<size_type>(start); i--)
                        {
                            _a.destroy(_f + i + n - 1);
                            _a.construct(_f + i + n - 1, *(_f + i - 1));
                        }
                        for (size_type i = 0; i < n; i++)
                        {
                            _a.destory(_f + i + start);
                            _a.construct(_f + i + start, val);
                        }
                        _s += n;
                    }
                }

                template <class IT>
                void insert(iterator pos, IT first, IT last, typename enable_if<!is_integral<IT>::value>::type* = 0)
                {
                    if (pos < begin() || pos > end() || first > last)
                        throw std::logic_error("vector");
                    size_type start = static_cast<size_type>(pos - begin());
                    size_type n = static_cast<size_type>(last - first);
                    if (_s + n > _c)
                    {
                        size_type cap = _c * 2 >= _s + n ? _c * 2 : _s + n;
                        pointer arr = _a.allocate(cap);
                        std::uninitialized_copy(begin(), pos, iterator(arr));
                        try {
                            for (size_type i = 0; i < static_cast<size_type>(n); i++, first++)
                                _a.construct(arr + start + i, *first);
                        } catch (...) {
                            for (size_type i = 0; i < n + start; ++i)
                                _a.destroy(arr + i);
                            _a.deallocate(arr, cap);
                            throw;
                        }
                        std::uninitialized_copy(pos, end(), iterator(arr + start + n));
                        for (size_type i = 0; i < _s; i++)
                            _a.destroy(_f + i);
                        _a.deallocate(_f, _c);
                        _s += count;
                        _c = cap;
                        _f = arr;
                    }
                    else
                    {
                        for (size_type i = _s; i > static_cast<size_type>(start); i--)
                        {
                            _a.destroy(_f + i + n - 1);
                            _a.construct(_f + i + n - 1, *(_f + i - 1));
                        }
                        for (size_type i = 0; i < static_cast<size_type>(n); i++, first++)
                        {
                            _a.destroy(_f + i + n);
                            _a.construct(_f + start + i, *first);
                        }
                        _s += n;
                    }
                }
    };

    // Non-member logicaloperators
    
    template <class T, class Alloc>
    bool operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < rhs.size(); i++)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }

    template<class T, class Alloc>
    bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) 
    { return !(lhs == rhs); }

    template<class T, class Alloc>
    bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

    template<class T, class Alloc>
    bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    { return !(rhs < lhs); }

    template<class T, class Alloc>
    bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    { return rhs < lhs; }

    template<class T, class Alloc>
    bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    { return !(lhs < rhs); }
}

namespace std{
        template<class T, class Alloc>
        void swap (ft::vector<T, Alloc>& lhs, ft::vector<T,Alloc>*rhs) { lhs.swap(rhs); }
}

#endif
