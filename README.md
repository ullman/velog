# velog

## Description

Serial log application for VE.Direct devices

## Compiling

```bash
make
make install
```

## Usage

velog -i /tmp/vmodem1 -o log.csv -r 1

Required:
-i  [serial device]

Optional:
-o [log to file]
-r [logfile rotate cycle in days]


## Licence

GPL Version 3

See `COPYING` for details
