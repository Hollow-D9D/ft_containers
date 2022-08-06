/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 05:56:38 by tharutyu          #+#    #+#             */
/*   Updated: 2022/08/03 05:56:38 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include "../iterators/iterator_traits.hpp"
#include "../helpers/enable_if.hpp"


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
                        RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type>& s>) : _p(&(*s)) {}
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

                        RandomAccessIterator& operator++(int){
                            RandomAccessIterator tmp(*this);
                            ++_p;
                            return tmp;
                        }

                        RandomAccessIterator& operator--(int){
                            RandomAccessIterator tmp(*this);
                            --_p;
                            return tmp;
                        }

                        RandomAccessIterator& operator+(const difference_type & d) const {
                            return _p + d;
                        }
                        
                        RandomAccessIterator& operator-(const difference_type & d) const {
                            return _p - d;
                        }

                        RandomAccessIterator& operator+=(const difference_type & d) const {
                            _p += a;
                            return *this;
                        }                        

                        RandomAccessIterator& operator-=(const difference_type & d) const {
                            _p -= a;
                            return *this;
                        }

                        pointer operator->() const {
                            return _p;
                        }

                        reference operator*() const {
                            return *_p;
                        }

                        reference operator[](size_t n) const {
                            return *(_p + n);
                        }

                        virtual ~RandomAccessIterator() {}
            };

        public:
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef iterator;
            typedef const_iterator;
            typedef reverse_iterator;
            typedef const_reverse_iterator;
            typedef std::ptrdiff_t difference_type;
            typedef std::size_t size_type;

        private:
            pointer     _f;
            size_type   _s, _c;
            allocator_type _a;

    };
}

#endif