#ifndef SPLIT_H_
#define SPLIT_H_

namespace localstd
{
	/// \brief splits a list based on an operation
	/// \ingroup non_mutating_algorithms
	/// \tparam InputIt
	/// \tparam OutputIt
	/// \tparam UnaryOperation
	/// \param start an input iterator
	/// \param end an input iterator
	/// \param out_first an output iterator
	/// \param unary_op a unary operator
	/// \return an output iterator equal to \p out_first
	///
	/// Applies the operator to determine when to split elements within
	/// 	the input range and assigns the result to an output sequence
	/// \p unary_op must not alter its arguments
	template <class InputIt, class OutputIt, class UnaryOperation>
	constexpr OutputIt split(InputIt start, InputIt end, OutputIt out_first, UnaryOperation unary_op)
	{
		auto begin = start;
		while (start != end)
		{
			if (unary_op(*start))
			{
				*out_first++ = {begin, start};
				begin = std::next(start, 1);
			}
			std::advance(start, 1);
		}

		*out_first++ = {begin, end};

		return out_first;
	}
}// namespace localstd

#endif
