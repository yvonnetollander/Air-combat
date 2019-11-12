all:
	+$(MAKE) -C src

build-win:
	+$(MAKE) -C src $@

win:
	+$(MAKE) -C src $@

run-win:
	+$(MAKE) -C src $@

build-linux:
	+$(MAKE) -C src $@

linux:
	+$(MAKE) -C src $@

run-linux:
	+$(MAKE) -C src $@

build-wsl:
	+$(MAKE) -C src $@

wsl:
	+$(MAKE) -C src $@

run-wsl:
	+$(MAKE) -C src $@

br:
	+$(MAKE) -C src $@

build:
	+$(MAKE) -C src $@

run:
	+$(MAKE) -C src $@

clean:
	+$(MAKE) -C src $@
