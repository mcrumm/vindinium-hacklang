<?hh //strict
namespace Hackdinium\Game;

use Hackdinium\Aim;

final class Pos {
    static private ImmVector<Aim> $compass = ImmVector { Aim::North, Aim::East, Aim::South, Aim::West };

    public function __construct(public int $x, public int $y) {}

    public function neighbors() : ImmVector<Pos> {
        return self::$compass->map($dir ==> $this->to($dir));
    }

    public function to(Aim $dir) : this {
        switch ($dir) {
            case Aim::North:  return $this->copy(-1,  0);
            case Aim::East:   return $this->copy( 0,  1);
            case Aim::South:  return $this->copy( 1,  0);
            case Aim::West:   return $this->copy( 0, -1);
            case Aim::Stay:   return $this;
        }
    }

    public function towards(Pos $pos) : ?Aim {
        if      ($pos->y < $this->y) { return Aim::West;  }
        elseif  ($pos->x > $this->x) { return Aim::South; }
        elseif  ($pos->y > $this->y) { return Aim::East;  }
        elseif  ($pos->x < $this->x) { return Aim::North; }
        return null;
    }

    public function toInt(int $size) : int {
        return !$this->within($size) ? -1 : $this->x * $size + $this->y;
    }

    public function within(int $size) : bool {
        return $this->x >= 0 && $this->x < $size && $this->y >= 0 && $this->y < $size;
    }

    public function __toString() : string {
        return sprintf('x:%d y:%d', $this->x, $this->y);
    }

    private function copy(int $x, int $y) : this {
        return new Pos($this->x + $x, $this->y + $y);
    }
}
