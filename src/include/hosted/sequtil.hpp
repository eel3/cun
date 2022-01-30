// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Sequence utility functions.

#ifndef CUN_SEQUTIL_HPP_INCLUDED
#define CUN_SEQUTIL_HPP_INCLUDED

// C++ standard library
#include <algorithm>

namespace cun {

namespace sequtil {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename SequenceT, typename PredicateT>
bool all_of(const SequenceT& seq, PredicateT pred)
{
    return std::all_of(seq.cbegin(), seq.cend(), pred);
}

template <typename SequenceT, typename PredicateT>
bool any_of(const SequenceT& seq, PredicateT pred)
{
    return std::any_of(seq.cbegin(), seq.cend(), pred);
}

template <typename SequenceT, typename PredicateT>
bool none_of(const SequenceT& seq, PredicateT pred)
{
    return std::none_of(seq.cbegin(), seq.cend(), pred);
}

template <typename SequenceT, typename ActionT>
ActionT for_each(SequenceT& seq, ActionT action)
{
    return std::for_each(seq.begin(), seq.end(), action);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename SequenceT, typename ValueT>
bool contain(const SequenceT& seq, const ValueT& value)
{
    return cun::sequtil::any_of(seq, [&value](const auto& v) { return v == value; });
}

template <typename SequenceT, typename ValueT>
bool not_contain(const SequenceT& seq, const ValueT& value)
{
    return cun::sequtil::none_of(seq, [&value](const auto& v) { return v == value; });
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename SequenceT, typename PredicateT, typename ActionT>
ActionT for_each_if(SequenceT& seq, PredicateT pred, ActionT action)
{
    (void) cun::sequtil::for_each(seq, [&pred, &action](auto& v) {
        if (pred(v)) {
            action(v);
        }
    });
    return action;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename SequenceT, typename PredicateT>
void trim_front_if(SequenceT& seq, PredicateT pred)
{
    auto p = std::find_if_not(seq.cbegin(), seq.cend(), pred);
    if (p == seq.cbegin()) {
        // no values to trim
    } else if (p == seq.cend()) {
        seq.clear();
    } else {
        seq.erase(seq.cbegin(), p);
    }
}

template <typename SequenceT, typename PredicateT>
void trim_back_if(SequenceT& seq, PredicateT pred)
{
    auto p = std::find_if_not(seq.crbegin(), seq.crend(), pred);
    if (p == seq.crbegin()) {
        // no values to trim
    } else if (p == seq.crend()) {
        seq.clear();
    } else {
        seq.erase(p.base(), seq.cend());
    }
}

template <typename SequenceT, typename PredicateT>
void trim_if(SequenceT& seq, PredicateT pred)
{
    cun::sequtil::trim_back_if(seq, pred);
    cun::sequtil::trim_front_if(seq, pred);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename SequenceT, typename ValueT>
void trim_front(SequenceT& seq, const ValueT& value)
{
    cun::sequtil::trim_front_if(seq, [&value](const auto& v) { return v == value; });
}

template <typename SequenceT, typename ValueT>
void trim_back(SequenceT& seq, const ValueT& value)
{
    cun::sequtil::trim_back_if(seq, [&value](const auto& v) { return v == value; });
}

template <typename SequenceT, typename ValueT>
void trim(SequenceT& seq, const ValueT& value)
{
    cun::sequtil::trim_if(seq, [&value](const auto& v) { return v == value; });
}

} // namespace sequtil

} // namespace cun

#endif // ndef CUN_SEQUTIL_HPP_INCLUDED
