<?hh //strict
namespace Hackdinium\f;

type predicate<T> = (function(T): bool);

function find<T>(ImmVector<T> $v, ?predicate<T> $p): ?T {
    return null === $p ? $v->get(0) : reduce($v, $p)->get(0);
}

function getOrElse<T>(?T $var, T $none): T {
    return null === $var ? $none : $var;
}

function reverse<T>(Vector<T> $v): Vector<T> {
    $v->reverse();
    return $v;
}

function shuffle<T>(Vector<T> $v): Vector<T> {
    $v->shuffle();
    return $v;
}

function reduce<T>(ImmVector<T> $v, predicate<T> $p): ImmVector<T> {
    return $v->filter($p);
}
