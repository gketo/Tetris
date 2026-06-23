#pragma once

#include "Core/Lib/Matrix/MatrixStridedSpan.h"

#include <cstddef>
#include <stdexcept>

namespace Lib::Matrix {

    template <typename T>
    class MatrixColView
    {
    public:
        MatrixColView(T* p, size_t cols, size_t rows)
            : m_ptr{p}
            , m_rows{rows}
            , m_cols{cols}
        {}

        template <typename TPtr, typename TRef>
        class IteratorBase
        {
        public:
            IteratorBase(TPtr ptr, size_t rows, size_t cols)
            : m_ptr{ ptr }
            , m_rows{ rows }
            , m_cols{ cols }
            {}

            TRef operator*() const 
            { 
                return { m_ptr, m_rows, m_cols};
            }

            IteratorBase& operator++()
            {
                m_ptr++;
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
            size_t m_rows;
            size_t m_cols;
        };

        using Iterator = IteratorBase<T*, MatrixStridedSpan<T>>;
        using ConstIterator = IteratorBase<const T*, MatrixStridedSpan<const T>>;

        Iterator begin() { return Iterator(m_ptr, m_rows, m_cols); }
        Iterator end() { return Iterator(m_ptr + m_cols, m_rows, m_cols); }
        ConstIterator begin() const { return ConstIterator(m_ptr, m_rows, m_cols); };
        ConstIterator end() const { return ConstIterator(m_ptr + m_cols, m_rows, m_cols); };

        size_t size() const { return m_cols; }

        T& operator[](size_t i) { return m_ptr[i * m_cols]; }

        T& at(size_t i)
        {
            if (i >= m_rows)
            {
                throw std::out_of_range("[MatrixColView] at() index out of range");
            }

            return m_ptr[i * m_cols];
        }

    private:
        T* m_ptr;
        size_t m_rows;
        size_t m_cols;
    };
}