<?hh //strict
namespace Hackdinium\Bot\Gadget;

use Hackdinium\Game\Board;
use Hackdinium\Game\Pos;
use Hackdinium\Input;
use Hackdinium\Util\Timer;
use Hackdinium\Util\Queue;
use Hackdinium\f;

type Goal = (function(Pos): bool);
type Stack = Vector<Pos>;
type Path = Queue<Pos>;

class GPS extends Guide {
    public static function boot(Input $input): GPS {
        return new static($input->game->board);
    }

    public function locate(Pos $from, Goal $goal): Stack {
        return f\reverse(Vector::fromItems($this->start($from, $goal)));
    }

    private function start(Pos $from, Goal $f): Path {
        return $this->step(Vector{ Queue::factory( Vector{ $from } ) }, Set{}, $f);
    }

    private function step(Vector<Path> $paths, Set<int> $visited, Goal $f): Path {
        if (0 === $paths->count()) { return new Queue(); }
        $path   = $paths->at(0);
        $paths->removeKey(0);
        $on     = $path->bottom();
        $intPos = $on->toInt($this->board->size);
        if ($visited->contains($intPos)) {
            return $this->step($paths, $visited, $f);
        }
        $found = f\find($on->neighbors(), $f);
        if (null !== $found) {
            $path->unshift($found);
            $vtmp = f\reverse(Vector::fromItems($path));
            $vtmp->removeKey(0);
            return Queue::factory($vtmp);
        }
        $newPath = $paths->addAll($this->validMoves($on, $visited)
            ->map(($p2) ==> { $np = clone $path; $np->unshift($p2); return $np; })
        );
        $visited->add($intPos);
        return $this->step($newPath, $visited, $f);
    }
}
