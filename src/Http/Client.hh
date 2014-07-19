<?hh
namespace Hackdinium\Http;

use GuzzleHttp\Client as HttpClient;
use GuzzleHttp\Command\Event\ProcessEvent;
use GuzzleHttp\Command\Guzzle\GuzzleClient;
use GuzzleHttp\Command\Model;
use Hackdinium\Aim;
use Hackdinium\Input;

class Client {
    private Description $description;
    private GuzzleClient $client;

    public function __construct(private array $config = [], private array $cmdConfig = []) : void {
        $this->description = new Description($config);
        $this->client = new GuzzleClient(new HttpClient(), $this->description, $cmdConfig);
        $this->client->getEmitter()->attach(new Processor());
    }

    public function arena() : Input {
        return $this->send('arena');
    }

    public function training(int $turns, ?string $map = null) : Input {
        return $this->send('training', [ 'turns' => $turns, 'map' => $map ]);
    }

    public function move(string $url, Aim $dir) : Input {
        $url = str_replace((string)$this->description->getBaseUrl() . 'api/', '', $url);
        return $this->send('move', [ 'url' => $url, 'dir' => (string) $dir ]);
    }

    private function send(string $name, array $options = []) : Input {
        $command = $this->client->getCommand($name, $options);
        return $this->client->execute($command);
    }
}
