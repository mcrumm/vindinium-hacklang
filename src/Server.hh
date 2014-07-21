<?hh //strict
namespace Hackdinium;

final class Server {
    private Http\Client $http;

    public function __construct(string $key, string $host) {
	$this->http = new Http\Client($key, $host);
    }

    public function arena() : Input {
        return $this->http->arena();
    }

    public function move(string $url, Aim $dir) : Input {
        return $this->http->move(urldecode($url), $dir);
    }

    public function training(int $turns = 300, ?string $map = null) : Input {
        return $this->http->training($turns, $map);
    }
}
