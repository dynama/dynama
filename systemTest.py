import math, os, sys, subprocess, random, logging, datetime, time, sqlite3

#Array of websites that are pinged at random
websites = ["www.google.com", "www.facebook.com", "www.reddit.com", 
			"www.craigslist.com", "www.iwastesomuchtime.com", "www.secdev.org", 
			"www.stackoverflow.com", "www.apple.com", "www.reddit.com", 
			"www.grooveshark.com", "www.python.org", "www.youtube.com",
			"www.yahoo.com", "wallbase.cc", "www.bing.com", 
			"www.amazon.com", "www.twitter.com", "www.mozilla.com"]

#Initialize logging
# LOG_FILENAME = 'ping_log.log'
# logging.basicConfig(filename=LOG_FILENAME, level=logging.DEBUG)

#take in command line arguments
#num_pings = sys.argv[1]
num_pings = 5
null = open('/dev/null', 'w')

def test():
	os.remove('database.sqlite3')
	time.sleep(2)
	subprocess.Popen('./zombie_watch')
	time.sleep(3)
	DNS_Traffic()

def DNS_Traffic():
	count = 1
	conn = sqlite3.connect('database.sqlite3')
	c = conn.cursor()
	c.execute('SELECT COUNT(*) FROM dnsPacket')
	baseNumPackets = c.fetchone()[0]
	conn.close()
	while (count < int(num_pings)+1):
		# now = datetime.datetime.now()
		# x = random.randint(1,17)
		subprocess.Popen('ping -c 1 -q -q google.com', shell=True, stdout=null)#+ websites[x], shell=True)
		# logging.debug(now.strftime("%Y-%m-%d %H:%M:%S ") + websites[x])	
		time.sleep(1)
		checkDatabase(count + baseNumPackets)
		count = count + 1

def checkDatabase(expectedNumCollectedPackets):
	conn = sqlite3.connect('database.sqlite3')
	c = conn.cursor()
	c.execute('SELECT COUNT(*) FROM dnsPacket')
	numCollectedPackets = c.fetchone()[0]
	if numCollectedPackets == expectedNumCollectedPackets*2:
		print 'Test ' + str(expectedNumCollectedPackets) + ' passed.'
	else:
		print 'Test ' + str(expectedNumCollectedPackets) + ' FAILED.'
		print 'Expected ' + str(expectedNumCollectedPackets*2) + ' packets, found ' + str(numCollectedPackets)
	conn.close()


test()