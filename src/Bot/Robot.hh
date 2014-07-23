<?hh //strict
namespace Hackdinium\Bot;

use Hackdinium\Aim;
use Hackdinium\Printable;

abstract class Robot implements Bot {
    use Printable;

    protected ImmVector<Aim> $aim;

    public function __construct() {
        $this->aim = ImmVector { Aim::NORTH(), Aim::EAST(), Aim::SOUTH(), Aim::WEST() };
    }
}
