<?hh //strict
namespace Hackdinium\Tests;

use Hackdinium\Tile;
use HackPack\HackUnit\Core\TestCase;

class TileTest extends TestCase {
    protected Map<string, string> $tileStrings;
    protected Map<string, Vector<string>> $tilePatterns;

    public function __construct(protected string $name) {
        parent::__construct($name);
        $this->tileStrings = Map {
            Tile\Air::class         => '  ',
            Tile\Tavern::class      => '[]',
            Tile\Wall::class        => '##',
            Tile\MineTile::class    => '$-',
        };
        $this->tilePatterns = Map {
            Tile\MineTile::class    => Vector { '$-', '$1', '$2', '$3', '$4' },
            Tile\HeroTile::class    => Vector { '@1', '@2', '@3', '@4' }
        };

    }

    public function testFromString() : void {
        foreach ($this->tileStrings as $klass => $str) {
            $this->expect(is_a($this->getTile($str), $klass))->toEqual(true);
        }
    }

    public function testFromStringPattern() : void {
        foreach ($this->tilePatterns as $klass => $strings) {
            foreach ($strings as $str) {
                $this->expect(is_a($this->getTile($str), $klass))->toEqual(true);
            }
        }
    }

    private function getTile(string $str) : Tile\Tile {
        return Tile\Tile::fromString($str);
    }
}
