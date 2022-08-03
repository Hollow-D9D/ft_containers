/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 04:50:11 by tharutyu          #+#    #+#             */
/*   Updated: 2022/08/03 04:50:11 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{
    template <bool b, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> {typedef T t; };
}

#endif