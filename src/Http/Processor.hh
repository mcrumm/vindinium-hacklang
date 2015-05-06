<?hh
namespace Hackdinium\Http;

use GuzzleHttp\Command\Event\ProcessEvent;
use GuzzleHttp\Event\SubscriberInterface;
use Hackdinium\Game;
use Hackdinium\Hero;
use Hackdinium\Input;

class Processor implements SubscriberInterface {

    public function getEvents() : array {
        $m = Map { 'process' => Vector { 'onProcess' } };
        return $m->toArray();
    }

    public function onProcess(ProcessEvent $event) : void {
        $model = $event->getResult();

        $event->setResult(new Input(
            $this->toModel($model['game'], Game::class),
            $this->toModel($model['hero'], Hero::class),
            $model['token'],
            urldecode($model['viewUrl']),
            urldecode($model['playUrl'])
        ));
    }

    private function toModel(array $data, string $name) {
        // Bypass auto-instantiation for the Board
        if (Game\Board::class === $name) {
            return new Game\Board($data['size'], $data['tiles']);
        }

        $class      = new \ReflectionClass($name);
        $invoked    = $class->getConstructor();
        $args       = Vector {};

        if (! $invoked) {
            throw new \RuntimeException(sprintf('Class "%s"  has no constructor.', $name));
        }

        foreach ($invoked->getParameters() as $p) {
            $key = $p->name;

            // Overload heroes array with an ID indexed ImmMap
            if ('heroes' === $key) {
                $args[] = $this->generateHeroesMap($data[$key]);
                continue;
            }

            $klass = $this->getParameterType($p);
            if (null === $klass && array_key_exists($key, $data)) {
                $args[] = $data[$key];
            } elseif(!array_key_exists($key, $data)) {
                $args[] = null;
            } elseif(null !== $klass) {
                $args[] = $this->toModel($data[$key], $klass);
            } else {
                throw new \InvalidArgumentException('Model class could not be determined.');
            }
        }

        return $class->newInstanceArgs($args);
    }

    private function generateHeroesMap(array $data) : ImmMap<int, Hero> {
        $getPairs = ($heroes) ==> {
            foreach ($heroes as $hero) {
                $hero = $this->toModel($hero, Hero::class);
                yield Pair { $hero->id, $hero };
            }
        };

        return ImmMap::fromItems($getPairs($data));
    }

    private function getParameterType(\ReflectionParameter $p) : ?string {
        $type = null;
        try {
            $class = $p->getClass();
            if (!$class) {
                $type = null;
            } elseif ($class->implementsInterface('\\OutputCollection')) {
                $type = null;
            } else {
                $type = $class->name;
            }
        }
        catch(\ReflectionException $ex) {}
        return $type;
    }
}
