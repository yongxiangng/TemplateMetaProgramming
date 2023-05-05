//
// Created by ngyongxiang on 6/05/23.
//

#ifndef TEMPLATEMETAPROGRAMMING_PRIME_H
#define TEMPLATEMETAPROGRAMMING_PRIME_H

namespace Prime_Prime
{

struct TrueType
{
    static inline constexpr bool Value = true;
};

struct FalseType
{
    static inline constexpr bool Value = false;
};

template <bool Cond, typename TrueRes, typename FalseRes>
struct IfElseThen
{
    using Type = TrueRes;
};

template <typename TrueRes, typename FalseRes>
struct IfElseThen<false, TrueRes, FalseRes>
{
    using Type = FalseRes;
};

template <int N, int P=2>
struct Prime;

template <>
struct Prime<2, 2>
{
    static inline constexpr bool Value = true;
};

template <int P>
struct Prime<2, P>
{
    static inline constexpr bool Value = true;
};

template <int P>
struct Prime<P, P>
{
    static inline constexpr bool Value = true;
};

template <int N, int P>
struct Prime
{
    static inline constexpr bool Value = IfElseThen<
        (N >= 2 && N % P != 0 && P <= N),
        Prime<N, P + 1>,
        FalseType>::Type::Value;
};

static_assert(Prime<-2>::Value == false);
static_assert(Prime<-1>::Value == false);
static_assert(Prime<0>::Value == false);
static_assert(Prime<1>::Value == false);
static_assert(Prime<2>::Value == true);
static_assert(Prime<3>::Value == true);
static_assert(Prime<4>::Value == false);
static_assert(Prime<5>::Value == true);
static_assert(Prime<6>::Value == false);
static_assert(Prime<7>::Value == true);

}

#endif //TEMPLATEMETAPROGRAMMING_PRIME_H
