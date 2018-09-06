## Work Plan
The server is prepared to perform the location technique implementation steps and make the connection with stations in order to get rssi information for a certain point. 
Actually we can divide the server tasks into three main functions:
  - Building the rssi database of reference point (this task is performed only one time).
  - Estimate mobile device location by WkNN algorithm.
  - Receiving rssi values of a certain point from all stations.

When the server is start at the first time, it begins building the rssi database for one time. So it takes the first receiving point data as the 1st reference point number with location of (x=0,y=0).  In order to build the database, the indoor area should be divided into rectangular grid of reference points. the server 
