<?hh //strict
namespace Hackdinium\Bot;

use Hackdinium\Aim;
use Hackdinium\Printable;

abstract class Robot implements Bot {
    use Printable;

    protected ImmVector<Aim> $aim;

    public function __construct() {
        $this->aim = Aim::toCardinal();
    }

    protected function tooPerilous(string $msg = 'The path is wrought with peril.  Better stay put') : Aim {
        echo $msg . "\n";
        return Aim::STAY();
    }
}
