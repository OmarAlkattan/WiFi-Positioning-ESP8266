<p align="center">
  <img src="https://raw.githubusercontent.com/OmarAlkattan/WiFi-Positioning-ESP8266/master/Station/station.jpg" />
</p>

##Work Plan
There are two main roles that each station performing them sequentially. the first role is sniffing the target mobile device Wi-Fi packets, and the second role is sending the mean rssi value of that packets to the Server. It's very important that all stations start the sniffing role simultaneously in each time they perform this role, in order to pick packets at all stations for the same location point, and estimate mobile locations at equal intervals.

In the sniffing role each station will pick only the data packets that transmitted from mobile device to a specific AP.

The stations should be placed in a form that commensurate with work area.
