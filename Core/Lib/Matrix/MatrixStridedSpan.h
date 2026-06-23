#pragma once

#include <cstddef>
#include <stdexcept>

namespace Lib::Matrix {

    template <typename T>
    class MatrixStridedSpan
    {
    public:
        MatrixStridedSpan(T* p, size_t c, size_t s)
        : m_ptr{ p }
        , m_count{ c }
        , m_stride{ s }
        {}

        template <typename TPtr, typename TRef>
        class IteratorBase
        {
        public:
            IteratorBase(TPtr ptr, size_t stride)
            : m_ptr{ ptr }
            , m_stride{ stride }
            {}

            TRef operator*() const { return *m_ptr; }

            IteratorBase& operator++()
            {
                m_ptr += m_stride;
                return *this;
            }

            IteratorBase operator++(int)
            {
                IteratorBase tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator!=(const IteratorBase& other) const { return m_ptr != other.m_ptr; }

        private:
            TPtr m_ptr;
            size_t m_stride;
        };

        using Iterator = IteratorBase<T*, T&>;
        using ConstIterator = IteratorBase<const T*, const T&>;

        Iterator begin() { return Iterator(m_ptr, m_stride); }
        Iterator end() { return Iterator(m_ptr + m_count * m_stride, m_stride); }
        ConstIterator begin() const { return ConstIterator(m_ptr, m_stride); };
        ConstIterator end() const { return ConstIterator(m_ptr + m_count * m_stride, m_stride); };

        size_t size() const { return m_count; }

        const T& operator[](size_t i) const { return m_ptr[i * m_stride]; }
        T& operator[](size_t i) { return m_ptr[i * m_stride]; }

        T& at(size_t i)
        {
            if (i >= m_count)
            {
                throw std::out_of_range("[MatrixStridedSpan] at() index out of range");
            }

            return m_ptr[i * m_stride];
        }
        
    private:
        T* m_ptr;
        size_t m_count;
        size_t m_stride;
    };
}