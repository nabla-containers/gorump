all: hello.bin
xen: hello-xen.bin

%.a: %.go
	CC=${RUMPRUN_CC} CGO_ENABLED=1 GOOS=rumprun ../../go1.5/bin/go build -buildmode=c-archive -v -a -x $<

%.pseudo: %.a
	RUMPRUN_STUBLINK=succeed ${RUMPRUN_CC} -g -o $@ $(basename $@).c $<

%.bin: %.pseudo
	${RUMPRUN_BAKE} hw_virtio $@ $<

%.spt: %.pseudo
	${RUMPRUN_BAKE} solo5_spt $@ $<

%-xen.bin: %.pseudo
	${RUMPRUN_BAKE} xen_pv $@ $<

clean:
	rm -f hello*.a hello*.h hello hello-xen hello*.bin *.spt
