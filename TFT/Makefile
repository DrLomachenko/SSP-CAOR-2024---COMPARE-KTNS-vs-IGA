CXX = /opt/homebrew/opt/gcc/bin/g++-14
CXXFLAGS = -O3 -fopenmp -std=c++11 -arch arm64

TARGETS = IGA_version/samplecode IGA_version/run IGA_version/sumariza \
          KTNS_version/samplecode KTNS_version/run KTNS_version/sumariza

all: $(TARGETS)

$(shell mkdir -p IGA_version KTNS_version)


IGA_version/SwitchingCounter.o: IGA.cpp SwitchingCounter.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

IGA_version/samplecode.o: samplecode.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

IGA_version/samplecode: IGA_version/samplecode.o IGA_version/SwitchingCounter.o
	$(CXX) $(CXXFLAGS) -o $@ $^

IGA_version/run: run.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^

IGA_version/sumariza: sumariza.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^

KTNS_version/SwitchingCounter.o: KTNS.cpp SwitchingCounter.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KTNS_version/samplecode.o: samplecode.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

KTNS_version/samplecode: KTNS_version/samplecode.o KTNS_version/SwitchingCounter.o
	$(CXX) $(CXXFLAGS) -o $@ $^

KTNS_version/run: run.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^

KTNS_version/sumariza: sumariza.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf IGA_version KTNS_version *.o