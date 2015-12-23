# main: main.c capture.c process.c video.c soble.c threshold.c diff.c binary.c
# 	g++ -o main main.c capture.c process.c video.c soble.c threshold.c diff.c binary.c -I.


# clean:
# 	@echo "cleaning project"
# 	-rm main *.o
# 	@echo "clean completed"

main: main.o capture.o process.o video.o soble.o threshold.o diff.o binary.o filter.o morphology.o
	g++ main.o capture.o process.o video.o soble.o threshold.o diff.o binary.o filter.o morphology.o -o main

main.o: main.c config.h
	g++ -c main.c

capture.o: capture.c config.h
	g++ -c capture.c

process.o: process.c config.h 
	g++ -c process.c

video.o: video.c config.h
	g++ -c video.c

soble.o: soble.c config.h 
	g++ -c soble.c

threshold.o: threshold.c config.h
	g++ -c threshold.c


diff.o: diff.c config.h 
	g++ -c diff.c

binary.o: binary.c config.h 
	g++ -c binary.c

filter.o: filter.c config.h 
	g++ -c filter.c
	
morphology.o: morphology.c config.h 
	g++ -c morphology.c


clean:
	@echo "cleaning project"
	-rm main *.o
	@echo "clean completed"