<?hh
namespace Hackdinium\Cli;

use Aura\Cli\CliFactory;
use Aura\Cli\Context;
use Aura\Cli\Status;
use Hackdinium\Kernel;
use Hackdinium\Server;

class Shell {
    const ARG_KEY   = 1;
    const ARG_MODE  = 2;

    private Stdio $io;
    private Context $context;
    private GameHelp $help;
    private Vector<string> $modes = Vector { 'training', 'arena' };

    public function __construct(private array<string> $args = []) {
                    $f  = new CliFactory();
        $this->context  = $f->newContext([ 'argv' => $args ]);
        $this->io       = $f->newStdio();
        $this->help     = new GameHelp(new Context\OptionFactory());
    }

    public function boot(Kernel $kernel) : void {
        try {
            $getopt = $this->getopt();
            $this->startGame($kernel, $getopt);
        } catch (\Exception $ex) {
            $this->printUsage();
            $this->renderException($ex);
            exit(Status::USAGE);
        }
    }

    public function println(string $message) : void {
        $this->io->outln($message);
    }

    public function renderException(\Exception $ex) : void {
        $this->fail(() ==> {
            do {
                $prev = $ex->getPrevious();
                $this->io->errln($ex->getMessage());
                $this->io->errln($ex->getTraceAsString());
                $ex = $prev;
            } while (null !== $ex);
        });
    }

    private function fail((function():void) $output, ?int $code = null) : void {
        $this->io->out('<<red>>');
        $output();
        if (null !== $code) {
            exit($code);
        }
        $this->io->out('<<reset>>');
    }

    private function getopt() : Context\Getopt {
        $getopt = $this->context->getopt($this->help->getOptions());

        if ($getopt->hasErrors()) {
            throw array_reduce($getopt->getErrors(), ($prev, $ex) ==> {
                $ex->setPrevious($prev);
                return $ex;
            }, new \RuntimeException());
        }

        return $getopt;
    }

    private function makeServer(Context\Getopt $getopt) : Server {
        $key = $getopt->get(self::ARG_KEY);
        if (null === $key) {
            throw new \InvalidArgumentException('You must specify your API key.');
        }

        return new Server($key, $getopt->get('-h', 'http://vindinium.org'));
    }

    private function printUsage(string $name = 'hackdinium') : void {
        $this->io->outln($this->help->getHelp($name));
    }

    private function startGame(Kernel $kernel, Context\Getopt $getopt) : void {
        $mode = $getopt->get(self::ARG_MODE, 'training');
        if (-1 === $this->modes->linearSearch($mode)) {
            throw new \InvalidArgumentException(sprintf('Mode "%s" must be one of %s', $mode, implode(',', $this->modes->toArray()))); 
        }

        $server = $this->makeServer($getopt);

        if ('arena' === $mode) {
            $kernel->arena($server, (int)$getopt->get('-t', PHP_INT_MAX));
        } else {
            $turns  = (int) $getopt->get('-t', 200);
            $map    = $getopt->get('-m', null);
            $kernel->training($server, ($server) ==> $server->training($turns, $map));
        }

        exit(Status::SUCCESS);
    }
}
