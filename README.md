# MyVoxController
Interact with the particles on the screen by whistling into the app.

Run the program on Mac (microphone input is assumed to be on deviceId[0]): Download an open the following file.
https://github.com/avroshk/MyVoxController/blob/master/apps/myApps/myVoxControllerGame/bin/myVoxControllerGameDebug.app/Contents/MacOS/myVoxControllerGameDebug 

**Platform**

<p>I chose <a href="http://openframeworks.cc/documentation/">openframeworks</a> platform to implement the vocal controlled game. It has a comprehensive wrapper over OpenGL. For me it was the perfect platform to implement graphics and audio in C++.</p>

**Source Code** <a href="https://github.com/avroshk/MyVoxController/tree/master/apps/myApps/myVoxControllerGame/src">Click here</a>

**Architecture**

myFeatures ->  main  <-ofApp (Openframeworks flow) <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ^  <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |  <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;myReadAudio 



