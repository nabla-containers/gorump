all: nanomsg.bin
spt: nanomsg.spt
hvt: nanomsg.hvt

%.a: %.go
	CC=x86_64-rumprun-netbsd-gcc CGO_ENABLED=1 GOOS=rumprun ../../go/bin/go build -buildmode=c-archive -v -a -x $<

%.pseudo: %.a
	RUMPRUN_STUBLINK=succeed x86_64-rumprun-netbsd-gcc -g -o $@ $(basename $@).c $<  -lnanomsg -L/home/ubuntu/rumprun-packages/pkgs/lib/

%.bin: %.pseudo
	rumprun-bake hw_virtio $@ $<

%.spt: %.pseudo
	rumprun-bake solo5_spt $@ $<

%.hvt: %.pseudo
	rumprun-bake solo5_hvt $@ $<

clean:
	rm -f nanomsg.a nanomsg.h nanomsg nanomsg.bin
