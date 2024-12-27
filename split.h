#ifndef SPLIT_H_
#define SPLIT_H_

#include <iterator>

namespace localstd
{
    /// @brief splits a list based on an operation
    /// @tparam InputIt
    /// @tparam OutputIt
    /// @tparam UnaryOperation
    /// @param first an input iterator
    /// @param last an input iterator
    /// @param out_first an output iterator
    /// @param unary_op a unary operator
    /// @return an output iterator equal to \p out_first
    ///
    /// Applies the operator to determine when to split elements within
    /// 	the input range and assigns the result to an output sequence
    /// @p unary_op must not alter its arguments
    template<class InputIt, class OutputIt, class UnaryOperation>
    constexpr OutputIt
    split(InputIt first, InputIt last, OutputIt out_first, UnaryOperation unary_op) {
        auto begin = first;
        while (first != last) {
            if (unary_op(*first)) {
                *out_first++ = {begin, first};
                begin = std::next(first, 1);
            }
            std::advance(first, 1);
        }

        *out_first++ = {begin, last};

        return out_first;
	}
}// namespace localstd

#endif
