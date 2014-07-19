<?hh //strict
namespace Hackdinium\Tile;

class Tile {
    use \Hackdinium\Printable;
    public static function fromString(string $str) : Tile {
        switch($str) {
            case '  ':  return new Air();
            case '##':  return new Wall();
            case '[]':  return new Tavern();
        }

        $matches = [];

        if (preg_match('/\$([-0-9])/', $str, $matches)) {
            return new MineTile((int)$matches[1]);
        } elseif(preg_match('/\@([-0-9])/', $str, $matches)) {
            return new HeroTile((int)$matches[1]);
        }

        throw new \InvalidArgumentException(sprintf('Unknown tile "%s"', $str));
    }
}
final class Air         extends Tile {}
final class Wall        extends Tile {}
final class Tavern      extends Tile {}
final class HeroTile    extends Tile { public function __construct(public int $id) {} }
final class MineTile    extends Tile { public function __construct(public ?int $heroId) {} }

namespace Hackdinium;

final class Aim extends Util\Enum {
    const NORTH = 'North';
    const EAST  = 'East';
    const SOUTH = 'South';
    const WEST  = 'West';
}

final class Hero {
    use Printable;

    public function __construct(
        public int $id,
        public string $name,
        public ?string $userId,
        public ?int $elo,
        public Game\Pos $pos,
        public int $life,
        public int $gold,
        public int $mineCount,
        public Game\Pos $spawnPos,
        public bool $crashed
    ) {}

    <<Override>> public function __toString() : string {
        return "Hero $this->id $this->pos life:$this->life mine:$this->mineCount gold:$this->gold";
    }
}

final class Game {
    public function __construct(
        public string $id,
        public int $turn,
        public int $maxTurns,
        public Vector<Hero> $heroes,
        public Game\Board $board,
        public bool $finished
    ) {}
}

final class Input {
    public function __construct(
        public Game $game,
        public Hero $hero,
        public string $token,
        public string $viewUrl,
        public string $playUrl
    ) {}
}

trait Printable {
    public function __toString() : string {
        return array_slice(explode('\\', static::class), -1)[0];
    }
}

function getOrElse<T>(?T $var, T $none) : T {
    return is_null($var) ? $none : $var;
}