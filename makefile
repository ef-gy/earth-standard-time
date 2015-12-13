-include ef.gy/base.mk include/ef.gy/base.mk

NAME:=est

.third-party/libefgy/include/ef.gy/base.mk:
	mkdir .third-party || true
	cd .third-party && git clone git://github.com/ef-gy/libefgy.git

include/ef.gy/base.mk: .third-party/libefgy/include/ef.gy/base.mk
	ln -sfn ../.third-party/libefgy/include/ef.gy include/ef.gy

data/.volatile include/data/.volatile:
	mkdir -p $(dir $@)
	touch $@

data/fullmoon.htm: data/.volatile
	$(CURL) 'http://home.hiwaay.net/~krcool/Astro/moon/fullmoon.htm' -o $@

data/fullmoon: data/fullmoon.htm src/extract-plaintext.xslt
	$(TIDY) -asxhtml $< 2>/dev/null |\
		$(XSLTPROC) --novalid src/extract-plaintext.xslt - 2>/dev/null > $@

data/fullmoon.julian: data/fullmoon
	sed -E 's/.*\s+([0-9.]+)$$/\1/' $<|sort|uniq|tail -n +2>$@

data/full-moon.h: include/data/full-moon.h

include/data/full-moon.h: data/fullmoon.julian include/data/.volatile
	echo '/* automatically generated; see makefile for details */' > $@
	echo '#include <array>' >> $@
	echo 'namespace data {' >> $@
	echo 'std::array<double,$(shell wc -l < $<)> fullMoons = {' >> $@
	sed -E 's/^.*$$/\0l,/' $< >> $@
	echo '};}' >> $@
