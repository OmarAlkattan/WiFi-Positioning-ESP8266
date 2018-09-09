# Indoor WLAN postioning system based on WiFi Fingerprinting using ESP8266
A system that tracking mobile devices in an indoor environment. The system is based on the WiFi radiation of the mobile device, so there is no need for an additional software to be installed on that device. Once the device is connecting to the WiFi hotspot, the system will estimate it's location.

## Suggested Applications:
 • Tracking people: by tracking thier mobile phone scince they connect to a WLAN network in that indoor environment.
 
 • Approve connection requests: when people in cafes trying to connect to the cafe's WLAN, it much easier if the approval of the requests was depend on thier location (if they are inside cafe or not) in comparison with setting password.
 
 • Information services: information that depend on customers location, like guiding notifications in a theater.
 
 • Markiting: advertisements that depend on person location.
 
 • Social networking and entertainment.

## System Setup:

  ### 1) Preparing Area:
  The system is uses the two-dimensional Cartesian coordinate system. That mean that the movements of the targated mobile device must be within one floor area. No matter if the stations was not fixed on the same plane level of the mobile device, but they should be fixed in a manner that ensure that each point on the plane of mobile device movements can cover a number of stations (4 stations for accurecy within ~0.8m).
When the system is running for the first time, it's start with training mode and expecting you to start train it on fixed points. The locations of the training points should be already determined in the system before training.
Before starting we have to divide area into rectangular gird. The intersections of this grid must divid it into squares, and they represents the training points.


  ### 2) Setting Keys:
  After preparing the area, we have to set the main keys of the system. These keys are concerned with the performance of the system and comes as follow:
   #### Keys at server:
     STATIONS_NUM: Number of total stations.
     REFERENCES_NUM: Number of total training points (grid intersections).
     REFERENCES_NUM_ON_X: Number of training points on x axis.
     REFERENCES_NUM_ON_Y: Number of training points on y axis.     
     REFERENCES_SAMPLING_STEP: The distance between two adjacent points on the grid (float number must be greater than ~1.5m to avoid proximity errors).
     ELECTED_REFERENCE_POINTS: the k factor of estimation algorithm (WkNN algoritm).
   #### Keys at stations:
     STATION_ID: Unique number for each station (1 -> STATION_NUM).
     TIME_INTERVAL: The interval before re-discover the new location of the target (it must be one value in all stations and great enough to ensure that all stations completed their previous session).
