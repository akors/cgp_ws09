
#ifndef CGP_MATRIX_HPP
#define CGP_MATRIX_HPP

#include <cstddef>
#include <valarray>
#include <iterator>
#include <iostream>
#include <limits>
#include <exception>

namespace cgp_matrix {

class MatrixError;

/** A generic Matirx class.
*
* Models:
* Assignable
*
* @tparam T Must model the Assignable concept
*/
template <typename T>
class matrix
{

public:
    class row_iterator;
    class col_iterator;

    // Fulfilling the Container concept requirements
    typedef T value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef std::size_t difference_type;
    typedef std::size_t size_type;
    typedef col_iterator iterator;
    typedef col_iterator const_iterator;

    class col_iterator
        : public std::iterator<
            std::input_iterator_tag, T, std::ptrdiff_t, pointer, reference
        >
    {
        friend class matrix<T>;

        matrix* base_ptr;
        size_type index;

        col_iterator(matrix* _base_ptr, size_type _index)
            : base_ptr(_base_ptr), index(_index)
        {}

        col_iterator(const matrix* _base_ptr, size_type _index)
            : base_ptr(const_cast<matrix*>(_base_ptr)), index(_index)
        {}

    public:
        // constructor
        col_iterator()
        {}

        // dereference operator
        reference operator * ()
        { return base_ptr->data_array. operator[] (index); }

#if 0
        // member access operator
        pointer operator -> ()
        { return &(base_ptr->operator[] (index)); }
#endif

        bool operator == (const col_iterator& other)
        { return index == other.index; }

        bool operator != (const col_iterator& other)
        { return index != other.index; }

        bool operator < (const col_iterator& other)
        { return index < other.index; }

        col_iterator operator ++ ()
        { return col_iterator(base_ptr, ++index); }

        col_iterator operator ++ (int)
        {
            return col_iterator(base_ptr, index++);
        }
    };

    class row_iterator
        : public std::iterator<
            std::input_iterator_tag, T, std::ptrdiff_t, pointer, reference
        >
    {
        friend class matrix<T>;

        matrix* base_ptr;
        size_type row, col;

        row_iterator(matrix* _base_ptr, size_type _row, size_type _col)
            : base_ptr(_base_ptr), row(_row), col(_col)
        {}

        row_iterator(const matrix* _base_ptr, size_type _row, size_type _col)
            : base_ptr(const_cast<matrix*> (_base_ptr)), row(_row), col(_col)
        {}

    public:
        // dereference operator
        reference operator * ()
        { return base_ptr->data_array. operator[] (row * base_ptr->columns() + col); }

#if 0
        // member access operator
        pointer operator -> ()
        { return &(base_ptr->operator[] (row * base_ptr->columns() + col)); }
#endif

        bool operator == (const row_iterator& other)
        {  return (row == other.row) && (col == other.col); }

        bool operator != (const row_iterator& other)
        { return !((row == other.row) && (col == other.col)); }

        bool operator < (const row_iterator& other)
        { return
            (row + col * base_ptr->rows()) <
                (other.row + other.col * other.base_ptr->rows() );
        }

        row_iterator operator ++ ()
        {
            // advance column if the row is the last row
            col += (row+1 == base_ptr->rows());

            // advance row, wrap around row size
            row = (row+1) % base_ptr->rows();

            return row_iterator(base_ptr, row, col);
        }

        row_iterator operator ++ (int)
        {
            size_type old_row = row, old_col = col;

            // advance column if the row is the last row
            col += (row+1 == base_ptr->rows());

            // advance row, wrap around row size
            row = (row+1) % base_ptr->rows();

            return row_iterator(base_ptr, old_row, old_col);
        }

    };

    typedef row_iterator const_row_iterator;
    typedef col_iterator const_col_iterator;


    class RowType
    {
        std::valarray<T>& base_arr;
        size_type columns, this_row;

        friend class matrix;

        RowType(std::valarray<T>& base_arr_,
                size_type columns_,
                size_type this_row_)
            : base_arr(base_arr_), columns(columns_),
            this_row(this_row_)
        {
        }

        RowType(const std::valarray<T>& base_arr_,
                size_type columns_,
                size_type this_row_)
            : base_arr(const_cast<std::valarray<T>&>(base_arr_)), columns(columns_),
            this_row(this_row_)
        {
        }

    public:
        reference operator [] (size_type col)
        {
            return base_arr[this_row * columns + col];
        }
    };

    matrix()
        : rows_(0), cols_(0)
    {}

    matrix(const matrix& other)
        :  data_array(other.data_array), rows_(other.rows_), cols_(other.cols_)
    {}

    matrix(size_type rows, size_type cols)
        : data_array(rows*cols), rows_(rows), cols_(cols)
    {}

    matrix(const T* val, size_type rows, size_type cols)
        : data_array(val, rows*cols), rows_(rows), cols_(cols)
    {}

    col_iterator col_begin() { return col_iterator(this, size_type(0u)); }
    col_iterator col_end() { return col_iterator(this, data_array.size()); }
    col_iterator col_begin(size_type row) { return col_iterator(this, row * rows_); }
    col_iterator col_end(size_type row) { return col_iterator(this, (row+1) * rows_); }

