exe = time ./partition
test = ../verifier/verify
comp = g++ -o partition main.cpp -O3
cell1 = ../testcases/p2-1.cells
cell2 = ../testcases/p2-2.cells
cell3 = ../testcases/p2-3.cells
nets1 = ../testcases/p2-1.nets
nets2 = ../testcases/p2-2.nets
nets3 = ../testcases/p2-3.nets
out1 = ../output/p2-1.out
out2 = ../output/p2-2.out
out3 = ../output/p2-3.out

all:
	$(comp)
p2-1:
	$(exe) $(cell1) $(nets1) $(out1)
p2-2:
	$(exe) $(cell2) $(nets2) $(out2)
p2-3:
	$(exe) $(cell3) $(nets3) $(out3)
testp2-1:
	$(test) $(nets1) $(cell1) $(out1)
testp2-2:
	$(test) $(nets2) $(cell2) $(out2)
testp2-3:
	$(test) $(nets3) $(cell3) $(out3)	
clean:
	rm partition $(out1) $(out2) $(out3)
