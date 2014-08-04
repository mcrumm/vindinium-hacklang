<?hh //strict
namespace Hackdinium\Bot;

use Hackdinium\Aim;
use Hackdinium\Input;

const int DRINK     =  -2;
const int ENTROPY   =  -1;
const int FIGHT     = -20;

interface Bot {
    public function move(Input $input): Aim;
}
