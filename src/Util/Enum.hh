<?hh
namespace Hackdinium\Util;

use Eloquent\Enumeration\AbstractEnumeration;
use Hackdinium\Printable;

abstract class Enum extends AbstractEnumeration {
    use Printable;

    public static function toImmVector() : ImmVector<Enum> {
        return new ImmVector(self::members());
    }

    public static function toVector() : Vector<Enum> {
        return new Vector(self::members());
    }

    <<Override>> public function __toString() : string {
        return $this->value();
    }
}
