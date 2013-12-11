shortestpath: comparison.h node.h main.cpp node.cpp
	g++ main.cpp node.cpp -o shortestpath.x

clean:
	rm shortestpath.x