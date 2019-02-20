include ${RUMPRUN_MKCONF}

spt: goprog.spt

ifeq ($(RUMPRUN_CC),)
$(error Please run: source rumprun/obj/config)
endif

setup: 
	cp ../../main.c .
	cp ../../gomaincaller.go .

goprog.a: $(wildcard *.go)
	CC=${RUMPRUN_CC} CGO_ENABLED=1 GOOS=rumprun ../../../../go1.5/bin/go build -buildmode=c-archive -v -a -x -o goprog.a *.go

goprog.pseudo: goprog.a
	RUMPRUN_STUBLINK=succeed ${RUMPRUN_CC} -g -o goprog.pseudo main.c goprog.a

goprog.spt: setup goprog.pseudo
	${RUMPRUN_BAKE} solo5_spt goprog.spt goprog.pseudo

%.bin: %.pseudo
	rumprun-bake hw_virtio $@ $<

.PHONY: run
run: goprog.spt
	${SOLO5SRC}/tenders/spt/solo5-spt --net=tap100 $< '{"cmdline":"$< a 1 2 3 4", "net":{"if":"ukvmif0","cloner":"True","type":"inet","method":"static","addr":"10.0.0.2","mask":"16"}}'
    
clean:
	rm -f goprog.a goprog.h goprog.spt goprog.pseudo main.c gomaincaller.go 
