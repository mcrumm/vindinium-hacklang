<?hh
namespace Hackdinium\Bot;

use Hackdinium\Aim;
use Hackdinium\Printable;

abstract class Robot implements Bot {
    use Printable;

    protected ImmVector<Aim> $aim;

    public function __construct() {
        $this->aim = ImmVector { Aim::NORTH(), Aim::SOUTH(), Aim::EAST(), Aim::WEST() };
    }
}
