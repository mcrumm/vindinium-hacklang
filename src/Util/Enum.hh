<?hh
namespace Hackdinium\Util;

use Eloquent\Enumeration\AbstractEnumeration;
use Hackdinium\Printable;

abstract class Enum extends AbstractEnumeration {
    use Printable;

    public function __toString() : string {
        return $this->value();
    }
}
