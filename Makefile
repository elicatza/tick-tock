PROGRAM=tick-tock
DESTDIR=/usr/local/bin


install:
	chmod 755 $(PROGRAM)
	mkdir -p $(DESTDIR)
	cp $(PROGRAM) $(DESTDIR)/$(PROGRAM)

uninstall:
	rm -f $(DESTDIR)/$(PROGRAM)


.PHONY: install uninstall 
