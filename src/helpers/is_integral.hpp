/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:12:03 by tharutyu          #+#    #+#             */
/*   Updated: 2022/08/03 01:12:03 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft
{
    //Remove Const
    template <class T> struct remove_const { typedef T type; };
    template <class T> struct remove_const <const T> { typedef T type; };

    //Conditional
    template<bool B, class T, class F>
    struct conditional {typedef F type;};
    template<class T, class F>
    struct conditional<true, T, F> {typedef T type; };

    //Is integral
    template <typename T>
    struct is_integral { static const bool val = false; };

    template <>
    struct is_integral<bool> { static const bool val = true; };

    template <>
    struct is_integral<char> { static const bool val = true; };

    template <>
    struct is_integral<signed char> { static const bool val = true; };

    template <>
    struct is_integral<short> { static const bool val = true; };

    template <>
    struct is_integral<wchar_t> { static const bool val = true; };

    template <>
    struct is_integral<char16_t> { static const bool val = true; };

    template <>
    struct is_integral<int> { static const bool val = true; };

    template <>
    struct is_integral<long> { static const bool val = true; };

    template <>
    struct is_integral<long long> { static const bool val = true; };

    template <>
    struct is_integral<unsigned char> { static const bool val = true; };

    template <>
    struct is_integral<unsigned short> { static const bool val = true; };

    template <>
    struct is_integral<unsigned int> { static const bool val = true; };

    template <>
    struct is_integral<unsigned long> { static const bool val = true; };

    template <>
    struct is_integral<unsigned long long> { static const bool val = true; };

}

#endif