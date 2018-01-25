
#!/bin/bash

make clean && \
	make download && \
	make pci-database && \
	make cross-compiler && \
	make all && \
	make vm-setup && \
	make test && \

exit;
