Hackdinium
==========

[Vindinium](http://vindinium.org) starter in (mostly) [hack-strict](http://hacklang.org), based on the [Scala version](https://github.com/ornicar/vindinium-starter-scala) by @ornicar.

>Four legendary heroes were fighting for the land of Vindinium  
>Making their way in the dangerous woods  
>Slashing goblins and stealing gold mines  
>And looking for a tavern where to drink their gold

### Play

The game script is located at [`bin/hackdinium`](bin/hackdinium), or `vendor/bin/hackdinium` if installed via composer.

```bash
$ hackdinium

SUMMARY
    hackdinium -- Vindinium is an Artificial Intelligence programming challenge.

USAGE
    hackdinium <key> <[training|arena]> [-t,--turns=300] [-h,--host="http://vindinium.org/"]

DESCRIPTION
    Vindinium is an Artificial Intelligence programming challenge.
You have to take the control of a legendary hero using the programming language of your choice.
You will fight with other AI for a predetermined number of turns and the hero with the greatest
amount of gold will win.

For more information, visit http://vindinium.org/

OPTIONS
    -t [<value>]
    --turns[=<value>]
        Number of Turns / Number of Arena Games
    -m [<value>]
    --map[=<value>]
        Training mode map [m1..m6]
    -h [<value>]
    --host[=<value>]
        The host URL
```


### Extend

#### Install

Hackdinium is available via [composer](http://getcomposer.org).

```JSON
{
    "require": {
        "mcrumm/vindinium-hacklang": "~0.3"
    }
}
```

#### Virtual Environment

Check out the [vagrant-hackdinium](https://github.com/mcrumm/vagrant-hackdinium) repo for a fully-functional virtual environment for Hackdinium.

### Why "mostly" hack-strict?

First off, the top-level namespace, as well as the [Bot](src/Bot) and [Game](src/Game) namespaces are entirely `//strict`. Any companion code you write can likely be the same.

However, there are a few `partial` objects/namespaces, as well:

- [Hackdinium\Cli](src/Cli) depends on [Aura.Cli](https://github.com/auraphp/Aura.Cli).
- [Hackdinium\Http](src/Http) extends [vindium-guzzle](https://github.com/mcrumm/vindinium-guzzle), which itself depends on [Guzzle4](https://github.com/guzzle/guzzle).
- [Hackdinium\Util\Enum](src/Util/Enum.hh) depends on [Eloquent\Enumeration](https://github.com/eloquent/enumeration).

> If I had my way, I'd never work... I'd paint, and read, and play violin. I'd climb the mountains, and sing the songs that I like to sing. But I don't got that kinda time. --[P. Diddy](http://m.imdb.com/title/tt0353049/quotes?qt=qt0312304)
