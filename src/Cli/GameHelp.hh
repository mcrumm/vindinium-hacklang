<?hh
namespace Hackdinium\Cli;

use Aura\Cli\Help;

class GameHelp extends Help {
    protected function init() {
        $this->setSummary('Vindinium is an Artificial Intelligence programming challenge.');
        $this->setUsage('<key> <[<<cyan>>training|<<red>>arena<<reset>>]> [-t,--turns=<<yellow>>300<<reset>>] [-h,--host=<<yellow>>"http://vindinium.org/"<<reset>>]');
        $this->setOptions([
            't,turns::' => 'Number of Turns / Number of Arena Games',
            'm::'       => 'Training mode map type [1..6]',
            'h,host::'  => 'The host URL'
        ]);
        $this->setDescr(<<<'EOD'
Vindinium is an Artificial Intelligence programming challenge.
You have to take the control of a legendary hero using the programming language of your choice.
You will fight with other AI for a predetermined number of turns and the hero with the greatest
amount of gold will win.

For more information, visit http://vindinium.org/
EOD
);
    }
}
