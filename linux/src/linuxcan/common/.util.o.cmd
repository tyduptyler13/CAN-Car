cmd_/home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/util.o := gcc -Wp,-MD,/home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/.util.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/4.8/include  -I/usr/src/linux-headers-3.13.0-24-generic/arch/x86/include -Iarch/x86/include/generated  -Iinclude -I/usr/src/linux-headers-3.13.0-24-generic/arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I/usr/src/linux-headers-3.13.0-24-generic/include/uapi -Iinclude/generated/uapi -include /usr/src/linux-headers-3.13.0-24-generic/include/linux/kconfig.h -Iubuntu/include  -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -m64 -mno-mmx -mno-sse -mpreferred-stack-boundary=3 -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -maccumulate-outgoing-args -fstack-protector -DCONFIG_X86_X32_ABI -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_FXSAVEQ=1 -DCONFIG_AS_AVX=1 -DCONFIG_AS_AVX2=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -pg -mfentry -DCC_USING_FENTRY -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -DCC_HAVE_ASM_GOTO -DLINUX=1 -D_LINUX=1 -I/home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../include/ -D_DEBUG=0 -DDEBUG=0 -DWIN32=0  -DMODULE  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(util)"  -D"KBUILD_MODNAME=KBUILD_STR(kvpcican)" -c -o /home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/.tmp_util.o /home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/util.c

source_/home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/util.o := /home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/util.c

deps_/home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/util.o := \
  /usr/src/linux-headers-3.13.0-24-generic/arch/x86/include/asm/div64.h \
    $(wildcard include/config/x86/32.h) \
  include/asm-generic/div64.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  include/uapi/linux/types.h \
  /usr/src/linux-headers-3.13.0-24-generic/arch/x86/include/uapi/asm/types.h \
  /usr/src/linux-headers-3.13.0-24-generic/include/uapi/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  /usr/src/linux-headers-3.13.0-24-generic/arch/x86/include/uapi/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  /usr/src/linux-headers-3.13.0-24-generic/include/uapi/linux/posix_types.h \
  include/linux/stddef.h \
  include/uapi/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /usr/src/linux-headers-3.13.0-24-generic/arch/x86/include/asm/posix_types.h \
  /usr/src/linux-headers-3.13.0-24-generic/arch/x86/include/uapi/asm/posix_types_64.h \
  /usr/src/linux-headers-3.13.0-24-generic/include/uapi/asm-generic/posix_types.h \
  /home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../include/util.h \

/home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/util.o: $(deps_/home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/util.o)

$(deps_/home/tyler/git/CAN-Car/linux/src/linuxcan/pcican/../common/util.o):
