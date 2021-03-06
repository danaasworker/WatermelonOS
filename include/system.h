#ifndef SYSTEM_H
#define SYSTEM_H

#include <kernel.h>
#include <system/datatype.h>
#include <system/info.h>
#include <system/string.h>
#include <system/math.h>
#include <system/cli.h>
#include <system/memory.h>
#include <system/io.h>
#include <drivers/graphics.h>
#include <init/gdt.h>
#include <init/idt.h>
#include <init/isr.h>
#include <init/irq.h>
#include <init/syscalls.h>
#include <system/machine.h>
#include <system/app.h>
#include <system/resources.h>
#include <drivers/mouse.h>
#include <drivers/pit.h>
#include <drivers/keyboard.h>
#include <gui/button.h>
#include <gui/textfield.h>
#include <drivers/pci.h>
#include <system/notification.h>
#include <drivers/audio.h>
#include <drivers/audio/intel_hda.h>
#include <drivers/ide.h>
#include <drivers/storage.h>
#include <drivers/storage/harddisk.h>
#include <drivers/storage/cdrom.h>
#include <system/broadcast.h>
#include <fs/fat32.h>
#include <fs/fat16.h>
#include <fs/fat12.h>
#include <fs/ext2.h>
#include <drivers/cmos.h>
#include <system/time.h>

#endif
