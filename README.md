This is a C-SDL Drawing Demo

it does demonstrate how...

- to apply [De Casteljau's algorithm](https://en.wikipedia.org/wiki/De_Casteljau%27s_algorithm) on quadratic [Bézier curves](https://en.wikipedia.org/wiki/B%C3%A9zier_curve).

Screenshot:  
![Screenshot](./shot.jpg)

## Building

Linking against: `SDL2 SDL2_image SDL2_gfx`<br>

arch: `sudo pacman -S sdl2 sdl2_gfx sdl2_image`

On other Distros look out for ... and so on:<br>
deb/apt: libsdl2, libsdl2-dev<br>
rpm/yum: SDL2, SDL2-devel<br>

`git clone git@github.com:Acry/SDL2-Pong.git`<br>
`cd SDL2-Pong`

`make` will build native Linux executeables.<br>
`1`, `2`, `3` are wip builds.<br>
`casteljau` is the final build<br>

## Useful links:

[My Homepage](https://acry.github.io/)

[Nils Pipenbrinck aka Submissive/Cubic & \$eeN](http://www.cubic.org/docs/bezier.htm)<br>
[SDL2](https://www.libsdl.org/)<br>
[SDL-Discourse](https://discourse.libsdl.org)<br>
