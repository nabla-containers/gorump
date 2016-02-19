all: httpd.bin
xen: httpd-xen.bin

%.a: %.go
	CC=x86_64-rumprun-netbsd-gcc CGO_ENABLED=1 GOOS=rumprun ../../go/bin/go build -buildmode=c-archive -v -a -x $<

%.pseudo: %.a
	RUMPRUN_STUBLINK=succeed x86_64-rumprun-netbsd-gcc -g -o $@ $(basename $@).c $<

%.bin: %.pseudo
	rumprun-bake hw_virtio $@ $<

%-xen.bin: %.pseudo
	rumprun-bake xen_pv $@ $<

clean:
	rm -f httpd*.a httpd*.h httpd httpd-xen httpd*.bin