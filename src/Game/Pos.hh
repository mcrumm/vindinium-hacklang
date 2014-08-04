<?hh //strict
namespace Hackdinium\Game;

use Hackdinium\Aim;

final class Pos {
    public function __construct(public int $x, public int $y) {}

    public function neighbors() : ImmVector<Pos> {
        return Aim::toCardinal()->map($dir ==> $this->to($dir));
    }

    public function to(Aim $dir) : this {
        switch ($dir) {
            case Aim::NORTH():  return $this->copy(-1,  0);
            case Aim::EAST():   return $this->copy( 0,  1);
            case Aim::SOUTH():  return $this->copy( 1,  0);
            case Aim::WEST():   return $this->copy( 0, -1);
            case Aim::STAY():   // FALLTHROUGH
            default:            return $this;
        }
    }

    public function dirTo(Pos $pos) : ?Aim {
        if      ($pos->y < $this->y) { return Aim::WEST(); }
        elseif  ($pos->x > $this->x) { return Aim::SOUTH(); }
        elseif  ($pos->y > $this->y) { return Aim::EAST(); }
        elseif  ($pos->x < $this->x) { return Aim::NORTH(); }
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
