//
// Created by ngyongxiang on 5/05/23.
//

#ifndef TEMPLATEMETAPROGRAMMING_UNIQUE_H
#define TEMPLATEMETAPROGRAMMING_UNIQUE_H

#include <type_traits>

namespace Unique_Unique
{

template <int... Vals>
struct Vector;

template <typename In, typename Out=Vector<>>
struct Unique;

template <int Head, int... Tail, int... Output>
struct Unique<Vector<Head, Tail...>, Vector<Output...>>
{
    using Type = Unique<Vector<Tail...>, Vector<Output..., Head>>::Type;
};

template <int Head, int... Tail, int... Output>
struct Unique<Vector<Head, Head, Tail...>, Vector<Output...>>
{
    using Type = Unique<Vector<Head, Tail...>, Vector<Output...>>::Type;
};

template <typename Out>
struct Unique<Vector<>, Out>
{
    using Type = Out;
};

static_assert(std::is_same_v<Vector<1, 2, 3, 4, 5>, Unique<Vector<1, 1, 1, 2, 2, 3, 3, 3, 4, 5>>::Type>);
static_assert(std::is_same_v<Vector<1, 2, 3, 4, 5>, Unique<Vector<1, 2, 2, 3, 3, 4, 4, 4, 5, 5>>::Type>);
static_assert(std::is_same_v<Vector<1, 2, 3, 4, 5>, Unique<Vector<1, 2, 3, 4, 5>>::Type>);
static_assert(std::is_same_v<Vector<>, Unique<Vector<>>::Type>);
static_assert(std::is_same_v<Vector<1, 2, 3, 1, 3, 2>, Unique<Vector<1, 1, 2, 2, 3, 1, 3, 3, 2>>::Type>);

}

#endif //TEMPLATEMETAPROGRAMMING_UNIQUE_H
