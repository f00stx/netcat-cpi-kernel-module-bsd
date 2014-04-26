♫ netcat - Cycles Per Instruction
===============================

by [Brandon Lucia](http://brandonlucia.com/music.html), Andrew Olmstead, and David Balatero

Released April 2014

* [http://netcat.co](http://netcat.co)
* [http://netcat.bandcamp.com](http://netcat.bandcamp.com)
* [http://tableandchairsmusic.com/artists/netcat](http://tableandchairsmusic.com/artists/netcat)

Ported to FreeBSD by Richard Walker and Eitan Adler.

Cycles Per Instruction - The Kernel Module Edition - FreeBSD Flavoured!
-----------------------------------------------------------------------

Cycles Per Instruction has been ported to FreeBSD as a totally self-indulgent exercise in kernel module writing.

You'll need FreeBSD (really?), and audio/vorbis-tools. Note that this has only been tested on FreeBSD 10 on a PowerPC 970 (Powermac G5 PCIe).

UPDATE: Successfully builds/loads/plays on FreeBSD 10 on amd64. However, loading the module causes a kernel panic for any system shy of 6GB RAM (from a barebones install anyway - YMMV).

Interestingly enough, the order in which the track headers are included is still important - 1-2-3-4-5-6 crashes the compiler, 4-5-6-1-2-3 compiles fine. Someone who knows C a bit better than me could probably work out why.

If it sounds like someone is sandblasting a glockenspiel, you're probably having the same issue with the Powermac built-in audio that I did. Playing it through a pair of USB headphones worked a treat.

Enjoy! And please improve my chicken-scrawl code. I'm new to C.

Thanks to Eitan Adler for his early work on porting the module.
