# How to change MAC-address for classic Orange Pi 5 (not for 5+) with spi-uboot using nvme-ssd-boot

### Note1:

This scenario is only for NVME-SSD boot via spi-flash uboot-bootloader. Change_MAC does't work for microsd-boot.

### Note2: 

This manual is how to update spi-flash uboot. You can do backup copy of your spi-flash bootloader (16MB).

    $ mkdir ~/my-backup
    $ sudo dd if=/dev/mtdblock0 of=~/my-backup/original.spi

## HOWTO

Change Mac-address for classic Orange Pi 5 (Boot from nvme-ssd only. Change mac from micro-sd is not applied).

    cd ~
    git clone https://github.com/metamot/opi5_chg_mac
    cd ~/opi5_chg_mac/
    make


To see mac from file:
    
    ./chg_mac

To change mac into file:

    ./chg_mac xx:xx:xx:xx:xx:xx

For example:

    ./chg_mac f6:20:08:cd:73:6f

To update spi-flash (PLEASE BE PATIENT! This operation due 5min!):

    sudo dd if=./spi.img of=/dev/mtdblock0 bs=1M count=16 conv=notrunc

Reboot.

Check mac (see new mac-address):

    ip a

THERE ARE NO WARRANTIES!
(Used very old spi.img from official orange-pi-5 debian distro).
