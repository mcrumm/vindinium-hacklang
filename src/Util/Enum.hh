<?hh
namespace Hackdinium\Util;

use Eloquent\Enumeration\AbstractEnumeration;
use Hackdinium\Printable;

abstract class Enum extends AbstractEnumeration {
    use Printable;
    private static ?ImmVector<Enum> $immVector = null;
    private static ?Vector<Enum> $vector = null;

    public static function toImmVector() : ImmVector<Enum> {
        $iv = self::$immVector;
        if (null === $iv) {
            $iv = new ImmVector(self::members());
        }
        return $iv;
    }

    public static function toVector() : Vector<Enum> {
        $v = self::$vector;
        if (null === $v) {
            $v = new Vector(self::members());
        }
        return $v;
    }

    <<Override>> public function __toString() : string {
        return $this->value();
    }
}
