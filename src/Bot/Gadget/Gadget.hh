<?hh //strict
namespace Hackdinium\Bot\Gadget;

use Hackdinium\Input;

interface Gadget {
    public static function boot(Input $input): Gadget;
}
