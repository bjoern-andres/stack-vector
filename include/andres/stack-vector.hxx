#pragma once
#ifndef ANDRES_STACKVECTOR_HXX
#define ANDRES_STACKVECTOR_HXX

#include <cassert>
#include <array>
#include <stdexcept>

namespace andres {

/// STL-compliant container with flexible size, fixed maximum size and 
/// allocation on the stack. compatible with std::vector, not std::array.
template<class T, std::size_t N>
class StackVector {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename std::array<T, N>::iterator iterator;
    typedef typename std::array<T, N>::const_iterator const_iterator;
    typedef typename std::array<T, N>::reverse_iterator reverse_iterator;
    typedef typename std::array<T, N>::const_reverse_iterator const_reverse_iterator;

    StackVector(const size_type n = 0, const value_type& value = value_type())
        : size_(n), data_()
        { for(size_type j=0; j<size(); ++j) data_[j] = value; }
    void fill(const value_type& data)
        { std::fill_n(begin(), size(), data); }
    size_type size() const
        { return size_; }
    size_type max_size() const
        { return N; }
    bool empty() const
        { return size() == 0; }
    reference operator[](const size_type n)
        { assert(n < size()); return data_[n]; }
    const_reference operator[](const size_type n) const
        { assert(n < size()); return data_[n]; }
    reference at(const size_type n)
        { if(n < size()) return data_[n]; else throw std::out_of_range("andres::StackVector"); }
    const_reference at(const size_type n) const
        { if(n < size()) return data_[n]; else throw std::out_of_range("andres::StackVector"); }
    reference front()
        { return data_.front(); }
    const_reference front() const
        { return data_.front(); }
    reference back()
        { return N == 0 || size_ == 0 ? *end() : *(begin() + (size_ - 1)); }
    const_reference back() const
        { return N == 0 || size_ == 0 ? *end() : *(begin() + (size_ - 1)); }
    T* data()
        { return data_.data(); }
    const T* data() const
        { return data_.data(); }
    void resize(const size_type m, const value_type& v = value_type())
        {
            assert(m <= N);
            for(size_type j=size(); j<m; ++j) {
                data_[j] = v;
            }
            size_ = m;
        }
    void push_back(const value_type& v)
        { assert(size() < N); data_[size()] = v; ++size_; }

    iterator begin()
        { return data_.begin(); }
    const_iterator begin() const
        { return data_.begin(); }

    iterator end()
        { return data_.begin() + size(); }
    const_iterator end() const
        { return data_.begin() + size(); }

    reverse_iterator rbegin()
        { return reverse_iterator(data_.begin() + size()); }
    const_reverse_iterator rbegin() const
        { return reverse_iterator(data_.begin() + size()); }

    reverse_iterator rend()
        { return reverse_iterator(data_.begin()); }
    const_reverse_iterator rend() const
        { return const_reverse_iterator(data_.begin()); }

    const_iterator cbegin() const
        { return data_.cbegin(); }
    const_iterator cend() const
        { return data_.cbegin() + size(); }

    const_reverse_iterator crbegin() const
        { return const_reverse_iterator(data_.begin() + size()); }
    const_reverse_iterator crend() const
        { return const_reverse_iterator(data_.begin()); }

private:
    size_type size_;
    std::array<T, N> data_;
};

} // namespace andres

#endif // #ifndef ANDRES_STACKVECTOR_HXX
