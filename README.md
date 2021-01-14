# vemon

## Description

VE.Direct serial data stream parser. Use this utility to parse and log data
from your Victron Energy devices to csv or graphite's carbon database.

This is a fork of the [velog](https://github.com/ullman/velog) project by
Henrik Ullman. After considerable re-writing, I decided to release it as a
separate project rather than merge it back upstream.

## Compiling

```bash
# apt-get install build-essential libcunit1-dev
$ make all
$ make test
# make install
```

## Usage

```bash
velog -i /dev/serial/by-id/usb-VE_Direct_cable-port0 -o log.csv -r 1
```

Required:

```bash
-i  [serial device]
```

Optional:

```bash
-o [log to file]
-r [logfile rotate cycle in days]
-g [send to graphite host]
-d [graphite device id]
```

## Contrib

see `contrib/` for example graphing setup logging data to carbon-cache and graphing with
graphite on raspberry pi.

![vemon screenshot](contrib/20201020-solar_graphs.png)

## Licence

GPL Version 3

See `COPYING` for details
