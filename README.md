# velog

## Description

Serial log application for VE.Direct devices

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
```

## Licence

GPL Version 3

See `COPYING` for details
