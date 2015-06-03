SparkfunDataClient
==================
Version: 1.00

 Author: Vassilis Serasidis
 Home: www.serasidis.gr
 email: avrtsite@yahoo.gr

This sketch uses the UIPEthernet library (ENC28J60 ethernet shield). You can use the W5100 ethernet shield just by changing the line:

```#include <UIPEthernet.h>```
to
```#include <Ethernet.h>```
 
- Create your own data stream (https://data.sparkfun.com)
- You can mark your data as public or private during the data stream creation.
- Replace PUBLIC_KEY and PRIVATE_KEY with those sparkfun gave you
- Replace the data names "humidity", "maxTemp" etc on sendToSparkfunDataServer() with those you
  set to sparkfun data stream creation.
- You can view online or download your data as CSV or JSON file via 
  
  ```https://data.sparkfun.com/streams/ + YOUR_PUBLIC_KEY```

Send an example data stream with values 25.81, 26.94 and 14.48.
  ```GET /input/WGGWNZLKGOFAzyLwLOzQ?private_key=XRRmzj9YR2iXzjnKn6zR&humidity=25.81&maxTemp=26.94&nowTemp=14.48```
  
View the example data stream on web browser
  https://data.sparkfun.com/streams/WGGWNZLKGOFAzyLwLOzQ
  
