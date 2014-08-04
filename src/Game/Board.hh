<?hh //strict
namespace Hackdinium\Game;

use Hackdinium\Tile\Tile;
use Hackdinium\Tile\NullTile;

final class Board {
    public Vector<Tile> $tiles;
    private NullTile $nil;

    public function __construct(public int $size, private string $mud) {
        $this->nil = new NullTile();
        $this->tiles = static::parseTiles($mud);
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

    public function __toString(): string {
        $lines  = str_split($this->mud, $this->size * 2);
        return implode("\n", $lines);
    }
}
