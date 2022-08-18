#ifndef MAP_HPP
#define MAP_HPP

#include "../helpers/red_black_tree.hpp"
#include "../helpers/utilities.hpp"

namespace ft 
{

    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
    class map 
    {
        // Alias
        public:
                typedef Key             key_type;
                typedef T               mapped_type;
                typedef Compare         key_compare;
                typedef Allocator       allocator_type;
                typedef std::size_t     size_type;
                typedef std::ptrdiff_t  difference_type;
                typedef pair<const Key, T>  value_type;
                typedef const value_type& reference;
                typedef typename allocator_type::pointer pointer;
                typedef typename allocator_type::const_pointer const_pointer;
        
        private:
                class pair_compare
                {
                    key_compare _c;

                    public:
                            pair_compare(const key_compare & compare) : _c(compare) {}

                            bool operator()(const value_type& lhs, const value_type& rhs) const { return (_c(lhs.first, rhs.first)); }
                };
        
        public:
                typedef pair_compare value_compare;
                typedef red_black_tree<value_type, pair_compare, allocator_type> tree_type;
                typedef typename tree_type::iterator    iterator;
                typedef typename tree_type::const_iterator  const_iterator;
                typedef typename tree_type::reverse_iterator    reverse_iterator;
                typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

        private:
                allocator_type  _a;
                tree_type       _t;
                key_compare     _c;
        
        public:

                explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _a(alloc), _t(tree_type(comp,alloc)), _c(comp) {}

                template<class IT>
                map(IT first, IT last, const Compare& compare = Compare(), const Allocator& alloc = Allocator()) : _a(alloc), _t(first, last, compare, _a), _c(compare) {}

                // Simple methods
                allocator_type get_allocator() const { return (_t.get_allocator()); }
                size_type size() const { return (_t.size()); }
                size_type max_size() const { return (_t.max_size()); }
                bool empty() const { return (_t.empty()); }
                value_compare value_comp() const { return (_t.value_comp()); }
                key_compare key_comp() const { return (_c); }
                size_type count( const Key& key) const { return (_t.count(make_pair(key, mapped_type()))); }
                void swap(map & other)
                {
			        std::swap(this->_c, other._c);
			        _t.swap(other._t);
		        }

                //insert
                pair<iterator, bool> insert (const value_type& value) { return (_t.insert(value)); }
                iterator insert(iterator hint, const value_type& value) { return (_t.insert(hint, value)); }
                template<class IT>
                void insert(typename enable_if< !is_integral<IT>::value, IT>::type first, IT last) { _t.insert(first, last); }

                // Iterator
                iterator begin() { return (_t.begin()); }
                iterator end () { return (_t.end()); }
                
                reverse_iterator rbegin() { return (_t.rbegin()); }
                reverse_iterator rend() { return (_t.rend()); }
                

                iterator find(const Key& key) { return (_t.find(make_pair(key, mapped_type()))); }
                
                iterator lower_bound(const key_type& key) { return (_t.lower_bound(make_pair(key, mapped_type()))); }
                iterator upper_bound(const key_type& key) { return (_t.upper_bound(make_pair(key, mapped_type()))); }
                const_iterator lower_bound(const key_type& key) const { return (_t.lower_bound(make_pair(key, mapped_type()))); }
                const_iterator upper_bound(const key_type& key) const { return (_t.upper_bound(make_pair(key, mapped_type()))); }

                pair<iterator, iterator> equal_range(const key_type& key) { return (_t.equal_range(make_pair(key, mapped_type()))); }
                pair<const_iterator, const_iterator> equal_range(const key_type& key) const { return _t.equal_range(make_pair(key, mapped_type())); }
                
                //Access methods
                T& at(const Key &key)
                {
                    iterator res = _t.find(ft::make_pair(key, mapped_type()));
                    if (res == _t.end())
                        throw std::out_of_range("map::at: key not found");
                    return (res->second);
                }
                mapped_type& operator[](const key_type& key) { return (*((this->insert(ft::make_pair(key,mapped_type()))).first)).second; }

                //comparison operations
                template<class _K, class _T, class _C, class _A>
                friend bool operator==(const map<_K, _T, _C, _A>& lhs, const map<_K, _T, _C, _A>& rhs);

                template<class _K, class _T, class _C, class _A>
                friend bool operator<(const map<_K, _T, _C, _A>& lhs, const map<_K, _T, _C, _A>& rhs);

                //deletion
                void clear() { _t.clear(); }
                void erase(iterator pos) { _t.erase(pos); }
                void erase(iterator first, iterator last) { _t.erase(first, last); }
                size_type erase(const Key& key) { return (_t.erase(make_pair(key, mapped_type()))); }
    };

    template<class _K, class _T, class _C, class _A>
        bool operator==(const map<_K, _T, _C, _A>& lhs, const map<_K, _T, _C, _A>& rhs) { return (lhs._t == rhs._t); }

    template<class _K, class _T, class _C, class _A>
        bool operator!=(const map<_K, _T, _C, _A>& lhs, const map<_K, _T, _C, _A>& rhs) { return !(lhs == rhs); }

    template<class _K, class _T, class _C, class _A>
        bool operator<(const map<_K, _T, _C, _A>& lhs, const map<_K, _T, _C, _A>& rhs) { return (lhs._t < rhs._t); }

    template<class _K, class _T, class _C, class _A>
        bool operator>(const map<_K, _T, _C, _A>& lhs, const map<_K, _T, _C, _A>& rhs) { return (rhs < lhs); }

    template<class _K, class _T, class _C, class _A>
        bool operator<=(const map<_K, _T, _C, _A>& lhs, const map<_K, _T, _C, _A>& rhs) { return !(lhs > rhs); }

    template<class _K, class _T, class _C, class _A>
        bool operator>=(const map<_K, _T, _C, _A>& lhs, const map<_K, _T, _C, _A>& rhs) { return !(lhs < rhs); }

    template<class _K, class _T, class _C, class _A>
        void swap(const map<_K, _T, _C, _A>& lhs, const map<_K, _T, _C, _A>& rhs) { lhs.swap(rhs); }


}
#endif