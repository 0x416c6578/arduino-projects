package com.github.alex;

import org.apache.lucene.util.ThreadInterruptedException;
import org.openimaj.video.VideoDisplay;
import org.openimaj.video.capture.VideoCapture;
import org.openimaj.video.capture.VideoCaptureException;

/**
 * OpenIMAJ Hello world!
 *
 */
public class App {
    public static void main( String[] args ) {
      try {
        //Capture for 10s then exit...
        VideoCapture cap = new VideoCapture(640, 480);
        VideoDisplay.createVideoDisplay(cap);
        Thread.sleep(10000);
        cap.close();
        System.exit(0);
      } catch (VideoCaptureException e) {
        e.printStackTrace();
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
}
