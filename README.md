# MyVoxController
Interact with the particles on the screen by whistling into the app.

Run the program on Mac (microphone input is assumed to be on deviceId[0]): Download an open the following file.
https://github.com/avroshk/MyVoxController/blob/master/apps/myApps/myVoxControllerGame/bin/myVoxControllerGameDebug.app/Contents/MacOS/myVoxControllerGameDebug 

**Platform**

<p>I chose <a href="http://openframeworks.cc/documentation/">openframeworks</a> platform to implement the vocal controlled game. It has a comprehensive wrapper over OpenGL. For me it was the perfect platform to implement graphics and audio in C++.</p>

**Source Code** <a href="https://github.com/avroshk/MyVoxController/tree/master/apps/myApps/myVoxControllerGame/src">Click here</a>

**Architecture**

myFeatures ->  main  <-ofApp (Openframeworks flow) <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ^  <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |  <br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;myReadAudio 

<p>myReadAudio: reads audio using RtAudio wrapper exposed by openframeworks. I have a property called "overlapMultiple=4" which is used to create overlapped blocks before sending it for processing to "myFeatures". blockAndProcessAudio() collects 4 blocks of data and then shifts 1 block with every new block received before sending it to process that extracts features.</p>

<p>myFeatures: I designed myFeatures as a class that receives a block of audio, calculates pectral features and exposes get methods to access them. I have implmented various spectral features but I am only using the pitchchroma in the gameplay.</p>

<p>ofApp: this class exposes the lifecycle of the app. I am using an openframeworks add-on (external packages in openframeworks are called add-ons) called ofxLiquidFun to create a box2D object to draw bricks, circles and particles. I poll for the calculated pitchchroma in the update function.</p>

**Gameplay**

<p>I ran out of time before I could implement a gameplay that makes sense. The game lacks an objective or a scoring mechanisn. Currently, you can see a bar graph of the pitch chroma that you can control by whistling into the app. Whistling a pitch starts dropping objects at a location. You can control where the objects is dropped by changing the pitch.</p>







