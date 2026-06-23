#pragma once

#include "Core/Lib/Matrix/MatrixColView.h"
#include "Core/Types/Index2D.h"
#include "Core/Types/Size2D.h"
#include "Core/Lib/Matrix/MatrixRowView.h"
#include "Core/Lib/Matrix/MatrixStridedSpan.h"

#include <iostream> // debug
#include "Core/Utils/Logger.h" // debug todo remove

#include <algorithm>
#include <cstddef>
#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace Lib::Matrix {

    // Matrix
    template <typename TCell>
    class Matrix
    {
    public:
        Matrix() = default;

        Matrix(size_t rows, size_t cols)
        : m_size{ rows, cols }
        {
            m_data.resize(rows * cols);
        }

        Matrix(size_t rows, size_t cols, TCell fill)
        : m_size{ rows, cols }
        , m_data(rows * cols, fill)
        {}

        Matrix(size_t rows, size_t cols, const std::vector<TCell>& matrix)
        : m_size{ rows, cols }
        , m_data{ matrix }
        {
            if (m_data.size() != rows * cols)
            {
                throw std::invalid_argument("[Matrix] Constructor() size mismatch");
            }
        }

        const std::vector<TCell>& data() const  { return m_data; }
        bool empty() const                      { return m_data.empty(); }
        const Core::Type::Size2D& size() const  { return m_size; }
        size_t rows() const                     { return m_size.rows; }
        size_t cols() const                     { return m_size.cols; }

        auto operator<=>(const Matrix<TCell>&) const = default;

        MatrixRowView<const TCell> rowViews() const;
        MatrixRowView<TCell> rowViews();
        MatrixStridedSpan<const TCell> row(size_t r) const;
        MatrixStridedSpan<TCell> row(size_t r);

        MatrixColView<const TCell> colViews() const;
        MatrixColView<TCell> colViews();
        MatrixStridedSpan<const TCell> col(size_t c) const;
        MatrixStridedSpan<TCell> col(size_t c);

        void set(size_t r, size_t c, const TCell& cell);

        const TCell& operator()(size_t r, size_t c) const;
        TCell& operator()(size_t r, size_t c);

        const TCell& at(size_t r, size_t c) const;
        TCell& at(size_t r, size_t c);

        bool resize(size_t nrows, size_t ncols, const TCell& defaultCell = TCell());
        void reset(const TCell& fillCell = TCell());
        void clear();

        void insertRow(size_t at, const std::vector<TCell>& row);
        void insertRowFill(size_t at, const TCell& defaultCell = TCell());
        void insertCol(size_t at, const std::vector<TCell>& col);
        void insertColFill(size_t at, const TCell& defaultCell = TCell());

        void replaceRowRangeAt(size_t r, size_t c, std::span<const TCell> range);
        void replaceColRangeAt(size_t r, size_t c, std::span<const TCell> range);

        void appendRow(const std::vector<TCell>& row);
        void appendRowFill(const TCell& defaultCell = TCell());
        void appendCol(const std::vector<TCell>& col);
        void appendColFill(const TCell& defaultCell = TCell());

        std::vector<Core::Type::Index2D> find(const TCell& value) const;

        void transpose();
        void rotateLeft();
        void rotateRight();
       
        std::string toString() const;
        // debug
        std::string dbg_to_string() const;
        static void dbg_test();

    protected:
        Core::Type::Size2D m_size;
        std::vector<TCell> m_data;

        // linear index
        size_t lindex(size_t r, size_t c) const;
    };

    class BinaryMatrix : public Matrix<int>
    {
    public:
        BinaryMatrix(size_t rows, size_t cols, int fill = 0)
        : Matrix(rows, cols, static_cast<int>(fill != 0))
        {}

        BinaryMatrix(size_t rows, size_t cols, const std::vector<int>& matrix)
        : Matrix(rows, cols, [&matrix]{
            std::vector<int> bin;
            bin.reserve(matrix.size());
            for (int v : matrix) { bin.push_back(v != 0); }
            return bin;
        }())
        {}

        void setBit(size_t r, size_t c) { m_data[lindex(r, c)] = 1; }
        void unsetBit(size_t r, size_t c) { m_data[lindex(r, c)] = 0; }
    };

    template <typename TCell>
    size_t Matrix<TCell>::lindex(size_t r, size_t c) const
    {
        if (r >= m_size.rows || c >= m_size.cols)
        {
            throw std::out_of_range("[Matrix] lindex() index out of range");
        }
        return r * m_size.cols + c;
    }

    template <typename TCell>
    MatrixRowView<const TCell> Matrix<TCell>::rowViews() const
    {
        return MatrixRowView<const TCell>{
            m_data.data(),
            m_size.rows,
            m_size.cols
        };
    }

    template <typename TCell>
    MatrixRowView<TCell> Matrix<TCell>::rowViews()
    {
        return MatrixRowView<TCell>{
            m_data.data(),
            m_size.rows,
            m_size.cols
        };
    }

    template <typename TCell>
    MatrixColView<const TCell> Matrix<TCell>::colViews() const
    {
        return MatrixColView<TCell>{
            m_data.data(),
            m_size.cols,
            m_size.rows
        };
    }

    template <typename TCell>
    MatrixColView<TCell> Matrix<TCell>::colViews()
    {
        return MatrixColView<TCell>{
            m_data.data(),
            m_size.cols,
            m_size.rows
        };
    }

    template <typename TCell>
    MatrixStridedSpan<const TCell> Matrix<TCell>::row(size_t r) const
    {
        if (r >= m_size.rows)
        {
            throw std::out_of_range("[Matrix] row() index out of range");
        }

        return MatrixStridedSpan<const TCell>{
            m_data.data() + r * m_size.cols,
            m_size.cols,
            1
        };
    }

    template <typename TCell>
   MatrixStridedSpan<TCell> Matrix<TCell>::row(size_t r)
    {
        if (r >= m_size.rows)
        {
            throw std::out_of_range("[Matrix] row() index out of range");
        }

        return MatrixStridedSpan<TCell>{
            m_data.data() + r * m_size.cols,
            m_size.cols,
            1
        };
    }

    template <typename TCell>
    MatrixStridedSpan<const TCell> Matrix<TCell>::col(size_t c) const
    {
        if (c >= m_size.cols)
        {
            throw std::out_of_range("[Matrix] col() index out of range");
        }

        return MatrixStridedSpan<const TCell>{
            m_data.data() + c,
            m_size.rows,
            m_size.cols
        };
    }

    template <typename TCell>
    MatrixStridedSpan<TCell> Matrix<TCell>::col(size_t c)
    {
        if (c >= m_size.cols)
        {
            throw std::out_of_range("[Matrix] col() index out of range");
        }

        return MatrixStridedSpan<TCell>{
            m_data.data() + c,
            m_size.rows,
            m_size.cols
        };
    }

    template <typename TCell>
    void Matrix<TCell>::set(size_t r, size_t c, const TCell& cell)
    {
        if (r >= m_size.rows || c >= m_size.cols)
        {
            throw std::out_of_range("[Matrix] at() index out of range");
        }

        m_data[lindex(r, c)] = cell;
    }


    template <typename TCell>
    const TCell& Matrix<TCell>::operator()(size_t r, size_t c) const
    {
        return m_data[lindex(r, c)];
    }

    template <typename TCell>
    TCell& Matrix<TCell>::operator()(size_t r, size_t c)
    {
        return m_data[lindex(r, c)];;
    }

    template <typename TCell>
    const TCell& Matrix<TCell>::at(size_t r, size_t c) const
    {
        if (r >= m_size.rows || c >= m_size.cols)
        {
            throw std::out_of_range("[Matrix] at() index out of range");
        }
        return m_data[lindex(r, c)];
    }

    template <typename TCell>
    TCell& Matrix<TCell>::at(size_t r, size_t c)
    {
        if (r >= m_size.rows || c >= m_size.cols)
        {
            throw std::out_of_range("[Matrix] at() index out of range");
        }
        return m_data[lindex(r, c)];;
    }

    template <typename TCell>
    bool Matrix<TCell>::resize(size_t nrows, size_t ncols, const TCell& defaultCell)
    {
        // std::cout << "[Matrix] resizing to: " << static_cast<int>(nrows) << " rows, " << static_cast<int>(ncols) << "cols\n";
        if (nrows == m_size.rows && ncols == m_size.cols)
        {
            return false;
        }
        m_data.resize(nrows * ncols, defaultCell);
        m_size.rows = nrows;
        m_size.cols = ncols;
        return true;
    }

    template <typename TCell>
    void Matrix<TCell>::reset(const TCell& fillCell)
    {
        std::fill(m_data.begin(), m_data.end(), fillCell);
    }

    template <typename TCell>
    void Matrix<TCell>::clear()
    {
        m_data.clear();
    }

    template <typename TCell>
    void Matrix<TCell>::insertRow(size_t at, const std::vector<TCell>& row)
    {
        if (at > m_size.rows)
        {
            throw std::out_of_range("[Matrix] insertRow() index out of range");
        }

        if (row.size() != m_size.cols)
        {
            throw std::runtime_error("[Matrix] insertRow() row size mismatch");
        }

        m_data.insert(m_data.begin() + at * m_size.cols, row.begin(), row.end());
        m_size.rows++;
    }

    template <typename TCell>
    void Matrix<TCell>::insertRowFill(size_t at, const TCell& defaultCell)
    {
        if (at > m_size.rows)
        {
            throw std::out_of_range("[Matrix] insertRowFill() index out of range");
        }

        m_data.insert(m_data.begin() + at * m_size.cols, m_size.cols, defaultCell);
        m_size.rows++;
    }

    template <typename TCell>
    void Matrix<TCell>::insertCol(size_t at, const std::vector<TCell>& col)
    {
        if (at > m_size.cols)
        {
            throw std::out_of_range("[Matrix] insertCol() index out of range");
        }

        if (col.size() != m_size.rows)
        {
            throw std::runtime_error("[Matrix] insertCol() col size mismatch");
        }
        
        for (size_t r = 0; r < m_size.rows; ++r)
        {
            size_t pos = r * (m_size.cols + 1) + at;
            m_data.insert(m_data.begin() + pos, col[r]);
        }

        m_size.cols++;
    }

    template <typename TCell>
    void Matrix<TCell>::insertColFill(size_t at, const TCell& defaultCell)
    {
        if (at > m_size.cols)
        {
            throw std::out_of_range("[Matrix] insertColFill() index out of range");
        }

        for (size_t r = 0; r < m_size.rows; ++r)
        {
            size_t pos = r * (m_size.cols + 1) + at;
            m_data.insert(m_data.begin() + pos, defaultCell);
        }

        m_size.cols++;
    }

    template <typename TCell>
    void Matrix<TCell>::replaceRowRangeAt(size_t r, size_t c, std::span<const TCell> range)
    {
        if (r >= m_size.rows || c >= m_size.cols)
        {
            throw std::out_of_range("[Matrix] replaceRowRangeAt() index out of range");
        }

        if (c + range.size() > m_size.cols)
        {
            throw std::out_of_range("[Matrix] replaceRowRangeAt() range doesn't fit");
        }

        for (size_t col = c; col < c + range.size(); ++col)
        {
            at(r, col) = range[col - c] ;
        }
    }

    template <typename TCell>
    void Matrix<TCell>::replaceColRangeAt(size_t r, size_t c, std::span<const TCell> range)
    {
        if (r >= m_size.rows || c >= m_size.cols)
        {
            throw std::out_of_range("[Matrix] replaceColRangeAt() index out of range");
        }

        if (c + range.size() > m_size.cols)
        {
            throw std::out_of_range("[Matrix] replaceColRangeAt() range doesn't fit");
        }

        for (size_t row = r; row < r + range.size(); ++row)
        {
            at(row, c) = range[row - r] ;
        }
    }

    template <typename TCell>
    void Matrix<TCell>::appendRow(const std::vector<TCell>& row)
    {
        m_data.insert(m_data.end(), row.begin(), row.end());
    }

    template <typename TCell>
    void Matrix<TCell>::appendRowFill(const TCell& defaultCell)
    {
        resize(m_size.rows + 1, m_size.cols, defaultCell);
    }

    template <typename TCell>
    void Matrix<TCell>::appendCol(const std::vector<TCell>& col)
    {
        if (col.size() != m_size.rows)
        {
            throw std::runtime_error("[Matrix] appendCol() col size mismatch");
        }
        
        for (size_t r = 0; r < m_size.rows; ++r)
        {
            auto index = m_data.begin() + r * (m_size.cols + 1) + m_size.cols;
            m_data.insert(index, col[r]);
        }

        m_size.cols++;
    }

    template <typename TCell>
    void  Matrix<TCell>::appendColFill(const TCell& defaultCell)
    {
        for (size_t r = 0; r < m_size.rows; ++r)
        {
            auto index = m_data.begin() + r * (m_size.cols + 1) + m_size.cols;
            m_data.insert(index, defaultCell);
        }

        m_size.cols++;
    }

    template <typename TCell>
    std::vector<Core::Type::Index2D> Matrix<TCell>::find(const TCell& value) const
    {
        std::vector<Core::Type::Index2D> matches;
        if (m_data.empty())
        {
            return matches;
        }

        for (size_t it = 0; it < m_data.size(); ++it)
        {
            if (m_data[it] == value)
            {
                Core::Type::Index2D mcoords;
                mcoords.row = it/m_size.rows;
                mcoords.col = it%m_size.rows;
                matches.emplace_back(mcoords);
            }
        }
        return matches;
    }

    template <typename TCell>
    void Matrix<TCell>::transpose()
    {
        // transpose : https://en.wikipedia.org/wiki/In-place_matrix_transposition
        if (m_size.rows == m_size.cols)
        {
            for (size_t n = 0; n < m_size.rows - 1; ++n)
            {
                for (size_t m = n + 1; m < m_size.cols; ++m)
                {
                    std::swap((*this)(n, m), (*this)(m, n));
                }
            }
        }
        else
        {
            Matrix<TCell> temp(m_size.cols, m_size.rows);
            for (size_t r = 0; r< m_size.rows; ++r)
            {
                for (size_t c = 0; c < m_size.cols; ++c)
                {
                    temp(c, r) = (*this)(r, c);
                }
            }
            *this = temp;
        }
    }

    template <typename TCell>
    void Matrix<TCell>::rotateLeft()
    {
        // transpose
        transpose();

        // reverse each col
        for (size_t r = 0; r< m_size.rows/2; ++r)
        {
            for (size_t c = 0; c < m_size.cols; ++c)
            {
                std::swap((*this)(r, c), (*this)(m_size.rows - 1 - r, c));
            }
        }
    }

    template <typename TCell>
    void Matrix<TCell>::rotateRight()
    {
        // transpose
        transpose();

        // reverse each row
        for (size_t r = 0; r< m_size.rows; ++r)
        {
            std::reverse(m_data.begin() + r * m_size.cols, m_data.begin() + (r + 1) * m_size.cols);
        }
    }

    template <typename TCell>
    std::string Matrix<TCell>::toString() const
    {
        std::ostringstream os;
        if (m_data.empty())
        {
            return {};
        }

        for (const auto& cell : m_data)
        {
            os << cell;
        }

        return os.str();
    }

    // debug dbg
    template <typename TCell>
    std::string Matrix<TCell>::dbg_to_string() const
    {
        // maybe todo do for other than int but should be tested with int anyway
        static_assert(std::is_same_v<TCell, int>);

        std::string matrixStr;
        if (m_data.empty())
        {
            return matrixStr;
        }

        matrixStr.reserve(m_data.size() * 4);

        // padding
        const auto longest = std::to_string(*std::max_element(m_data.begin(), m_data.end())).size();

        for (size_t r = 0; r< m_size.rows; ++r)
        {
            for (size_t c = 0; c < m_size.cols; ++c)
            {
                auto cellStr = std::to_string((*this)(r, c));
                auto padding = longest - cellStr.size();
                matrixStr += std::string(padding, ' ');
                matrixStr += cellStr;
                matrixStr += ' ';
            }
            matrixStr += '\n';
        }

        return matrixStr;
    }

    template <typename TCell>
    void Matrix<TCell>::dbg_test()
        {
            size_t nrows = 4, ncols = 4;
            auto matrix = Matrix<int>(nrows, ncols, 0);

            int val = 1;
            for (size_t r = 0; r < matrix.size().rows; ++r)
            {
                for (size_t c = 0; c < matrix.size().cols; ++c)
                {
                    matrix(r, c) = val;
                    val++;
                }
            }

            std::cout << "Base:\n";
            std::cout << matrix.toString() << "\n";

            auto transpose = matrix;
            transpose.transpose();
            std::cout << "transpose\n";
            std::cout << transpose.toString() << "\n";

            auto rotate = matrix;
            rotate.rotateRight();
            std::cout << "rotate right\n";
            std::cout << rotate.toString() << "\n";
            rotate.rotateLeft();
            std::cout << "rotate left\n";
            std::cout << rotate.toString() << "\n";

            std::cout << "Base:\n";
            std::cout << matrix.toString() << "\n";

            std::cout << "row(1): [ ";
            for (const auto& cell : matrix.row(1))
            {
                std::cout << cell << " ";
            }
            std::cout << "]\n";

            std::cout << "col(1): ";
            for (const auto& cell : matrix.col(1))
            {
                std::cout << cell << "\n        ";
            }
            std::cout << "\n";

            std::cout << "Base:\n";
            std::cout << matrix.toString() << "\n";

            std::cout << "for each row():\n";
            for (const auto& row : matrix.rowViews())
            {
                std::cout << "[ ";
                for (const auto& cell : row)
                {
                    std::cout << cell << " ";
                }
                std::cout << " ]\n";
            }
            std::cout << "\n";

            std::cout << "Base:\n";
            std::cout << matrix.toString() << "\n";

            std::cout << "for each col():\n";
            for (const auto& col : matrix.colViews())
            {
                for (const auto& cell : col)
                {
                    std::cout << cell << "\n";
                }
                std::cout << "-\n";
            }

            std::cout << "Base:\n";
            std::cout << matrix.toString() << "\n";

            std::cout << "insertRow() 111 at 2:\n";
            matrix.insertRow(2, std::vector<int>(matrix.cols(), 111));
            std::cout << matrix.toString() << "\n";

            std::cout << "insertRowFill() 222 at 2:\n";
            matrix.insertRowFill(2, 222);
            std::cout << matrix.toString() << "\n";

            std::cout << "insertCol() 555 at 2:\n";
            matrix.insertCol(2, std::vector<int>(matrix.rows(), 555));
            std::cout << matrix.toString() << "\n";

            std::cout << "insertColFill() 666 at 2:\n";
            matrix.insertColFill(2, 666);
            std::cout << matrix.toString() << "\n";

            std::cout << "appendRow() 333:\n";
            matrix.appendRow(std::vector<int>(matrix.cols(), 333));
            std::cout << matrix.toString() << "\n";

            std::cout << "appendRowFill(444) 444:\n";
            matrix.appendRowFill(444);
            std::cout << matrix.toString() << "\n";

            std::cout << "appendCol() 777:\n";
            matrix.appendCol(std::vector<int>(matrix.rows(), 777));
            std::cout << matrix.toString() << "\n";

            std::cout << "appendColFill() 888:\n";
            matrix.appendColFill(888);
            std::cout << matrix.toString() << "\n";
        }
}





