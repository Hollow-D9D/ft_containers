/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:58:30 by tharutyu          #+#    #+#             */
/*   Updated: 2022/08/03 01:58:30 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP


//EQUAL
template <class it1, class it2>
bool equal (it1 f1, it1 l1, it2 f2)
{
    while (f1 != last1)
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

#endif