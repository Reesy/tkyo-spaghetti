# TkyoSpaghetti

This is an endless runner style game for the tkyosam fam. 

This game is compatible with touch screen devices and PC with mouse and keyboard. 

You can play the game here: [Tkyospaghetti](https://jim.wales/tkyospaghetti/)

![Game screenshot](game_screenshot.png)


## Platforms 

|  Platform         |  Status   |
| ----------------- | --------- |
| Windows - MingGW  |   ✔️      |
| Windows - MSVC    |   ✔️      |
| OSX               |   ✔️      |
| Browser - Emscripten  | ✔️   |
| Browser - Emscripten (with docker) | ✔️   |


## Cloning

How to clone:

```
git clone --recurse-submodules https://github.com/Reesy/TkyoSpaghetti
```

## Building: 
This project has a dependency on ```SDL2```, ```SDL2_image```, ```SDL2_mixer``` and ```SDL2_ttf``` (which I have bundled under /libs) but can be found at libsdl.org.

<dl>
    <dt> Requirements<dt>
    <dd style='color:red'> CMake -- required to build this project </dd>
<dl>
    
<dl>
    <dt> Optional Requirements<dt>
    <dd style='color:red'> emscripten/emsdk -- required to build this project for the web</dd>
    <dd style='color:red'> python2 -- required if you want to host for the web via python2 </dd>
    <dd style='color:red'> docker -- required if you want to host for the web via docker</dd>
<dl>

To build a Visual Studios project (the .vcxproj file will be placed in the sdl2-emscripten-project-template/build folder)

```
cmake . -B build
```
    
To build a release on OSX or MinGW (if using ```-G "MinGW Makefiles"```):

```
cmake . -B build
make
```

To build for browser with Emscripten (requires emscripten installed and on the path): 

```
emcmake cmake . -B build 
 
cd build && make
```

To build with debug symbols (on OSX):
```
cmake -DCMAKE_BUILD_TYPE=Debug . -B build
make
```

<div style='color:red'> The 'resources' folder needs to exist in the same directory as the .exe file (on OSX it will be automatically bundled into the app</div>

## Debugging
    
This project comes with a .vscode folder prebundled to make debugging easier, for this to work two plugins are necessary 

<dl>
    <dt> Recommended Plugins<dt>
    <dd style='color:green'>C/C++ Plugin </dd>
    <dd style='color:green'>CodeLLDB* </dd>
<dl>
    
*CodeLLDB is only recommended for debugging on modern OSX versions

## Building Manually    
    
Emscripten command (manually):
    
```
emcc src/main.cpp -O3 -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\",\"jpg\"]' -s USE_SDL_MIXER=2 -s USE_FREETYPE=1 -s ALLOW_MEMORY_GROWTH=1 --preload-file resources/
```

Running in small httpserver with Python 2: 
    ```python -m SimpleHTTPServer 8080``` 

## Building and hosting on the web
 
_This will create a make file and copy a basic index.html and python script to the embuild folder_
``` 
emcmake cmake -B embuild . 
cd embuild && make
``` 
Serving the file using httpserver with Python 2: ```python -m SimpleHTTPServer 8080``` 

## Hosting with docker  
### Building the image 
_The emscripten build must me run first_

```
emcmake cmake -B embuild . 
cd embuild && make
docker build -t <desired_image_name> .
``` 
 
### Running the image
```
docker run --name <desired_container_name> -p <desired_port>:3000 <desired_image_name> 
```

You will then be able to view the application on ```http://localhost:<desired_port>``` i.e http://localhost:3000
 

## Attributions 
SDL2 can be found https://www.libsdl.org/

Art By: Brandon

Background Found here: https://wallpaperaccess.com/pixel-city

Music By: https://soundcloud.com/victor-bui-trong 
Collision sound: https://freesound.org/people/JustInvoke/sounds/446125/ 
Jump sound: https://freesound.org/people/elektroproleter/sounds/157568/
