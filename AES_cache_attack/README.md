# AES full key recovery `Flush+Reload`

AES full key recovery of the openssl-1.1.0f T-Table implementation using timerfree methods to a `Flush+Reload` attack.

For openssl installation, you can follow the explanation from [`nepoche` repository](https://github.com/nepoche/Flush-Reload#openssl-installation).

# Run

```
# AES Flush+Reload using rdcycle
g++ newspy.cpp -o newspy -I/home/beagle/path_to/openssl-install/include -L/home/beagle/path_to/openssl-install/lib -lcrypto

# AES Flush+Reload using clock_timer
g++ newspy_clock_timer.cpp -o newspy_clock_timer -I/home/beagle/path_to/openssl-install/include -L/home/beagle/path_to/openssl-install/lib -lcrypto

# AES Flush+Reload using thread counter
g++ newspy_timerless.cpp -o newspy_timerless -I/home/beagle/path_to/openssl-install/include -L/home/beagle/path_to/openssl-install/lib -lcrypto

# AES Flush+Reload using perf_event_open
g++ newspy_perf_event_open.cpp -o newspy_perf_event_open -I/home/beagle/path_to/openssl-install/include -L/home/beagle/path_to/openssl-install/lib -lcrypto
```

# Tested on

C910
