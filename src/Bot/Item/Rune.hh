<?hh //strict
namespace Hackdinium\Bot\Item;

use Hackdinium\Bot\Robot;
use Hackdinium\Game\Pos;
use Hackdinium\Hero;
use Hackdinium\Input;
use Hackdinium\Tile;

type RuneScape = shape(
    'teamPlay'  => bool,
    'heroIds'   => Set<int>,
    'enemyIds'  => Set<int>,
    'enemies'   => ImmMap<int, Hero>
);

trait Rune {
    require extends Robot;

    protected ?Input $input = null;

    public function getRune(Input $input) : RuneScape {
        $game       = $input->game;
        $teamPlay   = $game->heroes->map(($h) ==> $h->name)->toSet()->count() > 1;
        $heroIds    = $game->heroes->map(($h) ==> $h->id)->toSet();

        $enemyF = true === $teamPlay
            ? ($h) ==> $h->name !== $input->hero->name
            : ($h) ==> $h->id   !== $input->hero->id
        ;

        $enemies = $game->heroes->filter($enemyF);
        $enemyIds = $enemies->map(($e) ==> $e->id)->toSet();

        return shape( 'teamPlay' => $teamPlay, 'heroIds' => $heroIds, 'enemies' => $enemies, 'enemyIds' => $enemyIds );
    }
}
