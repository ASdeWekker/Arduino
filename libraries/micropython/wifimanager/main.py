import wifimgr

wlan = wifimgr.get_connection()

if wlan is None:
    print("Could not initialize the network connection.")
    while True:
        pass  # you shall not pass :D

print("ESP OK")
