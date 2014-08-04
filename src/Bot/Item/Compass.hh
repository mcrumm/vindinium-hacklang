<?hh //strict
namespace Hackdinium\Bot\Item;

use Hackdinium\Aim;
use Hackdinium\Bot\Robot;
use Hackdinium\f;

trait Compass {
    require extends Robot;

    public function directions() : ImmVector<Aim> {
       return $this->aim;
    }

    public function shuffle(Vector<Aim> $v) : Vector<Aim> {
        $v->shuffle();
        return $v;
    }

    public function find(Vector<Aim> $v, (function(Aim): bool) $f, Aim $none) : Aim {
        return f\getOrElse(f\reduce($v->toImmVector(), $f)->get(0), $none);
    }

    public function first((function(Aim): bool) $f, ?Vector<Aim> $v = null, ?Aim $none = null) : Aim {
        $v = null === $v ? $this->aim->toImmVector() : $v->toImmVector();
        return f\getOrElse(f\find($v, $f), f\getOrElse($none, Aim::STAY()));
    }

    private function reduce<T>(Vector<T> $v, (function(T) : bool) $f) : Vector<T> {
        return f\reduce($v->toImmVector(), $f)->toVector();
    }
}
