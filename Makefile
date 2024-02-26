build:
	gcc src/main.c -o bin/main -pthread -lcurl -ldiscord -I./vendor/concord/include -L./vendor/concord/lib
	DYLD_LIBRARY_PATH=vendor/concord/lib bin/main

