<?hh
namespace Hackdinium\Util;

final class Queue<T> extends \SplQueue<T> implements \IteratorAggregate<T> {
    public static function factory(?Iterable<T> $values = null): this {
        $q = new self();
        if (null === $values) {
            return $q;
        }
        return $q->enqueueAll($values);
    }

    public function enqueueAll(Iterable<T> $values): this {
        foreach ($values as $value) {
            $this->enqueue($value);
        }
        return $this;
    }

    public function getIterator(): \Continuation<T> {
        foreach ($this as $item) {
            yield $item;
        }
    }

    public function pushAll(Iterable<T> $values): this {
        foreach ($values as $value) {
            $this->push($value);
        }
        return $this;
    }
}
