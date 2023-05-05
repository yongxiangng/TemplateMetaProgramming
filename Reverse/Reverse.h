//
// Created by ngyongxiang on 5/05/23.
//

#ifndef TEMPLATEMETAPROGRAMMING_REVERSE_H
#define TEMPLATEMETAPROGRAMMING_REVERSE_H

#include <type_traits>

namespace Reverse_Reverse
{

template <int... Vals>
struct Vec;

template <typename In, typename Out=Vec<>>
struct Reverse;

template <int Head, int... Tail, int... Out>
struct Reverse<Vec<Head, Tail...>, Vec<Out...>>
{
    using Type = Reverse<Vec<Tail...>, Vec<Head, Out...>>::Type;
};

template <typename Out>
struct Reverse<Vec<>, Out>
{
    using Type = Out;
};

static_assert(std::is_same_v<Vec<1, 2, 3, 4>, Reverse<Vec<4, 3, 2, 1>>::Type>);

}

#endif //TEMPLATEMETAPROGRAMMING_REVERSE_H
