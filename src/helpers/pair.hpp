/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:11:46 by tharutyu          #+#    #+#             */
/*   Updated: 2022/08/03 01:11:46 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
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

    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

}

#endif