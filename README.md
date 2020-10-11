# velog

## Description

Serial log application for VE.Direct devices

## Compiling

```bash
make all
make test
sudo make install
```

## Usage

```bash
velog -i /tmp/vmodem1 -o log.csv -r 1
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
