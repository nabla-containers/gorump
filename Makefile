# Copyright (c) 2018 Contributors as noted in the AUTHORS file
#
# Permission to use, copy, modify, and/or distribute this software
# for any purpose with or without fee is hereby granted, provided
# that the above copyright notice and this permission notice appear
# in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
# WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
# AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
# CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
# OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

SHELL := /bin/bash

export TOP=$(abspath .)
all: gorump_stamp

GORUMP=$(TOP)
GOBASE=$(TOP)
GOBOOTSTRAP=$(TOP)/gobootstrap
export GOROOT=$(GOBOOTSTRAP)
unexport GOPATH
unexport GOBIN

FILES=\
Makefile \

gobootstrap_stamp:
	rm -rf $(GOBOOTSTRAP)
	mkdir $(GOBOOTSTRAP)
	curl -L https://storage.googleapis.com/golang/go1.6.2.linux-amd64.tar.gz | tar xz -C $(GOBOOTSTRAP) --strip-components=1
	touch $@

gorump_stamp: gobootstrap_stamp
	cd $(GORUMP)/go/src && CGO_ENABLED=0 GOROOT_BOOTSTRAP=$(GOBOOTSTRAP) GOOS=rumprun GOARCH=amd64 ./make.bash && cd $(GOBASE)
	cp -r $(GORUMP)/go1.5 gorump
	cp $(GORUMP)/go1.5/bin/go go
	touch $@

clean:
	rm -rf gobootstrap gorump rumprun-solo5 *_stamp

distclean: clean rumprun-clean
