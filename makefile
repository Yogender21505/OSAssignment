pthread:
	@gcc pthread.c -o pt -lpthread
	@./pt
clear_files:
	@rm pt
