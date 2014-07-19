<?hh //strict
namespace Hackdinium;

final class Server {
    private Http\Client $http;

    public function __construct(string $key, ?string $host = null) {
        $this->http = new Http\Client(null === $host ? [] : [ 'baseUrl' => $host ], [ 'defaults' => [ 'key' => $key ] ]);
    }

    public function arena() : Input {
        return $this->http->arena();
    }

    public function move(string $url, Aim $dir) : Input {
        return $this->http->move($url, $dir);
    }

    public function training(int $turns = 300, ?string $map = null) : Input {
        return $this->http->training($turns, $map);
    }
}
