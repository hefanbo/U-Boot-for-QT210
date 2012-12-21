#!/bin/bash
dd if=out/qt210/spl/qt210-spl.bin iflag=dsync of=/dev/sdb oflag=dsync seek=1
dd if=out/qt210/u-boot.bin iflag=dsync of=/dev/sdb oflag=dsync seek=49
