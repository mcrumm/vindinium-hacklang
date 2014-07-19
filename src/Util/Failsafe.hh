<?hh //strict
namespace Hackdinium\Util;

use Hackdinium\Cli\Shell;

class Failsafe {
    public function __construct(private Shell $shell) {
        set_exception_handler([ $this, 'handleException' ]);
        //register_shutdown_function([ $this, 'handleFatal' ]);
    }

    public function handleException(\Exception $ex) : void {
        $this->shell->renderException($ex);
    }

    public function handleFatal() : void {
        $error = error_get_last();
        if (null !== $error) {
            $this->shell->println(sprintf(
                '<<red>>FATAL: %s on line %d in "%s"<<reset>>',
                $error['message'], $error['line'], $error['file']
            ));
            $this->shell->println(print_r(debug_backtrace(0), true));
        }
    }

    public function on((function() : void) $action) : void {
        try { $action(); }
        catch (\Exception $ex) { $this->handleException($ex); }
    }
}
