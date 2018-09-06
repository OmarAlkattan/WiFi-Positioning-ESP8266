## Work Plan
The server is prepared to perform the steps of the location technique and setup the connection with stations in order to get rssi value for a certain point from each station. 
Actually we can divide the server tasks into three main functions:
  - Building the rssi database of reference points (this task is performed only one time).
  - Estimate mobile device location by WkNN algorithm.
  - Receiving rssi values of a certain point from all stations.

When the server starts at the first time, it begins building the rssi database for one time. So it takes the rssi values of the first receiving point  as the first reference point with location of (x=0,y=0).  In order to build the database, the indoor area should be divided into rectangular grid of reference points. the server 
