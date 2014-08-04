<?hh //strict
namespace Hackdinium\Tests\Game;

use Hackdinium\Aim;
use Hackdinium\Game\Pos;
use HackPack\HackUnit\Core\TestCase;

class PosTest extends TestCase {
    protected Vector<(Pos, Aim, string)> $toProvider;
    protected Vector<(Pos, Pos, Aim)> $dirToProvider;

    public function __construct(protected string $name) {
        parent::__construct($name);
        $start = new Pos(0, 0);
        $this->toProvider = Vector {
            tuple($start, Aim::NORTH(), 'x:-1 y:0'),
            tuple($start, Aim::EAST(),  'x:0 y:1'),
            tuple($start, Aim::SOUTH(), 'x:1 y:0'),
            tuple($start, Aim::WEST(),  'x:0 y:-1'),
            tuple($start, Aim::STAY(),  'x:0 y:0')
        };
        $this->dirToProvider = Vector {
            tuple($start, new Pos(-1, 0), Aim::NORTH()),
            tuple($start, new Pos(0, 1), Aim::EAST()),
            tuple($start, new Pos(1, 0), Aim::SOUTH()),
            tuple($start, new Pos(0, -1), Aim::WEST()),
        };
    }

    public function testTo() : void {
        foreach ($this->toProvider as $item) {
            $this->expect($item[0]->to($item[1])->__toString())->toEqual($item[2]);
        }
    }

    public function testDirTo() : void {
        foreach ($this->dirToProvider as $item) {
            $this->expect($item[0]->dirTo($item[1]))->toEqual($item[2]);
        }
    }
}
