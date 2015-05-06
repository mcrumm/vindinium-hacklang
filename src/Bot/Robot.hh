<?hh //strict
namespace Hackdinium\Bot;

use Hackdinium\Aim;
use Hackdinium\Printable;

abstract class Robot implements Bot {
    use Printable;

    protected ImmVector<Aim> $aim = ImmVector { Aim::North, Aim::East, Aim::South, Aim::West };

    protected function tooPerilous(string $msg = 'The path is wrought with peril. Better stay put.') : Aim {
        echo $msg . "\n";
        return Aim::Stay;
    }
}
