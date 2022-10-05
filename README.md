# mouse-jiggler-macos

## How to build
```
g++ mouse_jiggler_macos.cpp -o mouse_jiggler_macos -framework ApplicationServices
```

## How to use
If screen saver starts after 10 mins, you can avoid it by the following.
```
./mouse_jiggler_macos -p 5 -t 300
```

* `-p` is poll[sec].
    * This application checks if the cursor has been physically moved or not every this poll [sec]. 
* `-t` is timeout[sec].
    * If the cursor has not been moved physically in timeout [sec], this application jiggles the cursor every poll [sec]. 

## Documents
[CGEventSourceCreate](https://developer.apple.com/documentation/coregraphics/1408776-cgeventsourcecreate/)
