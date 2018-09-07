# Indoor WLAN postioning system based on WiFi Fingerprinting using ESP8266
A system that tracking mobile devices in an indoor environment. The system is based on the WiFi radiation of the mobile device, so there is no need for an additional software to be installed on that device. Once the device is connecting to the WiFi hotspot, the system will estimate it's location.

## Suggested Applications:
 • Tracking people: by tracking thier mobile phone scince they connect to a WLAN network in that indoor environment.
 
 • Approve connection requests: when people in cafes trying to connect to the cafe's WLAN, it much easier if the approval of the requests was depend on thier location (if they are inside cafe or not) in comparison with setting password.
 
 • Information services: information that depend on customers location, like guiding notifications in a theater.
 
 • Markiting: advertisements that depend on person location.
 
 • Social networking and entertainment.

## Preparing Area
the system is uses the two-dimensional Cartesian coordinate system. That mean that the movements of the targated mobile device must be within one floor area. No matter if the stations was not fixed on the same level of the mobile device, but the stations should be fixed in a manner that ensure that each point on the plane of mobile device movements can cover n stations (n=4 for accurecy~1m).
