all: hello.bin
xen: hello-xen.bin

%.a: %.go
	CC=x86_64-rumprun-netbsd-gcc CGO_ENABLED=1 GOOS=rumprun ../../go/bin/go build -buildmode=c-archive -v -a -x hello.go another.go

%.pseudo: %.a
	RUMPRUN_STUBLINK=succeed x86_64-rumprun-netbsd-gcc -g -o $@ $(basename $@).c $<

%.bin: %.pseudo
	rumprun-bake hw_virtio $@ $<

%-xen.bin: %.pseudo
	rumprun-bake xen_pv $@ $<

clean:
	rm -f hello*.a hello*.h hello hello-xen hello*.bin another*.a another*.h