// struct Iterator
// {
//     using iterator_category = std::random_access_iterator
//     using difference_type   = std::ptrdiff_t;
//     using value_type        = TCell;
//     using pointer           = TCell*;  // or also value_type*
//     using reference         = TCell&;  // or also value_type&

//     Iterator(pointer ptr) : m_ptr(ptr) {}

//     // random access iterator needs to implement this
//     reference   operator*() const                   { return *m_ptr; }
//     reference   operator[](difference_type n) const { return *(m_ptr + n); }
//     pointer     operator->()const                   { return m_ptr; }

//     Iterator&   operator++()        { ++m_ptr; return *this; }
//     Iterator    operator++(int)     { Iterator tmp = *this; ++(*this); return tmp; }
//     Iterator&   operator--()        { --m_ptr; return *this; }
//     Iterator    operator--(int)     { Iterator tmp = *this; --(*this); return tmp; }

//     friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
//     friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }

//     friend Iterator operator+(difference_type n, const Iterator& it)    { return it + n; }
//     Iterator        operator+(difference_type n) const                  { return Iterator(m_ptr + n); }
//     Iterator        operator-(difference_type n) const                  { return Iterator(m_ptr - n); }

//     Iterator&   operator+=(difference_type n) { m_ptr += n; return *this; }
//     Iterator&   operator-=(difference_type n) { m_ptr -= n; return *this; }

//     difference_type operator-(const Iterator& other) const { return m_ptr - other.m_ptr; }


//     bool operator<(const Iterator& other) const { return m_ptr < other.m_ptr; }
//     bool operator<=(const Iterator& other) const { return m_ptr <= other.m_ptr; }
//     bool operator>(const Iterator& other) const { return m_ptr > other.m_ptr; }
//     bool operator>=(const Iterator& other) const { return m_ptr >= other.m_ptr; }

// private:
//     pointer m_ptr;
// };

// Iterator begin()    { return Iterator(&m_data.data()); }
// Iterator end()      { return Iterator(&m_data.data() + m_data.size()); }