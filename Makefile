chg_mac: chg_mac.c spi.img
	gcc -o $@ $<

spi.img: spi.img.tar.xz
	tar -xJf $< && touch $@

clean:
	rm -f chg_mac spi.img

