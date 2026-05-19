all: main.c
	gcc main.c -Os -o main
	gcc main_clock_fixed.c -Os -o main_clock_fixed
	gcc main_thread.c -Os -o main_thread
	gcc main_perf_event_open.c -Os -o main_perf_event_open

clean:
	rm -f main
	rm -f main_clock_fixed
	rm -f main_thread
	rm -f main_perf_event_open
