##  Project udp-test

### Testing udp connection in ESP32 and ESP8266

For testing using as client a PC with Linux, you must copy following scripts to a directory in path.
The scripts are in directory *scripts* and the names and functions are following

##### clsend:
Sends an string as argument to script that server interprets as a key: if string is *geheim* then server answers else remains silent.
Contents of clsend:

~~~

#!/bin/bash
# clsend
echo -n $1 >/dev/udp/192.168.0.59/4444

~~~

Server address in script must be edited to that of server in ESP32 or ESP8266
4444 is port on server as stated in *platformio.ini*

##### clrcv:
Receives answer from server in key accepted; once invoked, remain listening to all answers
Contents of clrcv

~~~

#!/bin/bash
# clrcv
nc -ul 9999

~~~

9999 is port on client as stated in *platformio.ini* only when DEBUG=1

### To set in platformio.ini

In this file, under *env* are build flags that must be set

Here are they:

~~~

    -DDEBUG=1
    -DLOCAL_PORT=4444
    -DREMOTE_PORT=9999
    -DMY_SSID=\xxxxxxxxxx\"
    -DMY_PWD=\"yyyyyyyyyyyy\"

~~~

DEBUG: must be in 1
LOCAL\_PORT and REMOTE\_PORT as stated
MY\_SSID and MY\_PWD must be set according to user WiFi

### How to test

#####   In ESP32 and ESP8266

- Set target in *platformio.ini*
- Verify that DEBUG=1
- Compile
- Load
- Show serial monitor
- Reset target
- Note IP address of target

#####   scripts

- Change script *clsend* to reflect IP address of target (server)
- Copy both scripts to a directory in the search path
- Verify that both scripts has execute permissions: if not then
    - cd to the directory where the scripts where copied
    - make following commands

~~~
chmod +x clsend
chmod +x clrcv
~~~

#####   Test

You must have the server program with the serial monitor running

Open a terminal screen and do the following command
This command will permit seeing the response from server; it will be waiting for each response

~~~
clrcv
~~~

Open another terminal and send this command:

~~~
clsend geheim
~~~

You must see something like this in the terminal where clrcv is running

~~~
$ Seconds since boot: 645
~~~

The line is the response from server

Now test with a bad key:

~~~
clsend bad
~~~

There will be no response from server
Also, all of these traffic more detailed will be seen in the serial monitor on server


