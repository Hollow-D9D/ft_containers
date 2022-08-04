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

#include <iostream>

namespace ft{

    template < class T, class Alloc = std::allocator<T> > 
    class vector
    {
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef allocator_type::reference reference;
        typedef allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef iterator;
        typedef const_iterator;
        typedef reverse_iterator;
        typedef const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;
    };
}

#endif