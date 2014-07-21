<?hh //strict

namespace Hackdinium\Bot;

use Hackdinium\Aim;
use Hackdinium\Compass;
use Hackdinium\Input;
use Hackdinium\Tile;

class RandomBot extends Robot {
    use Item\Compass;

    public function move(Input $input) : Aim {
        $dir = $this->first(
		(Aim $dir) ==> {
		    $move = $input->game->board->at($input->hero->pos->to($dir)); 
		    return !is_a($move, Tile\Wall::class)
			    && !is_a($move, Tile\Tavern::class)
			    && !is_a($move, Tile\MineTile::class)
		    ;
		},
            $this->shuffle($this->aim->toVector())
        );

        return $dir;
    }
}
