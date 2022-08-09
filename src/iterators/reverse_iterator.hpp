#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "./iterator_traits.hpp"

namespace ft{

    template <class Iterator>
    class reverse_iterator
    {
        public:
                typedef Iterator                                                iterator_type;
                typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
                typedef typename iterator_traits<Iterator>::value_type          value_type;
                typedef typename iterator_traits<Iterator>::difference_type     difference_type;
                typedef typename iterator_traits<Iterator>::pointer             pointer;
                typedef typename iterator_traits<Iterator>::reference           reference;

        private:
                iterator_type _i;
        
        public:
                //base
                
                reverse_iterator() : _i() {}
                explicit reverse_iterator (iterator_type i) : _i(i) {}
                template <class It>
                reverse_iterator (const reverse_iterator<It>& rev_it){ _i = rev_it._i; }
                iterator_type base() const { return (_i); }
                
                //operators
                reference operator*() const 
                {
                    iterator_type tmp = _i;
                    return(*--tmp);
                }

                reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_i - n)); }
                reverse_iterator& operator++() 
                { 
                    --_i;
                    return (*this);
                }
                reverse_iterator operator++(int)
                {
                    reverse_iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }
                reverse_iterator& operator+= (difference_type n)
                {
                    _i -= n;
                    return (*this);
                }
                reverse_iterator operator- (difference_type n) const { return (reverse_iterator(_i + n)); }
                reverse_iterator& operator--()
                {
                    ++_i;
                    return (*this);
                }
                reverse_iterator operator--(int)
                {
                    reverse_iterator tmp = *this;
                    --(*this);
                    return tmp;
                }
                reverse_iterator& operator -=(difference_type n)
                {
                    _i += n;
                    return (*this);
                }
                
                pointer operator->() const { return &(operator*()); }
                reference operator[] (difference_type n) const { return (_i[-n-1]); }
    };
    
    template<class Iterator>
        bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){ return (lhs.base() == rhs.base()); }
    template<class Iterator>
        bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){ return (lhs.base() != rhs.base()); }
    template<class Iterator>
        typename reverse_iterator<Iterator>::difference_type operator-(reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }
    template<class Iterator>
        reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) { return (it + n); }

    template<class Iterator>
        bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){ return (lhs.base() > rhs.base());}
    template<class Iterator>
        bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){ return (lhs.base() >= rhs.base());}
    template<class Iterator>
        bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){ return (lhs.base() < rhs.base());}
    template<class Iterator>
        bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs){ return (lhs.base() <= rhs.base());}
        
}

#endif
