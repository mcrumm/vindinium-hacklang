Hackdinium
==========

[Vindinium](http://vindinium.org) starter in (mostly) [hack-strict](http://hacklang.org), based on the [Scala version](https://github.com/ornicar/vindinium-starter-scala) by @ornicar.

>Four legendary heroes were fighting for the land of Vindinium  
>Making their way in the dangerous woods  
>Slashing goblins and stealing gold mines  
>And looking for a tavern where to drink their gold

### Play

The game script is located at [`bin/hackdinium`](bin/hackdinium), or `vendor/bin/hackdinium` if installed via composer.

**Usage**

```
Arguments:
 key                   Your API Key
 mode                  The game mode [training, arena] (default: "training")
 turns                 # Turns / # Games
 url                   Host URL (default: "http://vindinium.org/")

Options:
 --map (-m)            Training map [m1..m6]
 --quiet (-q)          Do not output any message.
 --verbose (-v|vv|vvv) Increase the verbosity of messages: 1 for normal output, 2 for more verbose output and 3 for debug
```

### Extend

Build your own Hackdinium Bot with [composer](http://getcomposer.org).

```JSON
{
    "require": {
        "mcrumm/vindinium-hacklang": "@stable"
    }
}
```

### Virtual Environment (some assembly required)

If you require an hhvm-friendly virtual environment, using [puphpet](http://puphpet.org/) is the best method to create one.

Scripts for configuring some [helpful hack tools](scripts/) are also included in this repo. Copy the contents of the [scripts](scripts/) directory into `puphpet/files/exec-always` directory and the following will be configured automatically:

-  [vim-hack](https://github.com/hhvm/vim-hack)
-  [composer bash-completion](https://github.com/iArren/composer-bash-completion)
-  [composer via HHVM](https://blog.engineyard.com/2014/hhvm-hack-part-2)
-  [hhi files](https://github.com/facebook/hhvm/tree/master/hphp/hack/hhi) synced to project directory

### Why "mostly" hack-strict?

First off, the top-level namespace, as well as the [Bot](src/Bot) and [Game](src/Game) namespaces are entirely `//strict`. Any companion code you write can likely be the same.

However, [Hackdinium\Console](src/Console) has dependencies on the Symfony Console component, and [Hackdinium\Http](src/Http) depends on Guzzle4, so from there, it's partial all the way down.

> If I had my way, I'd never work... I'd paint, and read, and play violin. I'd climb the mountains, and sing the songs that I like to sing. But I don't got that kinda time. --[P. Diddy](http://m.imdb.com/title/tt0353049/quotes?qt=qt0312304)
