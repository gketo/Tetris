#pragma once

// ==================== Includes ====================
#include "MatrixStridedSpan.h"

// ==================== Includes ====================
#include <cstddef>
#include <stdexcept>

namespace Lib::Matrix {

    template <typename T>
    class MatrixRowView
    {
    public:
        MatrixRowView(T* p, size_t rows, size_t cols)
        : m_ptr{ p }
        , m_rows{ rows }
        , m_cols{ cols }
        {}

        template <typename TPtr, typename TRef>
        class IteratorBase
        {
        public:
            IteratorBase(TPtr ptr, size_t cols)
            : m_ptr{ ptr }
            , m_cols{ cols }
            {}

            TRef operator*() const 
            { 
                return { m_ptr, m_cols, 1 };
            }

            IteratorBase& operator++()
            {
                m_ptr += m_cols;
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
            size_t m_cols;
        };

        using Iterator = IteratorBase<T*, MatrixStridedSpan<T>>;
        using ConstIterator = IteratorBase<const T*, MatrixStridedSpan<const T>>;

        Iterator begin() { return Iterator(m_ptr, m_cols); }
        Iterator end() { return Iterator(m_ptr + m_rows * m_cols, m_cols); }
        ConstIterator begin() const { return ConstIterator(m_ptr, m_cols); };
        ConstIterator end() const { return ConstIterator(m_ptr + m_rows * m_cols, m_cols); };

        size_t size() const { return m_rows; }

        T& operator[](size_t i) { return m_ptr[i * m_cols]; }

        T& at(size_t i)
        {
            if (i >= m_rows)
            {
                throw std::out_of_range("[MatrixRowView] at() index out of range");
            }

            return m_ptr[i * m_cols];
        }

    private:
        T* m_ptr;
        size_t m_rows;
        size_t m_cols;
    };
}