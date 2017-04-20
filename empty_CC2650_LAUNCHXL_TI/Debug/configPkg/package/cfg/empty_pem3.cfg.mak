# invoke SourceDir generated makefile for empty.pem3
empty.pem3: .libraries,empty.pem3
.libraries,empty.pem3: package/cfg/empty_pem3.xdl
	$(MAKE) -f /Users/clayton/workspace_v7/empty_CC2650_LAUNCHXL_TI/src/makefile.libs

clean::
	$(MAKE) -f /Users/clayton/workspace_v7/empty_CC2650_LAUNCHXL_TI/src/makefile.libs clean

