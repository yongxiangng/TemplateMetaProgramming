//
// Created by ngyongxiang on 5/05/23.
//

#ifndef TEMPLATEMETAPROGRAMMING_SORT_H
#define TEMPLATEMETAPROGRAMMING_SORT_H

#include <cstddef>

template <int... Vals>
struct Vec;

template <typename Vec1, typename Vec2>
struct Concat;

template <int... T1, int... T2>
struct Concat<Vec<T1...>, Vec<T2...>>
{
    using Type = Vec<T1..., T2...>;
};

template <bool Cond, typename True, typename False>
struct IfElseThen
{
    using Type = True;
};

template <typename True, typename False>
struct IfElseThen<false, True, False>
{
    using Type = False;
};

template <typename In, size_t l, size_t r, typename OutVec=Vec<>, size_t idx=0>
struct Split;

template <size_t l, size_t r, typename OutVec, size_t idx>
struct Split<Vec<>, l, r, OutVec, idx>
{
    using Type = OutVec;
};

template <int Head, int... Tail, size_t l, size_t r, int... outs, size_t idx>
struct Split<Vec<Head, Tail...>, l, r, Vec<outs...>, idx>
{
    using Type = IfElseThen<(l <= idx && idx < r),
        typename Split<Vec<Tail...>, l, r, Vec<outs..., Head>, idx + 1>::Type,
        typename Split<Vec<Tail...>, l, r, Vec<outs...>, idx + 1>::Type>::Type;
};

template <typename Vec1, typename Vec2, typename OutputVec=Vec<>>
struct Merge;

template <int a, int... i1s, int b, int... i2s, int... outs>
struct Merge<Vec<a, i1s...>, Vec<b, i2s...>, Vec<outs...>>
{
    using Type = IfElseThen<(a < b),
        typename Merge<Vec<i1s...>, Vec<b, i2s...>, Vec<outs..., a>>::Type,
        typename Merge<Vec<a, i1s...>, Vec<i2s...>, Vec<outs..., b>>::Type>::Type;
};

template <int... is, int... outs>
struct Merge<Vec<>, Vec<is...>, Vec<outs...>>
{
    using Type = Vec<outs..., is...>;
};

template <int... is, int... outs>
struct Merge<Vec<is...>, Vec<>, Vec<outs...>>
{
    using Type = Vec<outs..., is...>;
};

template <int... outs>
struct Merge<Vec<>, Vec<>, Vec<outs...>>
{
    using Type = Vec<outs...>;
};

template <typename In>
struct Sort;

template <int val>
struct Sort<Vec<val>>
{
    using Type = Vec<val>;
};

template <>
struct Sort<Vec<>>
{
    using Type = Vec<>;
};

template <int... vals>
struct Sort<Vec<vals...>>
{
    static inline constexpr size_t N = sizeof...(vals);

    using LeftVec = Split<Vec<vals...>, 0, N/2>::Type;
    using RightVec = Split<Vec<vals...>, N/2, N>::Type;

    using Left = Sort<LeftVec>::Type;
    using Right = Sort<RightVec>::Type;

    using Type = Merge<Left, Right>::Type;
};

static_assert(std::is_same_v<Merge<Vec<1, 3, 5>, Vec<2, 4>>::Type, Vec<1, 2, 3, 4, 5>>);
static_assert(std::is_same_v<Merge<Vec<>, Vec<>>::Type, Vec<>>);

static_assert(std::is_same_v<Split<Vec<1, 2, 3, 4, 5>, 0, 0>::Type, Vec<>>);
static_assert(std::is_same_v<Split<Vec<1, 2, 3, 4, 5>, 0, 3>::Type, Vec<1, 2, 3>>);
static_assert(std::is_same_v<Split<Vec<1, 2, 3, 4, 5>, 2, 3>::Type, Vec<3>>);
static_assert(std::is_same_v<Split<Vec<>, 2, 3>::Type, Vec<>>);

static_assert(std::is_same_v<Sort<Vec<1, 4>>::Type, Vec<1, 4>>);
static_assert(std::is_same_v<Sort<Vec<3, 1, 4, 1, 5, 9, 2, 6>>::Type, Vec<1, 1, 2, 3, 4, 5, 6, 9>>);
static_assert(std::is_same_v<Sort<Vec<-3, -1, -4, -1, -5, -9, -2, -6>>::Type, Vec<-9, -6, -5, -4, -3, -2, -1, -1>>);
static_assert(std::is_same_v<Sort<Vec<>>::Type, Vec<>>);
static_assert(std::is_same_v<Sort<Vec<1>>::Type, Vec<1>>);

#endif //TEMPLATEMETAPROGRAMMING_SORT_H
