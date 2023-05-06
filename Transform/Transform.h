//
// Created by ngyongxiang on 6/05/23.
//

#ifndef TEMPLATEMETAPROGRAMMING_TRANSFORM_H
#define TEMPLATEMETAPROGRAMMING_TRANSFORM_H

template <int... vals>
struct Vec;

template <int n>
struct MultTwo
{
    static inline constexpr int Value = n * 2;
};

template
<
    typename InputVec,
    template <int> class Functor,
    typename OutputVec=Vec<>
>
struct Transform;

template <template <int> class Functor, int... OutVals>
struct Transform<Vec<>, Functor, Vec<OutVals...>>
{
    using Type = Vec<OutVals...>;
};

template <int Head, int... Tail, template <int> class Functor, int... OutVals>
struct Transform<Vec<Head, Tail...>, Functor, Vec<OutVals...>>
{
    using Type = Transform<Vec<Tail...>, Functor, Vec<OutVals..., Functor<Head>::Value>>::Type;
};

static_assert(std::is_same_v<Transform<Vec<1, 3, 1, -1, -6>, MultTwo>::Type, Vec<2, 6, 2, -2, -12>>);

#endif //TEMPLATEMETAPROGRAMMING_TRANSFORM_H
