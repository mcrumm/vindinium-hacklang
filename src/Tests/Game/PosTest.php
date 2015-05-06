<?hh //strict
namespace Hackdinium\Tests\Game;

use Hackdinium\Aim;
use Hackdinium\Game\Pos;
use HackPack\HackUnit\Core\TestCase;

class PosTest extends TestCase {
    protected Vector<(Pos, Aim, string)> $toProvider;
    protected Vector<(Pos, Pos, Aim)> $towardsProvider;

    public function __construct(protected string $name) {
        parent::__construct($name);
        $start = new Pos(0, 0);
        $this->toProvider = Vector {
            tuple($start, Aim::North, 'x:-1 y:0'),
            tuple($start, Aim::East,  'x:1 y:0'),
            tuple($start, Aim::South, 'x:0 y:1'),
            tuple($start, Aim::West,  'x:0 y:-1'),
            tuple($start, Aim::Stay,  'x:0 y:0')
        };
        $this->towardsProvider = Vector {
            tuple($start, new Pos(-1, 0), Aim::North),
            tuple($start, new Pos(0, 1),  Aim::East),
            tuple($start, new Pos(1, 0),  Aim::South),
            tuple($start, new Pos(0, -1), Aim::West),
        };
    }

    public function testTo() : void {
        foreach ($this->toProvider as $item) {
            $this->expect($item[0]->to($item[1])->__toString())->toEqual($item[2]);
        }
    }

    public function testTowards() : void {
        foreach ($this->towardsProvider as $item) {
            $this->expect($item[0]->towards($item[1]))->toEqual($item[2]);
        }
    }
}
