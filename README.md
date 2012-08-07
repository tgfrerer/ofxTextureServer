<pre>
     _____    ___     
    /    /   /  /     ofxTextureServer
   /  __/ * /  /__    (c) ponies & light, 2012. 
  /__/     /_____/    poniesandlight.co.uk

  ofxTextureServer
  Created by Tim Gfrerer, 2012.
  
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
</pre>

# ofxTextureServer

A garbage-collected container and (pre)loader of ofTextures.

## Motivation

ofTextureServer helps you to memory-manage ofTextures. It will keep your footprint low if you plan to work with lots of ofTextures. Use ofTextureServer to keep track of all your ofTextures, to preload whole directories of images into ofTextures, so that you you can access them instantly once your app is running, or to help you automate your texture memory management.

## Example

See included example project.

### Reference Render

![image](http://poniesandlight.co.uk/static/ofxTextureServerReference.png)

## Dependencies

♥ oF >= 0071