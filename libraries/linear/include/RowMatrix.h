////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  [projectName]
//  File:     RowMatrix.h (linear)
//  Authors:  Ofer Dekel
//
//  [copyright]
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "RowMatrix.h"
#include "IMatrix.h"

// stl
#include <vector>
#include <iostream>
#include <random>

namespace linear
{
    /// <summary> Base class for RowMatrix. </summary>
    ///
    /// <typeparam name="DataVectorType"> Type of the data vector type. </typeparam>
    template<typename DataVectorType>
    class RowMatrix : public IMatrix
    {
    public:

        using IMatrix::Gemv;
        using IMatrix::Gevm;

        /// <summary> A read-only forward iterator of rows in the RowMatrix. </summary>
        class Iterator
        {
        public:

            /// <summary> Copy constructor. </summary>
            Iterator(const Iterator&) = default;

            /// <summary> Move constructor. </summary>
            Iterator(Iterator&&) = default;

            /// <summary> Returns true if the iterator is currently pointing to a valid iterate. </summary>
            ///
            /// <returns> true if valid, false if not. </returns>
            bool IsValid() const;

            /// <summary>
            /// Returns the number of iterates left in this iterator, including the current one.
            /// </summary>
            ///
            /// <returns> The total number of iterates left. </returns>
            uint64 NumIteratesLeft() const;

            /// <summary> Proceeds to the Next row. </summary>
            void Next();

            /// <summary> Returns a const reference to the current row. </summary>
            ///
            /// <returns> A const reference to the current row; </returns>
            const DataVectorType& Get() const;

        private:

            // private ctor, can only be called from RowMatrix class
            Iterator(const RowMatrix& table, uint64 firstRow, uint64 maxRow);
            friend RowMatrix<DataVectorType>;

            // members
            const RowMatrix& _table;
            uint64 _row;
            uint64 _maxRow;
        };

        /// <summary> The type of each row. </summary>
        using RowType = DataVectorType;

        /// <summary> Default constructor. </summary>
        RowMatrix() = default;

        /// <summary> Move constructor </summary>
        RowMatrix(RowMatrix<DataVectorType>&&) = default;

        /// <summary> Deleted copy constructor. </summary>
        RowMatrix(const RowMatrix<DataVectorType>&) = delete;

        /// <summary> Default move assignment operator. </summary>
        ///
        /// <param name="other"> [in,out] The other vector. </param>
        RowMatrix<DataVectorType>& operator=(RowMatrix<DataVectorType>&&) = default;

        /// <summary> Deleted asignment operator. </summary>
        RowMatrix<DataVectorType>& operator=(const RowMatrix<DataVectorType>&) = delete;

        /// <summary> Returns the number of rows in the matrix. </summary>
        ///
        /// <returns> The number of rows. </returns>
        virtual uint64 NumRows() const override;

        /// <summary> Returns the number of columns in the matrix. </summary>
        ///
        /// <returns> The number of columns. </returns>
        virtual uint64 NumColumns() const override;

        /// <summary> Returns a reference to a row. </summary>
        ///
        /// <param name="index"> Zero-based index of the row. </param>
        ///
        /// <returns> Refence to the specified row. </returns>
        const RowType& GetRow(uint64 index) const;

        /// <summary> Returns an iterator that traverses the rows. </summary>
        ///
        /// <param name="firstRow"> Zero-based index of the first row to iterate over. </param>
        /// <param name="size"> The number of rows to iterate over, a value of zero means all rows. </param>
        ///
        /// <returns> The iterator. </returns>
        Iterator GetIterator(uint64 firstRow = 0, uint64 numRows = 0) const;

        /// <summary> Pushes a row into the bottom of the matrix. </summary>
        ///
        /// <param name="row"> [in,out] The row. </param>
        void PushBackRow(DataVectorType&& row);

        /// <summary>
        /// Constructs a new row at the bottom of the matrix with given constructor arguments.
        /// </summary>
        ///
        /// <typeparam name="Args"> Types for the row constructor. </typeparam>
        /// <param name="args"> Variables for the row constructor. </param>
        template<typename... Args >
        void EmplaceBackRow(Args&&... args);

        /// <summary> Performs a general matrix-vector product: y = alpha * M * x + beta * y. </summary>
        ///
        /// <param name="p_x"> The x vector. </param>
        /// <param name="p_y"> [in,out] The y vector. </param>
        /// <param name="alpha"> The alpha parameter. </param>
        /// <param name="beta"> The beta parameter. </param>
        virtual void Gemv(const double* p_x, double* p_y, double alpha = 1.0, double beta = 0.0) const override;

        /// <summary> Performs a general vector-matrix product: y = alpha * x * M + beta * y. </summary>
        ///
        /// <param name="p_x"> The x vector. </param>
        /// <param name="p_y"> [in,out] The y vector. </param>
        /// <param name="alpha"> The alpha parameter. </param>
        /// <param name="beta"> The beta parameter. </param>
        virtual void Gevm(const double* p_x, double* p_y, double alpha = 1.0, double beta = 0.0) const override;

        /// <summary> Human readable printout to an output stream. </summary>
        ///
        /// <param name="os"> [in,out] Stream to write data to. </param>
        virtual void Print(std::ostream& os) const override;

    private:
        std::vector<DataVectorType> _rows;
        uint64 _num_columns = 0;
    };
}

#include "../tcc/RowMatrix.tcc"
