#!/usr/bin/env python
import sys
import time
import os.path

def log(s):
    with open('/var/log/bar/bar.log', 'a') as f:
        print >> f, time.strftime('%Y-%m-%d %H:%M:%S'), s

if __name__ == '__main__':
    name = os.path.basename(sys.argv[0]).split('.')[0]
    log('starting ...')
    while True:
        log('working ...')
        time.sleep(1)
    log('stopping ...')
