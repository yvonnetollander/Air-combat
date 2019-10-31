# Air Combat

Air combat is a simple 2D sidescrolling airplane dogfighting game game inspired by the likes of [Triplane Turmoil](https://en.wikipedia.org/wiki/Triplane_Turmoil) and the now unavailable Aapeli lentokonepeli. Uses the [SFML](https://www.sfml-dev.org/) library for graphics.

This project was buil for the Aalto University course ELEC-A7151 Object Oriented Programming with C++.

### Directory layout
  * `plan/` -- Project plan
  * `doc/` -- Documentation and related sources
  * `src/` -- Project source files
 
### Prerequisites
#### Windows (native)
- [Mingw-w64](http://mingw-w64.org) - make sure executables are in PATH
- [make](http://gnuwin32.sourceforge.net/packages/make.htm) - note: mingw typically already includes this
- *SFML lib and headers files are included in repo*

#### Windows (WSL)
- [Mingw-w64](http://mingw-w64.org) - *on debian systems: `sudo apt install mingw-w64`*
- make - *on debian systems: `sudo apt install make`*
- *SFML lib and headers files are included in repo*

#### Linux
- gcc - *on debian systems: `sudo apt install gcc`*
- make - *on debian systems: `sudo apt install make`*
- SFML header files - *on debian systems: `sudo apt install libsfml-dev`*

### Usage
- Clone repo
- Make sure prerequisites are in order
- In base dir, use the following commands:
```
make / make br
```
Build and run
```
make build
```
Just build
```
make run
```
Just run

### Platform-specific
The Makefile should detect the environment and build accordingly. If not, the platform-specific commands are further below.
```
make win / wsl / linux
```
Build and run
```
make build-win / build-wsl /build-linux
```
Just build
```
make run-win / run-wsl / run-linux
```
Just run
