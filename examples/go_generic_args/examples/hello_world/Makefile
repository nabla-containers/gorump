seccomp: goprog.seccomp

setup: 
	cp ../../main.c .
	cp ../../gomaincaller.go .

goprog.a: $(wildcard *.go)
	CC=x86_64-rumprun-netbsd-gcc CGO_ENABLED=1 GOOS=rumprun ../../go build -buildmode=c-archive -v -a -x -o goprog.a *.go

goprog.pseudo: goprog.a
	RUMPRUN_STUBLINK=succeed x86_64-rumprun-netbsd-gcc -g -o goprog.pseudo main.c goprog.a

goprog.seccomp: setup goprog.pseudo
	rumprun-bake solo5_ukvm_seccomp goprog.seccomp goprog.pseudo

%.bin: %.pseudo
	rumprun-bake hw_virtio $@ $<

.PHONY: run
run: goprog.seccomp
	../../ukvm-bin  --disk=../../x --net=tap100 ./goprog.seccomp '{"cmdline":"./goprog.seccomp a 1 2 3 4", "net":{"if":"ukvmif0","cloner":"True","type":"inet","method":"static","addr":"10.0.0.2","mask":"16"}}'
    
clean:
	rm -f goprog.a goprog.h goprog.seccomp goprog.pseudo main.c gomaincaller.go 