    const_col_iterator col_begin() const {return const_col_iterator(this, size_type(0u));}
    const_col_iterator col_end() const { return const_col_iterator(this, data_array.size()); }
    const_col_iterator col_begin(size_type row) const { return const_col_iterator(this, row * rows_); }
    const_col_iterator col_end(size_type row) const { return const_col_iterator(this, (row+1) * rows_); }


    row_iterator row_begin() { return row_iterator(this, 0, 0); }
    row_iterator row_end() { return row_iterator(this, 0, cols_); }
    row_iterator row_begin(size_type col) { return row_iterator(this, 0, col); }
    row_iterator row_end(size_type col) { return row_iterator(this, 0, col+1); }

    const_row_iterator row_begin() const { return const_row_iterator(this, 0, 0); }
    const_row_iterator row_end() const { return const_row_iterator(this, 0, cols_); }


    iterator begin() { return col_begin(); }
    iterator end() { return col_end(); }
    const_iterator begin() const { return col_begin(); }
    const_iterator end() const { return col_end(); }




    size_type size() const
    { return data_array.size(); }

    RowType operator [] (size_type row)
    { return RowType(data_array, cols_, row); }

    RowType operator [] (size_type row) const
    { return RowType(data_array, cols_, row); }


    size_type rows() const
    { return rows_; }

    size_type columns() const
    { return cols_; }

    bool empty() const
    { return !(rows_ * cols_); }

    size_type max_size() const
    { return std::numeric_limits<size_type>::max(); }

    // transpose matrix
    matrix<T> transpose() const
    {
        matrix<T> transposed(cols_, rows_);

        col_iterator in_it = this->col_begin();
        row_iterator row_it = transposed.row_begin();

        std::copy(in_it, this->col_end(), row_it);

        return transposed;
    }



private:

    std::valarray<T> data_array;
    size_type rows_, cols_;
};

// elementwise addition
template <typename T1, typename T2>
matrix<T1> operator + (const matrix<T1>& m1, const matrix<T2>& m2)
{
    // check matrix dimensions before proceeding
    if (!(m1.rows() == m2.rows() && m1.columns() == m2.columns()))
    {
        throw MatrixError ("Mismatched matrix dimensions");
    }

    // allocate resulting matrix
    matrix<T1> result(m1.rows(), m1.columns());

    // add all elements, put them into the resulting matrix
    std::transform(m1.begin(), m1.end(), m2.begin(), result.begin(),
        std::plus<T1>());

    return result;
}

// multiplication with constant
template <typename T1, typename T2>
matrix<T2> operator * (T1 c, const matrix<T2>& m)
{
    // allocate resulting matrix
    matrix<T2> result(m.rows(), m.columns());

    // add all elements, put them into the resulting matrix
    std::transform(m.begin(), m.end(), result.begin(),
        std::bind1st(std::multiplies<T2>(), c));

    return result;
}

// multiplication with constant
template <typename T1, typename T2>
inline
matrix<T2> operator * (const matrix<T1>& m, T2 c)
{
    // pass on to above definition
    return c * m;
}

// divide by constant
template <typename T1, typename T2>
matrix<T1> operator / (const matrix<T1>& m, T2 c)
{
    // allocate resulting matrix
    matrix<T1> result(m.rows(), m.columns());

    // add all elements, put them into the resulting matrix
    std::transform(m.begin(), m.end(), result.begin(),
        std::bind2nd(std::divides<T1>(), c));

    return result;
}

// matrix multiplication
template <typename T1, typename T2>
matrix<T1> operator * (const matrix<T1>& m1, const matrix<T2>& m2)
{
    // check matrix dimensions before proceeding
    if (m1.columns() != m2.rows())
    {
        throw MatrixError ("Mismatched matrix dimensions");
    }

    // allocate resulting matrix
    matrix<T2> result(m1.rows(), m2.columns());

    for (typename matrix<T1>::size_type out_row = 0;
        out_row < result.rows(); ++out_row)
    {
        for (typename matrix<T1>::size_type out_col=0;
            out_col < result.columns(); ++out_col)
        {
            result[out_row][out_col] = 0;
            for (typename matrix<T1>::size_type i = 0; i < m1.columns(); ++i)
                result[out_row][out_col] += m1[out_row][i] * m2[i][out_col];
        }
    }

    return result;
}


template <typename T>
std::ostream& operator << (std::ostream& os, cgp_matrix::matrix<T>& m)
{
    typename cgp_matrix::matrix<T>::size_type i, j;

    for (i = 0; i < m.rows(); ++i)
    {
        os<<"[";

        for (j = 0; j < m.columns(); ++j)
        {
            os<<' '<<m[i][j];
        }
        os<<" ]\n";
    }

    return os;
}

struct MatrixError : public std::exception
{
    MatrixError()
        : message("Unknown matrix error")
    { }

    MatrixError(const char* msg)
        : message(msg)
    {}

    const char* what() const throw()
    {
        return message.c_str();
    }

    virtual ~MatrixError() throw()
    {}

private:
    std::string message;
};

}

#endif // ifndef CGP_MATRIX_HPP
