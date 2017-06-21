#ApacheTop

>ApacheTop watches a logfile generated by Apache (in standard common or
>combined logformat, and generates human-parsable output in realtime.

>See the INSTALL file for ./configure options (there's a few newly added
>since v0.11)

##Installation

```
git clone https://github.com/w169q169/apachetop
cd apachetop
./autogen.sh
./configure
make && make install
```

## Options

Several commandline options dictate some of its' behaviour:
```
-f logfile
	Select which file to watch.
	Specify this option multiple times to watch multiple files

-H hits | -T time
	These options are mutually exclusive. Specify only one, if any at
	all. They work as follows. ApacheTop maintains a table of
	information internally containing all the relevant information about
	the hits it's seen. This table can only be a finite size, so you
	need to decide how big it's going to be. You have two options.
	You can either:
		Use -H to say "remember <this many> hits"
	or	Use -T to say "remember all hits in <this many> seconds"
	
	The default (at the moment) is to remember hits for 30 seconds.
	Setting this too large (whichever option you choose) will cause
	ApacheTop to use more memory and more CPU time. My experimentation
	finds that remembering no more than around 5000 requests works well.

-q
	Instructs ApacheTop to keep the querystrings, not remove them

-Q          
	filter query strings, such as 'actid,action', will get '/xx?actid=aa&action=bb'

-l
	Instructs ApacheTop to lowercase all URLs, thus /FOO and /foo are
	treated as the same and accumulate the same statistics.

-r
	Enable resolving of hosts/ips (you need adns!)

-s segments
	Instructs ApacheTop to only keep the first <segments> parts of the
	path. Trailing slashes are kept if present. Statistics are then
	merged for each truncated url.
	This is easiest to demonstrate with examples:
	-s 2 would produce the following:
	/media/x.jpg               ->  /media/x.jpg
	/media/images/x.jpg        ->  /media/images/
	/media/images/small/x.jpg  ->  /media/images/
	/media/images/big/x.jpg    ->  /media/images/
	Stats for the last three URLs would be merged in this case.

-p
	Instructs ApacheTop to keep the protocol (http:// usually) at the
	front of its' referrer strings. Normal behaviour is to remove them
	to give more room to more useful information.

-d secs
	Set default refresh delay, in seconds.
```

##Usage

Once it's running, you'll see a display like this:
```
last hit: 09:17:07        atop runtime:  0 days, 00:58:20              09:17:08
All:       638924 reqs ( 182.65/sec)      3433539K ( 981.6K/sec)  (   5.4K/req)
2xx:  455415 (71.3%) 3xx:  175745 (27.5%) 4xx:  7746 ( 1.2%) 5xx:    10 ( 0.0%)
R ( 30s):    5195 reqs ( 173.17/sec)        25405K ( 846.8K/sec)  (   4.9K/req)
2xx:    3447 (66.4%) 3xx:    1715 (33.0%) 4xx:    33 ( 0.6%) 5xx:     0 ( 0.0%)
                                                                               
 REQS REQ/S    KB  KB/S URL                                                    
  103   3.4  2983  99.4 /                                 
   56   1.9   239   8.0 /tickerdata/story2.dat
   47   1.6   104   3.6 /home/today/patina.js
   44   1.5    82   2.8 /home/styles/home_d0e2ee.css
<snip>
```