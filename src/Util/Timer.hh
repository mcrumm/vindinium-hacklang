<?hh //strict
namespace Hackdinium\Util;

class Timer {
    /**
     * @var array
     */
    private static array<string,int> $times = array(
      'hour'   => 3600000,
      'minute' => 60000,
      'second' => 1000
    );

    /**
     * @var array
     */
    private static array<string,int> $startTimes = array();

    /**
     * @var float
     */
    public static float $requestTime = 0.0;

    /**
     * Starts the timer.
     */
    public static function start(): void {
        array_push(self::$startTimes, microtime(true));
    }

    /**
     * Stops the timer and returns the elapsed time.
     *
     * @return float
     */
    public static function stop(): float {
        return microtime(true) - array_pop(self::$startTimes);
    }

    /**
     * Formats the elapsed time as a string.
     *
     * @param  float $time
     * @return string
     */
    public static function secondsToTimeString(float $time): string {
        $ms = round($time * 1000);

        foreach (self::$times as $unit => $value) {
            if ($ms >= $value) {
                $time = floor($ms / $value * 100.0) / 100.0;
                return sprintf('%f %s', $time, $time == 1 ? $unit : $unit . 's');
            }
        }

        return (string)$ms . ' ms';
    }

    /**
     * Formats the elapsed time since the start of the request as a string.
     *
     * @return string
     */
    public static function timeSinceStartOfRequest(): string {
        return self::secondsToTimeString(microtime(true) - self::$requestTime);
    }

    /**
     * Returns the resources (time, memory) of the request as a string.
     *
     * @return string
     */
    public static function resourceUsage(): string {
        return sprintf(
          'Time: %s, Memory: %4.2fMb',
          self::timeSinceStartOfRequest(),
          memory_get_peak_usage(true) / 1048576
        );
    }
}
