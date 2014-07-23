<?hh //strict
namespace Hackdinium\Bot\Item;

use Hackdinium\Aim;
use Hackdinium\Bot\Robot;

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
        return \Hackdinium\getOrElse($this->reduce($v, $f)->get(0), $none);
    }

    public function first((function(Aim): bool) $f, ?Vector<Aim> $v = null, ?Aim $none = null) : Aim {
        return $this->find(\Hackdinium\getOrElse($v, $this->aim->toVector()), $f, \Hackdinium\getOrElse($none, Aim::NORTH()));
    }

    private function reduce<T>(Vector<T> $v, (function(T) : bool) $f) : Vector<T> {
        return $v->filter($f);
    }
}
