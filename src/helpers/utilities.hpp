/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 07:31:40 by tharutyu          #+#    #+#             */
/*   Updated: 2022/08/10 01:59:06 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

namespace ft
{
    //ENABLE_IF
    template <bool b, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> {typedef T type; };

    //EQUAL
    template <class it1, class it2>
    bool equal (it1 f1, it1 l1, it2 f2)
    {
        while (f1 != l1)
        {
            if (!(*f1 == *f2))
                return false;
            ++f1;++f2;
        }
        return true;
    }

    //LEXICOGRAPHICAL COMPARE
    template<class it1, class it2>
    bool lexicographical_compare(it1 f1, it1 l1, it2 f2, it2 l2)
    {
        for (; f1 != l1; f1++, f2++)
        {
            if (f2 == l2 || *f1 > *f2) return false;
            else if (*f1 < *f2) return true;
        }
        return (f2 != l2);
    }

    template<class it1, class it2, class pred>
    bool lexicographical_compare(it1 f1, it1 l1, it2 f2, it2 l2, pred compare)
    {
        for (; f1 != l1; f1++, f2++)
        {
            if (f2 == l2 || compare(*f2, *f1)) return false;
            else if (compare(*f1, *f2)) return true;
        }
        return (f2 != l2);
    }

    //REMOVE_CONST
    template <class T> struct remove_const { typedef T type; };
    template <class T> struct remove_const <const T> { typedef T type; };

    //CONDITIONAL
    template<bool B, class T, class F>
    struct conditional {typedef F type;};
    template<class T, class F>
    struct conditional<true, T, F> {typedef T type; };

    //IS_INTEGRAL
    template<class T, bool val>
            struct integral_constant{
                static const bool value = val;
                typedef T value_type;
                typedef integral_constant type;
                operator value_type() const { return value; }
            };

    template <class T>
    struct is_integral : public ft::integral_constant<T, false> {};

    template <>
    struct is_integral<bool> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<char> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<signed char> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<short> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<wchar_t> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<char16_t> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<int> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<long> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<long long> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned char> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned short> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned int> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned long> : public ft::integral_constant<bool, true>{  };

    template <>
    struct is_integral<unsigned long long> : public ft::integral_constant<bool, true>{  };

    //PAIR
     template <typename T1, typename T2>
    class pair 
    {
        typedef T1 first_type;
        typedef T2 second_type;

        public:
            first_type first;
            second_type second;
        

            // Constructors
            pair() : first(), second() {}
            template<class U, class V> 
            pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
            pair (const pair& pr) : first(pr.first), second(pr.second) {}
            pair (const first_type& a, const second_type& b) : first(a), second(b) {}

            pair &operator=(const pair &pr) { first = pr.first; second = pr.second; return *this;}

    };

    template <typename T1, typename T2>
    bool operator==(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
    { return lhs.first == rhs.first && lhs.second == rhs.second; }

    template <typename T1, typename T2>
    bool operator!=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
    { return !(lhs == rhs); }

    template <typename T1, typename T2>
    bool operator<(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
    { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

        template <typename T1, typename T2>
    bool operator<=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
    { return !(rhs < lhs) ; }

        template <typename T1, typename T2>
    bool operator>(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
    { return rhs < lhs; }

        template <typename T1, typename T2>
    bool operator>=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
    { return !(lhs < rhs); }

    //MAKE_PAIR
    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

}

#endif
