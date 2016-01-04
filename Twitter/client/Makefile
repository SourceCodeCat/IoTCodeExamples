all: javasocketclient/JavaSocketClient.class

javasocketclient/JavaSocketClient.class:
	javac javasocketclient/JavaSocketClient.java
	echo 'java -cp . javasocketclient.JavaSocketClient $$1 $$2 "$$3"' > GoClient
	chmod +x GoClient
	echo "READY!!.."

clean:
	rm javasocketclient/*.class GoClient
