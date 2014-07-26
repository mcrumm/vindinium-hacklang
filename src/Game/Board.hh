<?hh //strict
namespace Hackdinium\Game;

use Hackdinium\Tile\Tile;
use Hackdinium\Tile\NullTile;

final class Board {
    private NullTile $nil;
    public function __construct(public int $size, public Vector<Tile> $tiles) {
        $this->nil = new NullTile();
    }

    public function at(Pos $pos) : Tile {
        return $pos->within($this->size) ? $this->tiles->at($pos->x * $this->size + $pos->y) : $this->nil;
    }

    public static function parseTiles(string $str) : Vector<Tile> {
        $pieces = str_split($str, 2);
        if (false === $pieces) {
            throw new \InvalidArgumentException(sprintf('Invalid tile string %s', $str));
        }

        return Vector::fromItems($pieces)->map($str ==> Tile::fromString($str));
    }
}
