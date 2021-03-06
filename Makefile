checkCollisions.so: src/checkCollisions.cpp
	g++ -O3 -Wall -shared -std=c++17 \
		src/checkCollisions.cpp \
		-fPIC `python3 -m pybind11 --includes` \
		-o checkCollisions.so

test: checkCollisions.so
	@pytest tests/test.py -sv

clean:
	rm -rf *.so
