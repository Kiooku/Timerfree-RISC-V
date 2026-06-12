# README: Building Sender/Receiver Covert Channel for RISC-V using RAVEN (gem5-based simulator) and C910 RISC-V board

This project includes two programs:

* sender
* receiver

and a header file shared.h

Compilation depends on the hardware/ISA features of the target platform.

# 1. Building on gem5 (Full-System RISC-V)

### Use Zicbom + Zicbop extensions

gem5’s RISC-V FS CPU models implement standard cache-block operations:

* `cbo.flush`(Zicbom)
* `prefetch.r / prefetch.w` (Zicbop)

### Compile with:

```
/opt/riscv/bin/riscv64-unknown-linux-gnu-gcc \
    -march=rv64gc_zicbom_zicbop \
    -S sender.c -o sender.s -static -pthread

/opt/riscv/bin/riscv64-unknown-linux-gnu-gcc \
    -march=rv64gc_zicbom_zicbop \
    -S receiver.c -o receiver.s -static -pthread
```

This enables the native RISC-V standard instructions:

* `prefetch.w`
* `cbo.flush`

The code in `shared.h` will automatically select the correct instruction sequence.

# 2. Running on gem5

Place `sender` and `receiver` inside the simulated FS root filesystem.

Boot into the system, then run:

./receiver &
./sender

# 3. Building on C910 (BeagleV-Ahead RISC-V Board) (use ifconfig to know ip address)

The C910 does not support Zicbom or Zicbop.
Instead, it uses T-Head custom cache operations:

* `DCACHE.CIVA` (invalidate/flush VA)
* `ICACHE.IVA`
* Prefetch = “trigger HW prefetch by performing an= load operation ld”

Your code must use the C910 mode in `shared.h`:

### Compile with:

<!-- ```
gcc \
    -DC910 -march=rv64gc \
    -S sender.c -o sender.s -static -pthread

gcc \
    -DC910 -march=rv64gc \
    -S receiver.c -o receiver.s -static -pthread
``` -->
gcc \
    -DC910 -march=rv64gc \
    sender.c -o sender -static -pthread

gcc \
    -DC910 -march=rv64gc \
    receiver.c -o receiver -static -pthread

`-DC910` activates the following behaviors in `shared.h`:

* `prefetch_w_ptr()` → has `ld` (prefetch emulation)
* `cbo_flush_ptr()` → has `.long 0x278800b` (DCACHE.CIVA)
* `iflush()` → has `.long 0x308800b` (ICACHE.IVA)

# 4. Running on C910 (BeagleV-Ahead)

Copy both binaries to the board:
<!-- 
```
scp sender receiver root@beaglev.local:/root/
``` -->

pkill receiver 2>/dev/null
pkill sender 2>/dev/null
rm /dev/shm/prefetch_cbo_shm_v2_fix 2>/dev/null
taskset -c 0 ./receiver &
sleep 0.2
taskset -c 1 ./sender (both same and different cores worked)


C910 will use the custom T-Head cache operations automatically.

# 5. Notes

* The shared memory name must match on both sides:

```
/prefetch_cbo_shm_v2_fix
```

* Both binaries must be compiled with matching ISA flags.
* For C910, never use Zicbom/Zicbop flags — it is not supported by this board.
