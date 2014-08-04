<?hh //strict
namespace Hackdinium\Bot\Gadget;

use Hackdinium\Game\Board;
use Hackdinium\Game\Pos;
use Hackdinium\Input;
use Hackdinium\Tile;

abstract class Guide implements Gadget {
    public function is(Pos $pos, (function(Tile\Tile): bool) $goal): bool {
        return $this->board->at($pos)->exists($goal);
    }

    public function isAir(Pos $p): bool {
        return $this->is($p, ($tile) ==> $tile->is(Tile\Air::class));
    }

    public function isAnyHero(Pos $p): bool {
        return $this->is($p, ($tile) ==> $tile->is(Tile\HeroTile::class));
    }

    public function isEnemy(int $id): (function(Pos): bool) {
        return (Pos $ePos) ==> {
            return $this->is($ePos, ($eTile) ==> {
                if (!is_a($eTile, Tile\HeroTile::class)) {
                    return false;
                }
                // UNSAFE
                return $id === $eTile->id;
            });
        };
    }

    public function isTavern(Pos $p): bool {
        return $this->is($p, ($tile) ==> $tile->is(Tile\Tavern::class));
    }
    
    public function isUnownedMine(int $id): (function(Pos): bool) {
        return (Pos $pos) ==> $this->is($pos, ($tile) ==> {
            if (!is_a($tile, Tile\MineTile::class)) {
                return false;
            }
            // UNSAFE
            return $id != $tile->heroId;
        });
    }

    public function posToInt(Pos $p): int {
        return $p->toInt($this->board->size);
    }

    public function validMoves(Pos $pos, Set<int> $visited = Set{}): ImmVector<Pos> {
        return $pos->neighbors()
            ->filter(($p) ==> $this->isAir($p))
            ->filter(($p2) ==> !$visited->contains($p2->toInt($this->board->size)))
        ;
    }

    protected function __construct(protected Board $board) {}
}
