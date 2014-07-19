<?hh //strict

namespace Hackdinium\Bot;

use Hackdinium\Aim;
use Hackdinium\Compass;
use Hackdinium\Input;
use Hackdinium\Tile\Wall;

class RandomBot extends Robot {
    use Item\Compass;

    public function move(Input $input) : Aim {
        $dir = $this->first(
            (Aim $dir) ==> !is_a($input->game->board->at($input->hero->pos->to($dir)), Wall::class),
            $this->shuffle($this->aim->toVector())
        );

        return $dir;
    }
}
