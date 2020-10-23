## Install graphite-carbon for storing your data.

    sudo apt-get install graphite-carbon

## Install graphite-web, grafana, or some other tool for displaying your data.

See `graphite-dashboard-power.json` for example power dashboard based on my
setup.

    sudo apt-get install apache2 libapache2-mod-wsgi-py3 graphite-web

## Setup udev rules for manging serial devices

These rules setup symlinks for each device based on the physical port that each
usb device is plugged into. Modify symbolic names and device paths for your
setup.

    sudo cp 10-vedirect.rules /etc/udev/rules.d/
    sudo udevadm control --reload-rules && sudo udevadm trigger

## Install systemd services

These systemd service definitions are examples based on the serial devices
above. Modify for your setup.

    sudo cp velog-*.service /etc/systemd/system/
    sudo systemctl enable velog-bmv velog-inverter velog-mppt1 velog-mppt2 velog-mppt2 velog-mppt3
    sudo systemctl start velog-bmv velog-inverter velog-mppt1 velog-mppt2 velog-mppt2 velog-mppt3
