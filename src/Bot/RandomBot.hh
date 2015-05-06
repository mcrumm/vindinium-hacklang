<?hh //strict
namespace Hackdinium\Bot;

use Hackdinium\Aim;
use Hackdinium\Input;
use Hackdinium\Tile;

class RandomBot extends Robot {
    use Item\Compass;

    public function move(Input $input) : Aim {
        return $this->first(
            (Aim $dir) ==> !is_a($input->game->board->at($input->hero->pos->to($dir)), Tile\Wall::class),
            $this->shuffle($this->aim->toVector())
        );
    }
}
