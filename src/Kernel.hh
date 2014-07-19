<?hh //strict
namespace Hackdinium;

use Hackdinium\Cli\Shell;
use Hackdinium\Util\Failsafe;

final class Kernel {
    private ?Bot\Bot $bot;
    private Failsafe $failsafe;
    private Shell $shell;

    public function __construct(private array<string> $args = []) {
        $this->shell    = new Shell($args);
        $this->failsafe = new Failsafe($this->shell);
        $this->bot      = new Bot\RandomBot();
    }

    public function arena(Server $server, int $games) : void {
        $oneGame    = $it ==> {
            $it = is_null($it) ? 1 : $it;
            $this->shell->println("[$it/$games] Waiting for pairing...");
            $input = $server->arena();
            $this->shell->println("[$it/$games] Start arena game {$input->viewUrl}");
            $this->steps($server, $input);
            $this->shell->println("\n[$it/$games] Finished arena game {$input->viewUrl}");
            return $it < $games ? ++$it : 0;
        };

        $i = 1;
        while (0 !== $i && $i < $games) {
            $i = $oneGame($i);
        }
    }

    public function training(Server $server, (function(Server) : Input) $boot) : void {
        $this->failsafe->on(() ==> {
            $input = $boot($server);
            $this->shell->println("Training game {$input->viewUrl}");
            $this->steps($server, $input);
            $this->shell->println("\nFinished training game {$input->viewUrl}");
        });
    }

    public function run(?Bot\Bot $bot = null) : void {
        $this->failsafe->on(() ==> {
            $this->bot = null === $bot ? null : $bot;
            $this->shell->boot($this);
        });
    }

    private function steps(Server $server, Input $input) : void {
        $this->failsafe->on(() ==> {
            $this->step($server, $input);
        });
    }

    private function step(Server $server, Input $input) : void {
        $bot = $this->bot;
        if (null === $bot) {
            throw new \RuntimeException('No robot on duty.');
        }

        if (!$input->game->finished) {
            echo '.';
            $this->step($server, $server->move($input->playUrl, $bot->move($input)));
        }
    }
}
