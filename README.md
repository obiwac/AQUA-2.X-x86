
# AQUA-2.X-x86
### This is the repository for the AQUA 2.X x86 kernel

## How to run (Linux)
#### First, download this repository with

```bash
$ git clone https://github.com/obiwac/AQUA-2.X-x86
$ cd AQUA-2.X-x86
```

#### The first and simplest way of compiling everything and setting up a cross-compiler, VM, etc. is to run

```bash
$ make auto
```

#### although it is ill-advised as it takes alot of time and will probably download and setup things you will most likely never need. The best way of building AQUA is described below:

##### Make sure that you have all the requiered dependencies by running

```bash
$ make download
```

###### **NOTE** This uses `apt` to install the packages so it will only work on Debian/Ubuntu based systems.
##### Then, build it with

```bash
$ make all
```

##### This will build it with an `i686-elf` cross compiler if you have one (if not you can automatically compile it with `$ make cross-compiler`), but will instead compile with `gcc -m32` if it doesn't detect it.
##### Then you can setup your Virtual Box VM or what not with the aqua.iso in aqua/.

##### You can automatically create a Virtual Box VM by running

```bash
$ make vm-setup
```

##### And you can then run it with

```bash
$ make test
```

###### **NOTE**: If AQUA boots up in text mode, change line 14 in file `src/asm/kernel.asm` from

```x86asm
MB_TEXT_MODE equ 1
```

###### to

```x86asm
MB_TEXT_MODE equ 0
```

##### If you ever discover a bug, run

```bash
$ make bug
```

##### This will create a `bug_report.zip` file with some useful diagnostic information (compiler, date, logs, ...) Send the resulting file to the #support channel on my discord (https://discord.gg/ac3mX7u)
##### If you want to build AQUA with the PCI database, run

```bash
$ make pci-database
```

##### to download the latest PCI-ID and create a database.
##### If you want to flash AQUA to a USB drive, run

```bash
$ make flash
```

##### This will flash AQUA to `/dev/sdb`.
###### **WARNING**: This uses the `dd` command which can be very dangerous if used incorrectly. It is strongly ill-advised to run the above command.

## Minimum / recommended Virtual Box VM specs

| Specification  | Minimum       | Recommended    |
| -------------- | -------------:| --------------:|
| RAM            | 512 MB        | 1024 MB        |
| VRAM           | 9 MB          | 12 MB          |
| Virtualization | VT-x / AMD-v  | VT-x / AMD-v   |
| Storage        | 2 GB          | 2 GB           |
| Audio          | ICH AC97      | Intel HD Audio |
| Networking     | RTL8139       | Intel i217     |

###### **NOTE** the "minimum" specs are not necessarily the *bare* minimum but are the minimum you will need if you want to be future-proof.
###### Some of these recommended features are not even partially or fully implemented yet.
