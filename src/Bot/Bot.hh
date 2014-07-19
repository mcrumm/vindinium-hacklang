<?hh //strict
namespace Hackdinium\Bot;

use Hackdinium\Aim;
use Hackdinium\Input;

interface Bot {
    public function move(Input $input): Aim;
}
