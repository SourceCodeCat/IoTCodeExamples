#Will scan the nerby AP's  and list them along with their MAC address and Signal Quality
iwlist wlan0 scan |grep "Address\|Quality\|ESSID"
