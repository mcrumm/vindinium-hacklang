<?hh //strict
namespace Hackdinium\Game;

use Hackdinium\Aim;

class Master {
    private static ImmVector<Aim\Dir> $dirs = ImmVector{};
    private static ?Aim\Dir $stay = null;

    public static function dirs() : ImmVector<Aim\Dir> {
        if (0 === count(self::$dirs)) {
            self::$dirs = ImmVector{ new Aim\North(), new Aim\East(), new Aim\South(), new Aim\West() };
        }
        return self::$dirs;
    }

    public static function dir(string $dir) : Aim\Dir {
        $dirs = self::dirs();
        switch ($dir) {
            case Aim\North::class:  return $dirs[0];
            case Aim\East::class:   return $dirs[1];
            case Aim\South::class:  return $dirs[2];
            case Aim\West::class:   return $dirs[3];
            default:                return self::stay();
        }
    }

    public static function stay() : Aim\Dir {
        if (null === self::$stay) {
            self::$stay = new Aim\Stay();
        }
        return self::$stay;
    }

    private function __construct() {}
}
