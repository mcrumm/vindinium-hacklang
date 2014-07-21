<?hh
namespace Hackdinium\Http;

use Hackdinium\Aim;
use Hackdinium\Input;
use Vindinium\Http\Server;

class Client extends Server {
    public function __construct(string $key, string $host = 'http://vindinium.org/') : void {
        parent::__construct($key, $host);
        $this->client->getEmitter()->attach(new Processor());
    }

    public function arena() : Input {
        return parent::arena();
    }

    public function training(int $turns, ?string $map = null) : Input {
        return parent::training($turns, $map);
    }

    public function move(string $url, Aim $dir) : Input {
        return parent::move($url, (string)$dir);
    }
}
