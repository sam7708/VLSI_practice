exe = time ../bin/fp
test = ../verifier/verify
comp = g++ -o ../bin/fp main.cpp -O3

block1 = ../testcase/n100.blocks
block2 = ../testcase/n200.blocks
block3 = ../testcase/n300.blocks
nets1 = ../testcase/n100.nets
nets2 = ../testcase/n200.nets
nets3 = ../testcase/n300.nets
pl1 = ../testcase/n100.pl
pl2 = ../testcase/n200.pl
pl3 = ../testcase/n300.pl
out1 = ../output/n100.floorplan
out2 = ../output/n200.floorplan
out3 = ../output/n300.floorplan
all:
	$(comp)
n100_0.1:
	$(exe) $(block1) $(nets1) $(pl1) $(out1) 1.1
n100_0.15:
	$(exe) $(block1) $(nets1) $(pl1) $(out1) 1.15
n200_0.1:
	$(exe) $(block2) $(nets2) $(pl2) $(out2) 1.1
n200_0.15:
	$(exe) $(block2) $(nets2) $(pl2) $(out2) 1.15
n300_0.1:
	$(exe) $(block3) $(nets3) $(pl3) $(out3) 1.1
n300_0.15:
	$(exe) $(block3) $(nets3) $(pl3) $(out3)	1.15
clean:
	rm exe
