 AirportTalk

Supported filetypes:
.mp3 which is played by mpg123.  Only mp3 type streams can be played
Required Libraries -> ssl, DLiriumLib, crypto, mysqlclient

install
sudo apt-get install mpg321
sudo apt-get install openssl libssl-dev
sudo apt-get install mysql-server
sudo apt-get install mysql-client
sudo apt-get install libmysqlclient-dev


to start and stop from the run levels place musicServer.sh into /etc/init.d directory and run this command. The application will run automatically at bootup
sudo update-rc.d musicServer.sh defaults 99
to remove musicServer.sh run this command
sudo update-rc.d -f musicServer.sh remove


GCC C++ Compiler
All Options:
-I/usr/local/ssl/include -I"/home/jdellaria/workspace/DLiriumLib" -O3 -Wall -c -fmessage-length=0
Includes:
/usr/local/ssl/include
"${workspace_loc:/DLiriumLib}"

GCC C Compiler
All Options:
-O3 -Wall -c -fmessage-length=0
Includes:

GCC C++ Linker
All Options:
-L/usr/lib/mysql -L"/home/jdellaria/workspace/DLiriumLib/Release" -L/usr/local/ssl/lib
Libraries:
ssl
DLiriumLib
crypto
mysqlclient
Library search path:
/usr/lib/mysql
"${workspace_loc:/DLiriumLib/Release}"
/usr/local/ssl/lib
