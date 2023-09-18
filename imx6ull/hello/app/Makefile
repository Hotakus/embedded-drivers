include ../tool_chain

APP_NAME		= "hello_test"
SRCS_ALL		= $(wildcard *.c)

build: hello_test

hello_test:
	$(CROSS_COMPILE)gcc $(SRCS_ALL) -o $(APP_NAME)

clean:
	rm -rf $(APP_NAME)

